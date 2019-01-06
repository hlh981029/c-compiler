# 简单的C语言编译器
编译原理课程大作业

## 概述
## 成员及分工
### 成员

|    姓名    |  学号   |
| :--------: | :-----: |
| 丁&emsp;泉 | 1612842 |
| 高&emsp;阳 | 1612846 |
|   韩凌昊   | 1612851 |
| 何&emsp;博 | 1612852 |
|   刘元浩   | 1612872 |


### 词法分析
|      任务       |   负责人   |
| :-------------: | :--------: |
| `Lex`版语法分析器 | 丁泉、高阳 |
| 正则表达式转`NFA` |   韩凌昊   |
|     `NFA`合并     |   韩凌昊   |
| `NFA`转`DFA` | 刘元浩 |
|    `DFA`最小化    |    丁泉    |
| 错误和注释处理  |    何博    |
|  文件输入输出   |    何博    |

### 语法分析

| 任务 | 负责人 |
| :-------------: | :--------: |
| 设计文法 | 刘元浩 |
| `FIRST`集、`FOLLOW`集 | 高阳 |
| 构造`LR1`项集 | 韩凌昊 |
| 合并`LR1`项集 | 何博 |
| 生成`GOTO`和`ACTION`表 | 何博 |
| 完成规约移入动作 | 丁泉 |
| 构造语法分析树 | 丁泉 |


### 语义分析与中间代码生成

| 任务 | 负责人 |
| :-------------: | :--------: |
| 设计动作 | 刘元浩、何博 |
| 重构符号表 | 何博 |
| 插入动作 | 丁泉、韩凌昊 |
| 生成中间代码 | 丁泉、韩凌昊 |


### 代码生成

| 任务 | 负责人 |
| :-------------: | :--------: |
| 设计三地址代码用法 | 韩凌昊 |
| 生成汇编代码 | 韩凌昊 |

### 代码优化与错误处理

| 任务 | 负责人 |
| :-------------: | :--------: |
| 类型检查 | 丁泉、刘元浩 |
| 消除死代码 | 丁泉、高阳 |
| 未使用变量的优化 | 丁泉 |
| 恐慌模式 | 丁泉、高阳 |

## 文法

## 算法实现及分析

### 词法分析

#### 思路

1. 正则表达式转`NFA`:

2. `NFA`合并：

3. `NFA`转`DFA`：

4. `DFA`最小化：

![preview](images/lexical_min_DFA_amount.jpg)

5. 文件输入和错误、注释处理：在此阶段编译器读入测试文件，将测试文件中的所有注释清除，根据先前阶段构建的`DFA`和对应的终态编号分析源文件的各个词素，并将文件转化为词法单元序列提供给语法分析器。

#### 数据结构

1. 正则表达式转`NFA`:

2. `NFA`合并：

3. `NFA`转`DFA`：

4. `DFA`最小化：

&emsp;&emsp;以下列出记录最小化`DFA`信息的数据结构

```c++
class Min_DFA {
public:
    vector<set<int>> vec;
    // 记录DFA初态的编号
    int dfa_s;
    // 记录原DFA状态数量
    int n_dfa_states;
    // 记录输入字符类型数量
    int n_chars;
    // 存储传入的DFA
    int** matrix;

    // 非终态集合
    set<int> start_set;
    // 终态集合
    set<int> final_set;

    // 记录最小化DFA结果
    vector<vector<int>>ans;
    map<int, string>map_ans;
    // 记录最小化DFA中初态的编号
    int start_state_ans;
}
```

&emsp;&emsp;以下列出进行最小化`DFA`的操作函数

```c++
    // 最小化DFA具体实现操作
    Min_DFA(map<int, string> dfa_end, int** dfa_map, int dfa_s, int n_dfa_states, int n_chars);

    // 获取一个状态所在集合的编号（即该集合第一个状态的编号）
    int get_begin(int destination);
    int get_position(int destination);

    // 拆分集合的函数
    bool break_up(set<int> origin_set);
}
```

