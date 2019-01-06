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

![preview](images/Preview.png)

> 1231231
>> 1231231
>>> 1231231

`行内代码`
**加粗**
*斜体*


```c++
#include <stdio.h>
```

# 编译原理大作业实验报告
## 概述
## 成员及分工
### 成员
-  丁&emsp;泉 1612842
-  高&emsp;阳 1612846
-  韩凌昊 1612851
-  何&emsp;博 1612852
-  刘元浩 1612872

### 词法分析
- Lex版语法分析器：丁泉、高阳
- 正则表达式转NFA：韩凌昊
- NFA合并：韩凌昊
- NFA转DFA：刘元浩
- DFA最小化：丁泉
- 错误和注释处理：何博
- 文件输入输出：何博

### 语法分析
- 设计文法：刘元浩
- FIRST集、FOLLOW集：高阳
- 构造LR1项集：韩凌昊
- 合并LR1项集：何博
- 生成GOTO和ACTION表：何博
- 完成归约移入动作：丁泉
- 构造语法分析树：丁泉

### 语义分析与中间代码生成
- 设计动作：刘元浩、何博
- 重构符号表：何博
- 插入动作：丁泉、韩凌昊
- 生成中间代码：丁泉、韩凌昊

### 代码生成
- 生成汇编代码：韩凌昊

### 代码优化与错误处理
- 类型检查：丁泉、刘元浩
- 消除死代码：丁泉、高阳
- 未使用变量的优化：丁泉
- 恐慌模式：丁泉、高阳

## 文法

## 算法实现及分析

### 词法分析

#### 思路

1. 文件输入和错误、注释处理：在此阶段编译器读入测试文件，将测试文件中的所有注释清除，根据先前阶段构建的`DFA`和对应的终态编号分析源文件的各个词素，并将文件转化为词法单元序列提供给语法分析器。

#### 数据结构

1. 文件输入和错误、注释处理：

&emsp;&emsp;首先从上游`DFA`文件读出

```c++
int row_number; //DFA 矩阵行数
int column_number; //DFA 矩阵列数
int** matrix; //DFA 矩阵
std::map<int, std::string> status_to_pattern //状态编号到模式的映射关系
```

&emsp;&emsp;并初始化输出序列

```c++
std::vector<LexicalUnit> output_sequence;
```

&emsp;&emsp;其中LexicalUnit为一个词法单元

```c++
class LexicalUnit
{
public:
    std::string name;
    std::string morpheme;
    // 在后期未使用，故删除
    // std::string value;
}
```

&emsp;&emsp;使用以下四个函数进行文件的词法分析

```c++
// 从文件中读入一个字符，并输入到DAF矩阵中进行状态装换
auto feed(char ch) -> void; 

// 处理测试文件中多行注释
void deal_with_multiplied_note();

// 处理文件中单行注释
void deal_with_line_note();

// 更新词法单元序列
void update_output_sequence();
```

`feed(char ch)`在进行状态转换时，如果遇见注释则会调用处理注释的函数；如果出现死态则调用函数`update_output_sequence()`更新词法单元序列；若输入非C语言字符(@等)则会报错。

#### 遇到的问题

1. 文件输入和错误、注释处理

- 使用`char`类型存储读入字符，无法读入中文字符。

- 未处理文件中字符串(`""`)

#### 成果

1. 文件输入和错误、注释处理

- 读入`DFA`和测试源文件 

- 输出词法单元序列并传递给语法分析器

---

### 语法分析

#### 思路

4. 合并`LR1`项集：查询并合并`LR1`中所有的同心集，优化状态数量，删除被合并的项目族和对应的`GO`函数，得到`LALR1`项目族集合和对应的`GO`函数

5. 生成`GOTO`和`ACTION`表：通过`LALR1`的`GO`函数生成对应的`GOTO`表和`ACTION`表

6. 完成归约移入动作：
![preview](images/grammar_reduce_shift.jpg)

7. 构造语法分析树：
按照产生式和`Action`表以及`Goto`表对词法单元序列进行移入归约操作。在进行归约操作时构造新的父节点以及相应的子节点。最后将唯一的父节点作为整棵语法分析树的根节点保存在`root`属性中。

#### 数据结构

4. 合并`LR1`项集：

&emsp;&emsp;merge_all

```c++
// 合并所有同心集
void merge_all();
// 在该函数中进行
```

5. 生成`GOTO`和`ACTION`表：

6. 完成归约移入动作：
7. 构造语法分析树：

```c++
class GrammerAnalyzer {
private:
    // 定义存储产生式的结构体，内部使用一个存储类型为string的vector记录产生式各个部分的内容
    typedef struct production {
        std::vector<std::string*> production_formula;
        production() {}
    }production;

    // 读入内存中存储的词法单元序列
    std::vector<hebo::LexicalUnit> output_sequence;

    // 记录终结符
    int terminal_number;
    std::string** terminal_list;

    // 记录非终结符
    int non_terminal_number;
    std::string** non_terminal_list;

    // 记录所有产生式的内容
    int production_number;
    production** production_list;

    // 记录action表和goto表的内容（从文件中读入）
    int table_number;
    std::vector<std::vector<std::string*>> action_table;
    std::vector<std::vector<std::string*>> goto_table;

public:
    // 记录最后生成语法树根节点的位置
    hebo::LexicalUnit* root;

private:
    // 从文件中读入所有信息，初始化各个表和数组
    void initialization();
    // 读入词法单元序列，构造语法树
    hebo::LexicalUnit* init_tree();
    // 前序遍历输出语法树
    void output_tree(hebo::LexicalUnit*, int);
}
```

#### 遇到的问题

6. 完成归约移入动作：

- C语言读取文件（抽取产生式等信息的操作）函数使用不熟练；

