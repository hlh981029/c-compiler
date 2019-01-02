#include "AsmGenerator.h"
using namespace std;

AssemblyGenerator::AssemblyGenerator()
{
    asm_out.open("../Assembly/Assembly.asm", ios::out);
}

AssemblyGenerator::~AssemblyGenerator()
{

}

void AssemblyGenerator::generate_asm() {

    generate_header();
    generate_global_var();
    generate_code();
    generate_footer();
    close_file();

}

void AssemblyGenerator::generate_header()
{
    asm_out <<
        ".386\n"
        ".model flat, stdcall\n"
        "include msvcrt.inc\n"
        "include kernel32.inc\n"
        "includelib msvcrt.lib\n"
        "includelib kernel32.lib\n" << endl;
    generate_proto();
    asm_out <<
        ".const\n"
        "$output_format_int byte \"%d\", 0DH, 0AH, 0\n"
        "$input_format_int byte \"%d\", 0\n"
        ".code\n"
        "$print proc,\n"
        "    val: dword\n"
        "    invoke crt_printf, addr $output_format_int, val\n"
        "    ret\n"
        "$print endp\n"
        "$input proc,\n"
        "    val : ptr dword\n"
        "    invoke crt_scanf, addr $input_format_int,  val\n"
        "    ret\n"
        "$input endp\n"
        "$$getch proc\n"
        "    invoke crt__getch\n"
        "    ret\n"
        "$$getch endp\n"
        << endl;
}

void AssemblyGenerator::generate_proto()
{
    for (int count = 3; count < function_table->function_item_vector.size(); count++) {
        FunctionItem& func = function_table->function_item_vector[count];
        string temp_arg1 = func.name;
        SymbolTable* func_symbol_table = get_function_symbol_table(temp_arg1);
        asm_out << "$" << temp_arg1 << " proto";
        int param_num = func.parameter_vector.size();
        vector<SymbolTable*> func_symbol_table_list;
        SymbolTable* temp_symbol_table;
        func_symbol_table_list.push_back(func_symbol_table);
        for (int count = 0; count < func_symbol_table_list.size(); count++) {
            for (int count1 = 0; count1 < func_symbol_table_list[count]->son_vector.size(); count1++) {
                func_symbol_table_list.push_back(func_symbol_table_list[count]->son_vector[count1]);
            }
        }
        if (param_num != 0) {
            // 参数不为空
            SymbolItem * temp_symbol;
            string temp_type;
            int temp_is_array;
            for (int count = 0; count < param_num; count++) {
                asm_out << "," << endl;
                temp_symbol = &func_symbol_table->symbol_item_vector[count];
                asm_out << "    " << temp_symbol->address << ":";
                temp_type = temp_symbol->type;
                temp_is_array = temp_type.rfind("[");
                if (temp_type == "int") {
                    // int
                    asm_out << "sdword";
                }
                else if (temp_type.substr(0, 3) == "int" && temp_is_array != -1) {
                    // int[]
                    asm_out << "ptr sdword";
                }
                else if (temp_type == "struct") {
                    // struct
                }
                else if (temp_type.substr(0, 6) == "struct" && temp_is_array == -1) {
                    // struct a
                }
                else if (temp_type.substr(0, 6) == "struct" && temp_is_array != -1) {
                    // struct a[]
                }
            }
        }
        if (func.return_type != "void") {
            if (func.return_type == "int") {
                asm_out << "," << endl;
                asm_out << "    temp: ptr sdword";
            }
            else if (func.return_type.substr(0, 6) == "struct") {

            }

        }
        asm_out << endl;
    }
}

void AssemblyGenerator::generate_footer()
{
    asm_out << "END $main" << endl;
}

