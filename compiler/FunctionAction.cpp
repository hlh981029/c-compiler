#include "GrammerAnalyzer.h"
using namespace hbst;
void GrammerAnalyzer::action101(hebo::LexicalUnit* root) {
	return;
}

void GrammerAnalyzer::action102(hebo::LexicalUnit* root) {
	root->father->child_node_list[2]->attribute.con_instr = root->father->attribute.con_instr;
	root->father->child_node_list[2]->attribute.break_instr = root->father->attribute.break_instr;
    SymbolTable* temptable = new SymbolTable("", this->out_table);
    this->out_table = temptable;
	return;
}

void GrammerAnalyzer::action103(hebo::LexicalUnit* root) {
    SymbolTable* temptable = new SymbolTable("", this->out_table);
    this->out_table = temptable;
	return;
}

void GrammerAnalyzer::action104(hebo::LexicalUnit* root) {
    root->father->child_node_list[3]->attribute.con_instr = root->father->attribute.con_instr;
    root->father->child_node_list[3]->attribute.break_instr = root->father->attribute.break_instr;
    SymbolTable* temptable = new SymbolTable("", this->out_table);
    this->out_table = temptable;
	return;
}

void GrammerAnalyzer::action109(hebo::LexicalUnit* root) {
	return;
}

void GrammerAnalyzer::action110(hebo::LexicalUnit* root) {
	return;
}

void GrammerAnalyzer::action111(hebo::LexicalUnit* root) {
	return;
}

void GrammerAnalyzer::action112(hebo::LexicalUnit* root) {
	return;
}

void GrammerAnalyzer::action113(hebo::LexicalUnit* root) {
	this->out_table = &global_symbol_table;
	this->struct_table = &global_struct_table;
	this->function_table = &global_function_table;
	return;
}

void GrammerAnalyzer::action114(hebo::LexicalUnit* root) {
    this->out_table = out_table->father;
    return;
}

void GrammerAnalyzer::action115(hebo::LexicalUnit* root) {
    this->out_table = out_table->father;
    return;
}

void GrammerAnalyzer::action116(hebo::LexicalUnit* root) {
    this->out_table = out_table->father;
    return;
}

void GrammerAnalyzer::action601(hebo::LexicalUnit* root) {
    root->father->child_node_list[1]->attribute.type = root->father->attribute.type;
    return;
}

void GrammerAnalyzer::action602(hebo::LexicalUnit* root) {
    SymbolItem temp_item;
    try {
        temp_item = this->out_table->get_symbol_from_address(root->father->child_node_list[1]->attribute.addr);
    }
    catch (std::string &s) {
        SymbolItem new_symbol_item(root->father->child_node_list[1]->morpheme, "function", 0, 0);
        this->out_table->put_symbol(new_symbol_item);
        temp_item = new_symbol_item;
    }
    FunctionItem func_item(temp_item.name, root->father->child_node_list[1]->attribute.type);
    function_table->put_function(func_item);
    root->father->child_node_list[4]->morpheme = temp_item.name;
    return;
}

void GrammerAnalyzer::action603(hebo::LexicalUnit* root) {
    root->father->child_node_list[1]->attribute.type = root->father->attribute.type;
    return;
}

void GrammerAnalyzer::action604(hebo::LexicalUnit* root) {
    SymbolItem temp_item;
    try {
        temp_item = this->out_table->get_symbol_from_address(root->father->child_node_list[1]->attribute.addr);
    }
    catch (std::string &s) {
        SymbolItem new_symbol_item(root->father->child_node_list[1]->morpheme, "function", 0, 0);
        this->out_table->put_symbol(new_symbol_item);
        temp_item = new_symbol_item;
    }
    FunctionItem func_item(temp_item.name, root->father->child_node_list[1]->attribute.type);
    function_table->put_function(func_item);
    return;
}

void GrammerAnalyzer::action605(hebo::LexicalUnit* root) {
    this->function_table->get_function(root->father->morpheme).add_parameter(root->father->child_node_list[0]->attribute.type);
    var_width_list.push_back(root->father->child_node_list[0]->attribute.width);
    var_name_list.push_back(root->father->child_node_list[0]->morpheme);
    return;
}


void GrammerAnalyzer::action606(hebo::LexicalUnit* root) {
    this->function_table->get_function(root->father->morpheme).add_parameter(root->father->child_node_list[0]->attribute.type);
    var_width_list.push_back(root->father->child_node_list[0]->attribute.width);
    var_name_list.push_back(root->father->child_node_list[0]->morpheme);
    return;
}

void GrammerAnalyzer::action607(hebo::LexicalUnit* root) {
    root->father->attribute.type = root->father->child_node_list[0]->attribute.type;
    root->father->attribute.width = root->father->child_node_list[0]->attribute.width;
    root->father->morpheme = root->father->child_node_list[1]->morpheme;
    return;
}

void GrammerAnalyzer::action608(hebo::LexicalUnit* root) {
    root->father->attribute.type = root->father->child_node_list[0]->attribute.type;
    root->father->attribute.width = root->father->child_node_list[0]->attribute.width;
    root->father->morpheme = "";
    return;
}
