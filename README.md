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
##### 文件输入和错误、注释处理
&emsp;&emsp;在此阶段编译器读入测试文件，将测试文件中的所有注释清除，根据先前阶段构建的`DFA`和对应的终态编号分析源文件的各个词素，并将文件转化为词法单元序列提供给语法分析器。

#### 数据结构
##### 文件输入和错误、注释处理
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
##### 文件输入和错误、注释处理
1. 使用`char`类型存储读入字符，无法读入中文字符。
2. 未处理文件中字符串(`""`)

#### 成果
##### 文件输入和错误、注释处理
- 读入`DFA`和测试源文件 
- 输出词法单元序列并传递给语法分析器

---
### 语法分析

#### 思路
6. 完成归约移入动作：
![preview](images/grammar_reduce_shift.jpg)

7. 构造语法分析树：
按照产生式和Action表以及Goto表对词法单元序列进行移入归约操作。在进行归约操作时构造新的父节点以及相应的子节点。最后将唯一的父节点作为整棵语法分析树的根节点保存在root属性中。

#### 数据结构
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
- 根据Action表和Goto表准确无误地处理了词法单元序列。

7. 构造语法分析树：
- 正确生成归约操作对应的语法分析树。

---
### 语义分析与中间代码生成
#### 思路
#### 数据结构
#### 遇到的问题
#### 成果 
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