5. 文件输入和错误、注释处理：

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

&emsp;&emsp;其中`LexicalUnit`为一个词法单元：

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

&emsp;&emsp;使用以下四个函数进行文件的词法分析：

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

1. 正则表达式转`NFA`:

2. `NFA`合并：

3. `NFA`转`DFA`：

4. `DFA`最小化：

- 不同的正则表达式，其终态在初始化终态的集合时应分立到不同的集合中去，同一正则表达式的不同终态在初始化终态的集合时应归到相同的集合中。该BUG未能在小规模测试中找到。

5. 文件输入和错误、注释处理

- 使用`char`类型存储读入字符，无法读入中文字符；

- 未处理文件中字符串(`""`)。

#### 成果

1. 正则表达式转`NFA`:

2. `NFA`合并：

3. `NFA`转`DFA`：

4. `DFA`最小化：

- 成功完成`DFA`状态的最小化，并将简化后的状态转换表存入文件中。

5. 文件输入和错误、注释处理

- 读入`DFA`和测试源文件；

- 输出词法单元序列并传递给语法分析器。

---

### 语法分析

#### 思路

4. 合并`LR1`项集形成`LALR1`：查询并合并`LR1`中所有的同心集，优化状态数量，删除被合并的项目族和对应的`GO`函数，得到`LALR1`项目族集合和对应的`GO`函数

5. 生成`GOTO`和`ACTION`表：通过`LALR1`的`GO`函数生成对应的`GOTO`表和`ACTION`表。

6. 完成归约移入动作：
![preview](images/grammar_reduce_shift.jpg)

7. 构造语法分析树：
按照产生式和`Action`表以及`Goto`表对词法单元序列进行移入归约操作。在进行归约操作时构造新的父节点以及相应的子节点。最后将唯一的父节点作为整棵语法分析树的根节点保存在`root`属性中。

#### 数据结构

4. 合并`LR1`项集形成`LALR1`：

* `merge_all()`函数进行合并同心集，该函数会遍历项目族集合
* 在`merge_all()`函数中使用`can_merge(int, int)`查看两个状态是否能够进行合并
* 如果能够合并则调用`merge_go_table(int, int)`和`merge_itemSets(int, int)`进行`GO`表的合并和项目族的合并。

5. 生成`GOTO`和`ACTION`表：


