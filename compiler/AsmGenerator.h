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
    // 汇编代码文件输出流
    std::ofstream asm_out;
    // 全局符号表
    SymbolTable *global_symbol_table;
    // 函数表
    FunctionTable *function_table;
    // 结构体表
    StructTable *struct_table;
    // 三地址指令表
    std::vector<GrammerAnalyzer::three_address_instruction*> *final_instruction;
    // 构造函数与析构函数
    AssemblyGenerator();
    ~AssemblyGenerator();
    // 生成汇编代码总函数
    void generate_asm();
    // 生成翻译三地址指令前print、input函数定义等必需的汇编代码
    void generate_header();
    // 生成函数声明的汇编代码
    void generate_proto();
    // 生成翻译三地址指令后的一些必需的汇编代码
    void generate_footer();
    // 生成全局变量声明的汇编代码
    void generate_global_var();
    // 生成三地址指令翻译成的汇编代码
    void generate_code();
    // 关闭汇编输出文件
    void close_file();
    // 获取函数的符号表
    SymbolTable* get_function_symbol_table(std::string name);
    // 生成测试样例（测试用）
    void generate_example();
    // 输出三地址指令列表（测试用）
    void output_instructions();
    // 向符号表、结构体表、函数表、三地址指令列表中添加项目（测试用）
    void add_symbol(SymbolItem i, SymbolTable* t = NULL);
    void add_struct(StructItem* i);
    void add_function(FunctionItem* i);
    void add_instruction(GrammerAnalyzer::three_address_instruction *i);
};