void AssemblyGenerator::generate_global_var()
{
    asm_out << ".data" << endl;
    int symbol_size = global_symbol_table->symbol_item_vector.size();
    SymbolItem* temp_item;
    string temp_type;
    int temp_is_array;
    for (int i = 0; i < symbol_size; i++) {
        temp_item = &global_symbol_table->symbol_item_vector[i];
        temp_type = temp_item->type;
        temp_is_array = temp_type.rfind("[");
        if (temp_type == "int") {
            // int
            asm_out << "    " << temp_item->address << " sdword ?" << endl;
        }
        else if (temp_type.substr(0, 3) == "int" && temp_is_array != -1){
            // int[]
            asm_out << "    " << temp_item->address << " sdword " << temp_item->width / 4 << " dup(?)" << endl;
        }
        else if (temp_type == "struct") {
            // struct
            continue;
        }
        else if (temp_type.substr(0, 6) == "struct" && temp_is_array == -1) {
            // struct a
            asm_out << "    " << temp_item->address << " label byte" << endl;
        }
        else if (temp_type.substr(0, 6) == "struct" && temp_is_array != -1) {
            // struct a[]
            asm_out << "    " << temp_item->address << " label byte" << endl;
        }
        else if (temp_type == "function") {
            // function
            continue;
        }
    }
    asm_out << endl;
}