* 从以上步骤得到`LALR1`的状态集合![](https://latex.codecogs.com/gif.latex?C=\left\{I_0,I_1,\cdots,I_n\right\})
* 如果有![](https://latex.codecogs.com/gif.latex?GO(I_i,X)=I_j,X\in%20terminal)，则置![](https://latex.codecogs.com/gif.latex?ACTION(i,X)=s_j)
* 如果有![](https://latex.codecogs.com/gif.latex?GO(I_i,X)=I_j,X\in%20nonterminal)，则置![](https://latex.codecogs.com/gif.latex?GOTO(i,X)=j)
* 如果项目![](https://latex.codecogs.com/gif.latex?A\rightarrow\alpha\cdot,a)在状态![](https://latex.codecogs.com/gif.latex?I_i)中，则置![](https://latex.codecogs.com/gif.latex?ACTION(i,a)=r_k)，其中![](https://latex.codecogs.com/gif.latex?k)为产生式对应的序号
* 如果增广文法开始项目在![](https://latex.codecogs.com/gif.latex?I_i)中，则置![](https://latex.codecogs.com/gif.latex?ACTION(i,\$)=acc)


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

4. 合并`LR1`项集形成`LALR1`：

- 试图使用快速构建法直接构建`LALR1`，但是出现相同输入相同程序但输出不同的BUG，估计指针管理不当


5. 生成`GOTO`和`ACTION`表：

- 文法存在移进-归约冲突，但是在此处仅做出标记，未进一步解决

6. 完成归约移入动作：

- `C`语言读取文件（抽取产生式等信息的操作）函数使用不熟练；

- 在进行语法分析时错误使用浅拷贝赋值指针的位置，应使用深拷贝赋值指针指向的内容。

7. 构造语法分析树：

- 归约时符号弹出栈的顺序（自右向左）与构造语法分析树子节点（自左向右）的顺序相反；

- 如何输出一棵优美的语法分析树，是个问题。

#### 成果 

4. 合并`LR1`项集形成`LALR1`：

- 减少状态数量从1000以上到300左右，提高分析器查表效率


5. 生成`GOTO`和`ACTION`表：

- 为分析器提供分析表

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

4. 生成中间代码：与汇编代码定义好接口，从根节点前序遍历整棵语法树，遇到动作节点时通过访问`SwitchToFunction.cpp`找到并执行对应的动作函数，将生成的四元式保存在内存中供下一步使用。

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
1. 三地址代码用法表

<table style="width:100%;">
  <tbody>
  <tr>
    <th width="15%">op</th>
    <th width="15%">arg1</th>
    <th width="15%">arg2</th>
    <th width="15%">result</th>
    <th width="40%">说明</th>
  </tr>
  <tr>
    <td colspan="5" align="center"><b>双目运算指令</b></td>
  </tr>
  <tr>
    <td>+</td>
    <td>operand1</td>
    <td>operand2</td>
    <td>result</td>
    <td>result = operand1 + operand2</td>
  </tr>
  <tr>
    <td>-</td>
    <td>operand1</td>
    <td>operand2</td>
    <td>result</td>
    <td>result = operand1 - operand2</td>
  </tr>
  <tr>
    <td>*</td>
    <td>operand1</td>
    <td>operand2</td>
    <td>result</td>
    <td>result = operand1 * operand2</td>
  </tr>
  <tr>
    <td>/</td>
    <td>operand1</td>
    <td>operand2</td>
    <td>result</td>
    <td>result = operand1 / operand2</td>
  </tr>
  <tr>
    <td>%</td>
    <td>operand1</td>
    <td>operand2</td>
    <td>result</td>
    <td>result = operand1 % operand2</td>
  </tr>
  <tr>
    <td>^</td>
    <td>operand1</td>
    <td>operand2</td>
    <td>result</td>
    <td>result = operand1 ^ operand2</td>
  </tr>
  <tr>
    <td>=</td>
    <td>operand</td>
    <td>-</td>
    <td>result</td>
    <td>result = operand</td>
  </tr>
  <tr>
    <td colspan="5" align="center"><b>单目运算指令</b></td>
  </tr>
  <tr>
    <td>++</td>
    <td>operand</td>
    <td>-</td>
    <td>result</td>
    <td>result = operand++</td>
  </tr>
  <tr>
    <td>--</td>
    <td>operand</td>
    <td>-</td>
    <td>result</td>
    <td>result = operand--</td>
  </tr>
  <tr>
    <td>MINUS</td>
    <td>operand</td>
    <td>-</td>
    <td>result</td>
    <td>result = -operand</td>
  </tr>
  <tr>
    <td>!</td>
    <td>operand</td>
    <td>-</td>
    <td>result</td>
    <td>result = !operand</td>
  </tr>
  <tr>
    <td colspan="5" align="center"><b>数组操作指令</b></td>
  </tr>
  <tr>
    <td>=[]</td>
    <td>array</td>
    <td>offset</td>
    <td>operand</td>
    <td>operand = array[offset]</td>
  </tr>
  <tr>
    <td>[]=</td>
    <td>array</td>
    <td>offset</td>
    <td>operand</td>
    <td>array[offset] = operand</td>
  </tr>
  <tr>
    <td colspan="5" align="center"><b>跳转指令（line）为跳转到的行号</b></td>
  </tr>
  <tr>
    <td>JMP</td>
    <td>-</td>
    <td>-</td>
    <td>line</td>
    <td>无条件跳转</td>
  </tr>
  <tr>
    <td>JE</td>
    <td>operand1</td>
    <td>operand2</td>
    <td>line</td>
    <td>operand1等于operand2则跳转</td>
  </tr>
  <tr>
    <td>JNE</td>
    <td>operand1</td>
    <td>operand2</td>
    <td>line</td>
    <td>operand1不等于operand2则跳转</td>
  </tr>
  <tr>
    <td>JG</td>
    <td>operand1</td>
    <td>operand2</td>
    <td>line</td>
    <td>operand1大于operand2则跳转</td>
  </tr>
  <tr>
    <td>JNG</td>
    <td>operand1</td>
    <td>operand2</td>
    <td>line</td>
    <td>operand1不大于operand2则跳转</td>
  </tr>
  <tr>
    <td>JGE</td>
    <td>operand1</td>
    <td>operand2</td>
    <td>line</td>
    <td>operand1大于等于operand2则跳转</td>
  </tr>
  <tr>
    <td>JNGE</td>
    <td>operand1</td>
    <td>operand2</td>
    <td>line</td>
    <td>operand1不大于等于operand2则跳转</td>
  </tr>
  <tr>
    <td>JL</td>
    <td>operand1</td>
    <td>operand2</td>
    <td>line</td>
    <td>operand1小于operand2则跳转</td>
  </tr>
  <tr>
    <td>JNL</td>
    <td>operand1</td>
    <td>operand2</td>
    <td>line</td>
    <td>operand1不小于operand2则跳转</td>
  </tr>
  <tr>
    <td>JLE</td>
    <td>operand1</td>
    <td>operand2</td>
    <td>line</td>
    <td>operand1小于等于operand2则跳转</td>
  </tr>
  <tr>
    <td>JNLE</td>
    <td>operand1</td>
    <td>operand2</td>
    <td>line</td>
    <td>operand1不小于等于operand2则跳转</td>
  </tr>
  <tr>
    <td>JZ</td>
    <td>operand</td>
    <td>-</td>
    <td>line</td>
    <td>operand为假则跳转</td>
  </tr>
  <tr>
    <td>JNZ</td>
    <td>operand</td>
    <td>-</td>
    <td>line</td>
    <td>operand为真则跳转</td>
  </tr>
  <tr>
    <td colspan="5" align="center"><b>函数调用指令</b></td>
  </tr>
  <tr>
    <td>PARAM</td>
    <td>argument</td>
    <td>-</td>
    <td>-</td>
    <td>将argument添加到参数列表</td>
  </tr>
  <tr>
    <td>CALL</td>
    <td>name</td>
    <td>-</td>
    <td>-</td>
    <td>调用名为name的函数</td>
  </tr>
  <tr>
    <td colspan="5" align="center"><b>函数定义指令</b></td>
  </tr>
  <tr>
    <td>FUNC</td>
    <td>name</td>
    <td>-</td>
    <td>-</td>
    <td>定义一个为name的函数</td>
  </tr>
  <tr>
    <td>ENDF</td>
    <td>name</td>
    <td>-</td>
    <td>-</td>
    <td>结束定义一个为name的函数</td>
  </tr>
  <tr>
    <td>RET</td>
    <td>argument</td>
    <td>-</td>
    <td>-</td>
    <td>终止函数，返回值为argument（可为空）</td>
  </tr>
  <tr>
    <td colspan="5" align="center"><b>空指令</b></td>
  </tr>
  <tr>
    <td>NULL</td>
    <td>-</td>
    <td>-</td>
    <td>-</td>
    <td>不生成任何指令</td>
  </tr>
</tbody>
</table>

#### 遇到的问题

#### 成果 

---

### 代码优化与错误处理

#### 思路

1. 类型检查：对所有逻辑运算符、赋值运算符、算术运算符、位运算符进行类型为`int`的类型检查；对所有的函数调用的参数和返回值类型进行类型检查；对所有的数组下标进行类型为`int`的类型检查。

2. 消除死代码：对`op`为`'-'`，`arg1`为`'1'`的四元式进行优化。在我们设计的四元式与汇编代码的对应关系中，该语句起辅助回填的作用，在回填结束后即没有任何用处，故在生成汇编代码之前将其优化。

3. 未使用变量的优化：对所声明的变量进行检查，如果他未出现下列三种情况之一，即将其优化掉：
     - 该变量被用作函数调用时传入参数（主要针对函数调用时传值传参所生成的临时变量）；
     - 该变量被用作表示数组访问下标；
     - 该变量被用于计算过程中除赋值外的其他部分。

4. 恐慌模式：当进行变量调用时，对变量是否已经在符号表中声明进行检查；当进行赋值或计算或函数调用时进行类型检查；当以上检查未通过时，输出错误提示信息，丢弃当前词法单元，继续向下遍历语法分析树。

#### 数据结构

1. 类型检查：当检查除类型不匹配时，输出错误提示信息，使用恐慌模式策略，继续遍历语法树。

```c++
void GrammerAnalyzer::say_error(int error_type, std::string left_type, std::string right_type) {
    std::cout << "NEED A " << right_type << " GET A " << left_type << std::endl;
    system("pause");
    return;
}
```

2. 消除死代码：此处时间复杂度为`O(n)`，代码思路已说明。

```c++
int cnt = 0;
for (int i = 0; i < this->final_instruction.size(); i++) {
    three_address_instruction* temp_instruction = this->final_instruction[i];
    if (temp_instruction->op == "JZ" && temp_instruction->result == std::to_string(i)) {
        temp_instruction->op = "NULL";
        cnt++;
        std::cout <<"NO: "<< i << " Instructions: Optimized For No-Meaning Loop" << std::endl;
    }
}
std::cout << "Optimize instructions: " << cnt << std::endl;
```

3. 未使用变量的优化：此处时间复杂度为`O(n^2)`，代码思路已说明。

```c++
cnt = 0;
for (int i1 = 0; i1 < this->final_instruction.size(); i1++) {
    three_address_instruction* temp_instruction = this->final_instruction[i1];
    if (temp_instruction->op == "=") {
        std::string temp_name = temp_instruction->result;
        bool flag = false;
        for (int i2 = 0; i2 < i1; i2++) {
            three_address_instruction* temp_temp_instruction = this->final_instruction[i2];
            if (temp_temp_instruction->op == "PARAM" && temp_temp_instruction->arg1 == temp_name) {
                flag = true;
                break;
            }
        }
        if (flag == false) {
            for (int i2 = i1 + 1; i2 < this->final_instruction.size(); i2++) {
                three_address_instruction* temp_temp_instruction = this->final_instruction[i2];
                if (temp_temp_instruction->op == "[]=" && temp_temp_instruction->result == temp_name) {
                    flag = true;
                    break;
                }
                if (temp_temp_instruction->arg1 == temp_name || temp_temp_instruction->arg2 == temp_name) {
                    flag = true;
                    break;
                }
            }
        }
        if (flag == true) {
            continue;
        }
        else {
            temp_instruction->op = "NULL";
            std::cout << "NO: " << i1 << " Instructions: Optimized For UnUsed Variables" << std::endl;
            cnt++;
        }
    }
}
std::cout << "Optimize instructions: " << cnt << std::endl;
```

4. 恐慌模式：代码思路已说明。

```c++
if (root->if_action == true) 
{
    execute_action(root->action_num, root);
    std::cout << "ACTION" << root->action_num << ": EXECUTED!" << std::endl;
}
```

#### 遇到的问题

- 此处没有遇到问题，但是未来改进和提升的空间仍有很大。

#### 成果 
- 完成了类型检查、错误处理和代码优化工作。
