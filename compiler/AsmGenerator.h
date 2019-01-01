#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "SymbolTable.hpp"

using namespace hbst;

struct three_address_instruction {
    int index;
    std::string op;
    std::string arg1;
    std::string arg2;
    std::string result;
    three_address_instruction(int i, std::string o, std::string a1, std::string a2, std::string re);
};

class AssemblyGenerator {
    std::ofstream asm_out;
    SymbolTable *global_symbol_table;
    FunctionTable *function_table;
    StructTable *struct_table;
    std::vector<three_address_instruction*> *final_instruction;
public:
    AssemblyGenerator();
    ~AssemblyGenerator();
    void generate_asm();
    void generate_header();
    void generate_proto();
    void generate_footer();
    void generate_global_var();
    void generate_code();
    void generate_example();
    void close_file();
    void add_symbol(SymbolItem i, SymbolTable* t = NULL);
    void add_struct(StructItem* i);
    void add_function(FunctionItem* i);
    void add_instruction(three_address_instruction *i);
    //FunctionItem* get_function(string name);
    SymbolTable* get_function_symbol_table(std::string name);
};