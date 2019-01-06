## 123
### 123
#### 123
##### 123
- aaaa
  - 123
    - 1234	
1. 123
2. 1231231
   1. 123
- [ ] 123

> 1231231
>> 1231231
>>> 123123

`行内代码`
**加粗**
*斜体*


```c++
#include <stdio.h>
```

# 编译原理大作业实验报告
## 概述
## 分工
## 文法
## 代码介绍
### 词法分析
#### &emsp;&emsp;思路
#### &emsp;&emsp;数据结构
#### &emsp;&emsp;遇到的问题
#### &emsp;&emsp;成果 
### 语法分析
### 语义分析
### 中间代码生成
### 代码生成
### 代码优化和错误处理
### 


```c++
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
    SymbolTable* get_function_symbol_table(std::string name);
};
```