- 在进行语法分析时错误使用浅拷贝赋值指针的位置，应使用深拷贝赋值指针指向的内容。

7. 构造语法分析树：

- 归约时符号弹出栈的顺序（自右向左）与构造语法分析树子节点（自左向右）的顺序相反；

- 如何输出一棵优美的语法分析树，是个问题。

#### 成果 

6. 完成归约移入动作：

- 从文件中正确读入文法各项信息；

- 根据`Action`表和`Goto`表准确无误地处理了词法单元序列。

7. 构造语法分析树：

- 正确生成归约操作对应的语法分析树。

---

### 语义分析与中间代码生成

#### 思路

1. 设计动作：

2. 重构符号表：

3. 插入动作：读入含有动作的产生式，更新语法分析部分的生成的产生式列表；重构记录节点的结构体，将节点属性、动作等内容加入；在节点内用`bool`变量`if_action`区分动作节点与属性节点；重写规约时构造语法分析树的代码。

4. 生成中间代码：与汇编代码定义好接口，从根节点前序遍历整棵语法树，遇到动作节点时执行对应的动作函数，将生成的四元式保存在内存中供下一步使用。

#### 数据结构

1. 设计动作：

2. 重构符号表：

3. 插入动作：
4. 生成中间代码：

```c++
// 以下只列出对GrammerAnalyzer类修改的部分
class GrammerAnalyzer {
    // 记录含有动作产生式的信息，更新production_list
    int production_action_number;
	std::vector<std::pair<int, int>>* transfer_list;
	production** production_list;

    // 函数调用时，记录声明函数的信息，供插入到函数名表使用
    std::vector<int> var_width_list;
    std::vector<std::string> var_name_list;

    // 记录当前所处函数的名字，供构造新的函数表对象使用
    std::string curr_func_name;

public:
    // 存储四元式的数据结构
    typedef struct {
        int index = -1;
        std::string op;
        std::string arg1;
        std::string arg2;
        std::string result;
    }three_address_instruction;

    // 记录四元式内容至内存
    std::vector<three_address_instruction*> final_instruction;

    // 记录全局符号表
    hbst::SymbolTable* out_table;

    // 记录结构体符号表
    hbst::StructTable* struct_table;

    // 记录函数符号表
    hbst::FunctionTable* function_table;

    // 构造函数
    GrammerAnalyzer(std::vector<hebo::LexicalUnit>);
}

// 对于一维数组属性信息的记录，包括数组名，元素类型，元素宽度，符号表中位置，元素地址
typedef struct {
    std::string name;
    std::string element_type;
    std::string pos;
    int element_width;
    std::vector<std::string> element_addr;
} array_info;

class LexicalUnit {
public:
    // 语法分析树节点信息：名字、词素值、是否动作节点、对应动作编号
    std::string name;
    bool if_action;
    int action_num;
    std::string morpheme;

    // 语法分析树节点属性信息：
    struct attribute {
        // 类型宽度、类型名、在符号表中位置
        int width;
        std::string type;
        std::string addr;

        // （如果是常量）常量值
        int const_value;

        // （如果是运算符）运算符值
        std::string op_value;

        // （如果是结构体）结构体信息
        bool if_struct;
        hbst::StructItem struct_info;

        // （如果是数组）数组信息
        array_info array_info;

        // （如果是函数调用）函数参数个数
        int param_number;

        // （如果是动作节点 需要生成四元式） 当前四元式编号
        int instr;

        // （控制流四元式）下一跳转四元式编号，为真跳转、为假跳转四元式编号（回填） continue、break跳转四元式编号
        int next_instr;
        int true_instr;
        int false_instr;
        int con_instr;
        int break_instr;
    } attribute;

    // （语法分析树上）子节点列表 父节点
    std::vector<LexicalUnit*> child_node_list;
    LexicalUnit* father;

    // 节点默认构造函数，默认非动作节点，无父节点，非控制流指令，非数组节点，非结构体节点
    LexicalUnit() {
        this->if_action = false;
        this->action_num = -1;
        this->father = NULL;
        this->attribute.instr = -1;
        this->attribute.next_instr = -1;
        this->attribute.true_instr = -1;
        this->attribute.false_instr = -1;
        this->attribute.con_instr = -1;
        this->attribute.break_instr = -1;
        this->attribute.if_struct = false;
    }
};
```

#### 遇到的问题

1. 设计动作：

2. 重构符号表：

3. 插入动作：

- 由于前期总体设计未考虑周全，导致构造语法分析树时未能将动作节点直接加入；且在产生式列表生成过程中使用了`set`，使得每次生成产生式，其顺序都不一样；因此使用`O(n^2)`代价的扫描将加入节点的产生式合并进原产生式列表中。此处未来可以优化。

- 动作设计过程中，一些属性值传递的动作没有设计完全，导致前期生成中间代码无法运行。

4. 生成中间代码：

- 无问题。

#### 成果 

1. 设计动作：

2. 重构符号表：

3. 插入动作：

- 将原产生式更新为含有动作的产生式，在规约时正确生成语法分析树。

4. 生成中间代码：

- 在对语法分析树的前序遍历过程中正确生成了中间代码，与汇编代码的接口定义良好，运行无误。

---

### 代码生成
#### 思路
#### 数据结构
#### 遇到的问题
#### 成果 

---

### 代码优化与错误处理
#### 思路
#### 数据结构
#### 遇到的问题
#### 成果 


<table style="width:100%;">
<tr>
<th width="15%">op</th>
<th width="15%">arg1</th>
<th width="15%">arg2</th>
<th width="15%">result</th>
<th width="40%">说明</th>
</tr>
<tr><td colspan="5" align="center">asd</td></tr>
<tr>
<td></td>
<td></td>
<td></td>
<td></td>
</tr>
</table>