void AssemblyGenerator::generate_code()
{
    asm_out << ".code" << endl;
    GrammerAnalyzer::three_address_instruction *temp_instruction;
    int instruction_size = final_instruction->size();
    string temp_op, temp_arg1, temp_arg2, temp_result;
    int have_no_param = 1;
    int param_number = 0;
    vector<string> param_list;
    string current_func_name;
    int temp_label_num = 0;
    for (int i = 0; i < instruction_size; i++) {
        temp_instruction = final_instruction->at(i);
        asm_out << "label" << temp_instruction->index << ":" << endl;
        temp_op = temp_instruction->op;
        temp_arg1 = temp_instruction->arg1;
        temp_arg2 = temp_instruction->arg2;
        temp_result = temp_instruction->result;

        if (temp_op == "FUNC") {
            current_func_name = temp_arg1;
            asm_out << "$" << temp_arg1 << " PROC";
            FunctionItem& func = function_table->get_function(temp_arg1);
            SymbolTable* func_symbol_table = get_function_symbol_table(temp_arg1);
            int param_num = func.parameter_vector.size();
            vector<SymbolTable*> func_symbol_table_list;
            SymbolTable* temp_symbol_table;
            func_symbol_table_list.push_back(func_symbol_table);
            for (int count = 0; count < func_symbol_table_list.size(); count++) {
                for (int count1 = 0; count1 < func_symbol_table_list[count]->son_vector.size(); count1++) {
                    func_symbol_table_list.push_back(func_symbol_table_list[count]->son_vector[count1]);
                }
            }
            if (param_num != 0) {
                // 参数不为空
                SymbolItem * temp_symbol;
                string temp_type;
                int temp_is_array;
                for (int count = 0; count < param_num; count++) {
                    asm_out << "," << endl;
                    temp_symbol = &func_symbol_table->symbol_item_vector[count];
                    asm_out << "    " << temp_symbol->address << ":";
                    temp_type = temp_symbol->type;
                    temp_is_array = temp_type.rfind("[");
                    if (temp_type == "int") {
                        // int
                        asm_out << "sdword";
                    }
                    else if (temp_type.substr(0, 3) == "int" && temp_is_array != -1) {
                        // int[]
                        asm_out << "ptr sdword";
                    }
                    else if (temp_type == "struct") {
                        // struct
                    }
                    else if (temp_type.substr(0, 6) == "struct" && temp_is_array == -1) {
                        // struct a
                    }
                    else if (temp_type.substr(0, 6) == "struct" && temp_is_array != -1) {
                        // struct a[]
                    }
                }
            }
            if (func.return_type != "void") {
                if (func.return_type == "int") {
                    asm_out << "," << endl;
                    asm_out << "    temp: ptr sdword";
                }
                else if (func.return_type.substr(0, 6) == "struct") {

                }
                asm_out << endl;
            }
            asm_out << endl;
            if (func_symbol_table->symbol_item_vector.size() > param_num || func_symbol_table_list.size() > 1)
            {
                if (param_num == -1) {
                    param_num = 0;
                }
                //asm_out << "    LOCAL ";
                SymbolItem * temp_symbol;
                string temp_type;
                int temp_is_array;
                for (int count_table = 0; count_table < func_symbol_table_list.size(); count_table++) {
                    temp_symbol_table = func_symbol_table_list[count_table];
                    int count = count_table == 0 ? param_num : 0;
                    for (; count < temp_symbol_table->symbol_item_vector.size(); count++) {
                        temp_symbol = &temp_symbol_table->symbol_item_vector[count];
                        //if (count_table == 0 && (count == param_num || count == 0)) {
                        //    asm_out << temp_symbol->address;
                        //}
                        //else {
                            asm_out << "    LOCAL " << temp_symbol->address;
                        //}
                        temp_type = temp_symbol->type;
                        temp_is_array = temp_type.rfind("[");
                        if (temp_type == "int") {
                            // int
                            asm_out << ":sdword";
                        }
                        else if (temp_type.substr(0, 3) == "int" && temp_is_array != -1) {
                            // int[]
                            asm_out << "[" << temp_symbol->width / 4 << "]" << ":sdword";
                        }
                        else if (temp_type == "struct") {
                            // struct
                        }
                        else if (temp_type.substr(0, 6) == "struct" && temp_is_array == -1) {
                            // struct a
                        }
                        else if (temp_type.substr(0, 6) == "struct" && temp_is_array != -1) {
                            // struct a[]
                        }
                        //asm_out << "," << endl;
                        asm_out << endl;
                    }
                }
                //asm_out << "        $end_of_local:dword" << endl;
            }
        }

        else if (temp_op == "PARAM") {
            if (have_no_param) {
                param_number = 0;
                have_no_param = 0;
                param_list.clear();
            }
            param_list.push_back(temp_arg1);
            param_number++;
        }

        else if (temp_op == "CALL") {
            asm_out << "    INVOKE $"<< temp_arg1;
            FunctionItem& func = function_table->get_function(temp_arg1);
            if (!have_no_param) {
                for (int count = 0; count < param_list.size(); count++) {
                    asm_out << ", " << param_list[count];
                }
                have_no_param = 1;
            }
            if (func.return_type == "int") {
                asm_out << ", ADDR " << temp_result;
            }
            else if (func.return_type.substr(0, 6) == "struct") {

            }
            asm_out << endl;
        }

        else if (temp_op == "ENDF") {
            asm_out << current_func_name << "_end:" << endl;
            asm_out << "    ret" << endl;
            asm_out << "$" << temp_arg1 << " ENDP" << endl;
        }

        else if (temp_op == "RET") {
            FunctionItem& func = function_table->get_function(current_func_name);
            string return_type = func.return_type;
            if (return_type == "int") {
                asm_out << "    mov eax, " << temp_arg1 << endl;
                asm_out << "    mov esi, temp" << endl;
                asm_out << "    mov [esi]" << ", eax" << endl;
            }
            asm_out << "    jmp " << current_func_name << "_end" << endl;

        }

        else if (temp_op == "+") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    add eax, " << temp_arg2 << endl;
            asm_out << "    mov " << temp_result << ", eax" << endl;
        }

        else if (temp_op == "-") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    sub eax, " << temp_arg2 << endl;
            asm_out << "    mov " << temp_result << ", eax" << endl;
        }

        else if (temp_op == "*") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    imul eax, " << temp_arg2 << endl;
            asm_out << "    mov " << temp_result << ", eax" << endl;
        }

        else if (temp_op == "/") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    cdq" << endl;
            asm_out << "    mov ebx, " << temp_arg2 << endl;
            asm_out << "    idiv ebx" << endl;
            asm_out << "    mov " << temp_result << ", eax" << endl;
        }

        else if (temp_op == "%") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    cdq" << endl;
            asm_out << "    mov ebx, " << temp_arg2 << endl;
            asm_out << "    idiv ebx" << endl;
            asm_out << "    mov " << temp_result << ", edx" << endl;
        }

        else if (temp_op == "^") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    xor eax, " << temp_arg2 << endl;
            asm_out << "    mov " << temp_result << ", eax" << endl;
        }

        else if (temp_op == "=") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    mov " << temp_result << ", eax" << endl;
        }

        else if (temp_op == "++") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    inc eax" << endl;
            asm_out << "    mov "<< temp_result << ", eax" <<endl;
        }

        else if (temp_op == "--") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    dec eax" << endl;
            asm_out << "    mov " << temp_result << ", eax" << endl;
        }

        else if (temp_op == "MINUS") {
            asm_out << "    mov eax, 0" << endl;
            asm_out << "    mov ebx, " << temp_arg1 << endl;
            asm_out << "    sub eax, ebx" << endl;
            asm_out << "    mov " << temp_result << ", eax" << endl;
        }

        else if (temp_op == "!") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    cmp eax, 0" << endl;
            asm_out << "    jz temp" << temp_label_num << endl;
            asm_out << "    mov eax, 0" << endl;
            asm_out << "    jmp temp" << temp_label_num + 1 << endl;
            asm_out << "temp" << temp_label_num << ":" << endl;
            asm_out << "    mov eax, 1" << endl;
            asm_out << "temp" << temp_label_num + 1 << ":" << endl;
            asm_out << "    mov " << temp_result << ", eax" << endl;
            temp_label_num += 2;
        }

        else if (temp_op == "=[]") {
            asm_out << "    mov esi, " << temp_arg2 << endl;
            asm_out << "    mov eax, " << temp_arg1 << "[esi]" << endl;
            asm_out << "    mov " << temp_result << ", eax" << endl;
        }

        else if (temp_op == "[]=") {
            asm_out << "    mov eax, " << temp_result << endl;
            asm_out << "    mov esi, " << temp_arg2 << endl;
            asm_out << "    mov " << temp_arg1 << "[esi], eax" << endl;
        }

        else if (temp_op == "JMP") {
            asm_out << "    jmp label" << temp_result << endl;
        }

        else if (temp_op == "JE") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    cmp eax, " << temp_arg2 << endl;
            asm_out << "    je label" << temp_result << endl;
        }

        else if (temp_op == "JNE") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    cmp eax, " << temp_arg2 << endl;
            asm_out << "    jne label" << temp_result << endl;
        }

        else if (temp_op == "JG") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    cmp eax, " << temp_arg2 << endl;
            asm_out << "    jg label" << temp_result << endl;
        }

        else if (temp_op == "JNG") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    cmp eax, " << temp_arg2 << endl;
            asm_out << "    jng label" << temp_result << endl;
        }

        else if (temp_op == "JGE") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    cmp eax, " << temp_arg2 << endl;
            asm_out << "    jge label" << temp_result << endl;
        }

        else if (temp_op == "JNGE") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    cmp eax, " << temp_arg2 << endl;
            asm_out << "    jnge label" << temp_result << endl;
        }

        else if (temp_op == "JL") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    cmp eax, " << temp_arg2 << endl;
            asm_out << "    jl label" << temp_result << endl;
        }

        else if (temp_op == "JNL") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    cmp eax, " << temp_arg2 << endl;
            asm_out << "    jnl label" << temp_result << endl;
        }

        else if (temp_op == "JLE") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    cmp eax, " << temp_arg2 << endl;
            asm_out << "    jle label" << temp_result << endl;
        }

        else if (temp_op == "JNLE") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    cmp eax, " << temp_arg2 << endl;
            asm_out << "    jnle label" << temp_result << endl;
        }

        else if (temp_op == "JZ") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    cmp eax, 0" << endl;
            asm_out << "    jz label" << temp_result << endl;
        }

        else if (temp_op == "JNZ") {
            asm_out << "    mov eax, " << temp_arg1 << endl;
            asm_out << "    cmp eax, 0" << endl;
            asm_out << "    jnz label" << temp_result << endl;
        }
        else if (temp_op == "-") {

        }
   }
}

