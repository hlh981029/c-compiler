#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "SymbolTable.hpp"
#include "GrammerAnalyzer.h"
using namespace hbst;

class AssemblyGenerator {
public:
    std::ofstream asm_out;
    SymbolTable *global_symbol_table;
    FunctionTable *function_table;
    StructTable *struct_table;
    std::vector<GrammerAnalyzer::three_address_instruction*> *final_instruction;

    AssemblyGenerator();
    ~AssemblyGenerator();
    void generate_asm();
    void generate_header();
    void generate_proto();
    void generate_footer();
    void generate_global_var();
    void generate_code();
    void generate_example();
    void output_instructions();
    void close_file();
    void add_symbol(SymbolItem i, SymbolTable* t = NULL);
    void add_struct(StructItem* i);
    void add_function(FunctionItem* i);
    void add_instruction(GrammerAnalyzer::three_address_instruction *i);
    //FunctionItem* get_function(string name);
    SymbolTable* get_function_symbol_table(std::string name);
};