//void AssemblyGenerator::generate_example()
//{
//    global_symbol_table = new SymbolTable;
//    function_table = new FunctionTable;
//    struct_table = new StructTable;
//    final_instruction = new vector<three_address_instruction*>;
//
//    // 三地址指令
//    add_instruction(new three_address_instruction(100   , "FUNC"        , "test_1"                  , ""                    , ""                    ));
//    add_instruction(new three_address_instruction(101   , "PARAM"       , "test_1_int_1$0"          , ""                    , ""                    ));
//    add_instruction(new three_address_instruction(102   , "CALL"        , "test_2"                  , ""                    , "temp$2"              ));
//    add_instruction(new three_address_instruction(103   , "="           , "temp$2"                  , ""                    , "test_1_int_2$1"      ));
//    add_instruction(new three_address_instruction(104   , "PARAM"       , "test_1_int_2$1"          , ""                    , ""                    ));
//    add_instruction(new three_address_instruction(105   , "CALL"        , "print"                   , ""                    , ""                    ));
//    add_instruction(new three_address_instruction(106   , "ENDF"        , "test_1"                  , ""                    , ""                    ));
//
//    add_instruction(new three_address_instruction(200   , "FUNC"        , "test_2"                  , ""                    , ""                    ));
//    add_instruction(new three_address_instruction(201   , "+"           , "test_2_int_1$3"          , "10"                  , "temp$5"              ));
//    add_instruction(new three_address_instruction(202   , "="           , "temp$5"                  , ""                    , "test_2_int_2$4"      ));
//    add_instruction(new three_address_instruction(203   , "RET"         , "test_2_int_2$4"          , ""                    , ""                    ));
//    add_instruction(new three_address_instruction(204   , "ENDF"        , "test_2"                  , ""                    , ""                    ));
//
//    add_instruction(new three_address_instruction(300   , "FUNC"        , "test_3"                  , ""                    , ""                    ));
//    add_instruction(new three_address_instruction(301   , "-"           , "test_3_int_1$7"          , "1"                   , "temp$9"              ));
//    add_instruction(new three_address_instruction(302   , "*"           , "temp$9"                  , "4"                   , "temp$9"              ));
//    add_instruction(new three_address_instruction(303   , "=[]"         , "test_3_int_array$6"      , "temp$9"              , "temp$10"             ));
//    add_instruction(new three_address_instruction(304   , "="           , "temp$10"                 , ""                    , "test_3_int_2$8"      ));
//    add_instruction(new three_address_instruction(305   , "[]="         , "test_3_int_array$6"      , "0"                   , "test_3_int_2$8"      ));
//    add_instruction(new three_address_instruction(306   , "RET"         , "test_3_int_2$8"          , ""                    , ""                    ));
//    add_instruction(new three_address_instruction(307   , "ENDF"        , "test_3"                  , ""                    , ""                    ));
//
//    add_instruction(new three_address_instruction(0     , "FUNC"        , "main"                    , ""                    , ""                    ));
//    add_instruction(new three_address_instruction(1     , "[]="         , "main_int_array_1$12"     , "0"                   , "10"                  ));
//    add_instruction(new three_address_instruction(2     , "[]="         , "main_int_array_1$12"     , "4"                   , "20"                  ));
//    add_instruction(new three_address_instruction(3     , "PARAM"       , "main_int_array_1$12"     , ""                    , ""                    ));
//    add_instruction(new three_address_instruction(4     , "PARAM"       , "2"                       , ""                    , ""                    ));
//    add_instruction(new three_address_instruction(5     , "CALL"        , "test_3"                  , ""                    , ""                    ));
//    add_instruction(new three_address_instruction(6     , "=[]"         , "main_int_array_1$12"     , "0"                   , "temp$13"             ));
//    add_instruction(new three_address_instruction(7     , "PARAM"       , "temp$13"                 , ""                    , ""                    ));
//    add_instruction(new three_address_instruction(8     , "CALL"        , "print"                   , ""                    , ""                    ));
//    add_instruction(new three_address_instruction(9     , "="           , "10"                      , ""                    , "main_int_1$11"       ));
//    add_instruction(new three_address_instruction(10    , "PARAM"       , "main_int_1$11"           , ""                    , ""                    ));
//    add_instruction(new three_address_instruction(11    , "CALL"        , "test_1"                  , ""                    , ""                    ));
//    add_instruction(new three_address_instruction(12    , "RET"         , "0"                       , ""                    , ""                    ));
//    add_instruction(new three_address_instruction(13    , "ENDF"        , "main"                    , ""                    , ""                    ));
//
//    // 符号表
//    SymbolItem *temp;
//    SymbolTable
//        *symbol_input,
//        *symbol_print,
//        *symbol_test_1,
//        *symbol_test_2,
//        *symbol_test_3,
//        *symbol_main,
//        *symbol_table_2;
//
//    // 函数符号表 新建符号表
//    symbol_input        =   new SymbolTable(global_symbol_table);
//    symbol_print        =   new SymbolTable(global_symbol_table);
//    symbol_test_1       =   new SymbolTable(global_symbol_table);
//    symbol_test_2       =   new SymbolTable(global_symbol_table);
//    symbol_test_3       =   new SymbolTable(global_symbol_table);
//    symbol_main         =   new SymbolTable(global_symbol_table);
//
//    // 函数符号表 命名
//    global_symbol_table ->  symbol_table_name = "global";
//    symbol_input        ->  symbol_table_name = "input";
//    symbol_print        ->  symbol_table_name = "print";
//    symbol_test_1       ->  symbol_table_name = "test_1";
//    symbol_test_2       ->  symbol_table_name = "test_2";
//    symbol_test_3       ->  symbol_table_name = "test_3";
//    symbol_main         ->  symbol_table_name = "main";
//
//
//    // 内层符号表 新建符号表
//    symbol_table_2       =   new SymbolTable(symbol_test_1);
//
//    // 函数符号表 插入内置函数符号
//    add_symbol(SymbolItem("input"               , "function"        , 0             , "input"                   ));
//    add_symbol(SymbolItem("print"               , "function"        , 0             , "print"                   ));
//    add_symbol(SymbolItem("$getch"              , "function"        , 0             , "$getch"                  ));
//    
//    // 函数符号表 插入自定义函数符号
//    add_symbol(SymbolItem("test_1"              , "function"        , 0             , "test_1"                  ));
//    add_symbol(SymbolItem("test_2"              , "function"        , 0             , "test_2"                  ));
//    add_symbol(SymbolItem("test_3"              , "function"        , 0             , "test_3"                  ));
//    add_symbol(SymbolItem("main"                , "function"        , 0             , "main"                    ));
//    
//    // 全局符号表
//    add_symbol(SymbolItem("global_int_1"        , "int"             , 4             , "global_int_1$0"          ));
//    add_symbol(SymbolItem("global_int_2"        , "int"             , 4             , "global_int_2$0"          ));
//    add_symbol(SymbolItem("global_int_array_1"  , "int[10]"         , 40            , "global_int_array_1$1"    ));
//    
//    // 函数符号表
//    add_symbol(SymbolItem("test_1_int_1"        , "int"             , 4             , "test_1_int_1$0"          ), symbol_test_1        );
//    add_symbol(SymbolItem("test_1_int_2"        , "int"             , 4             , "test_1_int_2$1"          ), symbol_test_1        );
//    add_symbol(SymbolItem(""                    , "int"             , 4             , "temp$2"                  ), symbol_test_1        );
//
//    add_symbol(SymbolItem("test_2_int_1"        , "int"             , 4             , "test_2_int_1$3"          ), symbol_test_2        );
//    add_symbol(SymbolItem("test_2_int_2"        , "int"             , 4             , "test_2_int_2$4"          ), symbol_test_2        );
//    add_symbol(SymbolItem(""                    , "int"             , 4             , "temp$5"                  ), symbol_test_2        );
//
//    add_symbol(SymbolItem("test_3_int_array"    , "int[10]"         , 4             , "test_3_int_array$6"      ), symbol_test_3        );
//    add_symbol(SymbolItem("test_3_int_1"        , "int"             , 4             , "test_3_int_1$7"          ), symbol_test_3        );
//    add_symbol(SymbolItem("test_3_int_2"        , "int"             , 4             , "test_3_int_2$8"          ), symbol_test_3        );
//    add_symbol(SymbolItem(""                    , "int"             , 4             , "temp$9"                  ), symbol_test_3        );
//    add_symbol(SymbolItem(""                    , "int"             , 4             , "temp$10"                 ), symbol_test_3        );
//
//    add_symbol(SymbolItem("main_int_1"          , "int"             , 4             , "main_int_1$11"           ), symbol_main          );
//    add_symbol(SymbolItem("main_int_array_1"    , "int[10]"         , 4             , "main_int_array_1$12"     ), symbol_main          );
//    add_symbol(SymbolItem(""                    , "int"             , 4             , "temp$13"                 ), symbol_main          );
//    
//    // 函数表
//    FunctionItem *temp_function;
//    temp_function = new FunctionItem("input"        , "int"         ); 
//    add_function(temp_function);
//    temp_function = new FunctionItem("print"        , "void"        ); temp_function->parameter_vector.push_back("int");
//    add_function(temp_function);
//    temp_function = new FunctionItem("$getch"       , "void"        ); 
//    add_function(temp_function);
//    temp_function = new FunctionItem("test_1"       , "void"        ); temp_function->parameter_vector.push_back("int");
//    add_function(temp_function);
//    temp_function = new FunctionItem("test_2"       , "int"         ); temp_function->parameter_vector.push_back("int");
//    add_function(temp_function);
//    temp_function = new FunctionItem("test_3"       , "void"        ); temp_function->parameter_vector.push_back("int[10]"); temp_function->parameter_vector.push_back("int");
//    add_function(temp_function);
//    temp_function = new FunctionItem("main"         , "int"         ); 
//    add_function(temp_function);
//
//    // 结构体表
//
//}

void AssemblyGenerator::output_instructions()
{
    for (int count = 0; count < final_instruction->size(); count++) {
        cout << "\t" << count << "\t" << final_instruction->at(count)->op << "\t" << final_instruction->at(count)->arg1 << "\t" << final_instruction->at(count)->arg2 << "\t" << final_instruction->at(count)->result << "\t" << endl;
    }
}

void AssemblyGenerator::close_file()
{
    asm_out.close();
}

void AssemblyGenerator::add_symbol(SymbolItem i, SymbolTable* t) {
    if (t == NULL) {
        t = global_symbol_table;
    }
    t->symbol_item_vector.push_back(i);
}

void AssemblyGenerator::add_struct(StructItem* i)
{
    struct_table->struct_item_vector.push_back(*i);
}

void AssemblyGenerator::add_function(FunctionItem* i)
{
    function_table->function_item_vector.push_back(*i);
}

void AssemblyGenerator::add_instruction(GrammerAnalyzer::three_address_instruction *i)
{
    final_instruction->push_back(i);
}

SymbolTable * AssemblyGenerator::get_function_symbol_table(string name)
{
    for (int i = 0; i < global_symbol_table->son_vector.size(); i++)
    {
        if (global_symbol_table->son_vector[i]->symbol_table_name == name) {
            return global_symbol_table->son_vector[i];
        }
    }
}

