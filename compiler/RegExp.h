#ifndef COMPILER_REGEXP_H
#define COMPILER_REGEXP_H

#include <string>

struct RegTreeNode
{
    // 该节点的操作符
    char reg_op; // '\1'='*'    '\2'='|'    '\3'='.'    '\4'='('    '\5'=')'
    // 该节点的左右子节点
    RegTreeNode* left;
    RegTreeNode* right;
    // 起止状态号
    int start;
    int end;
    RegTreeNode(char _reg_op, RegTreeNode* _left = nullptr, RegTreeNode* _right = nullptr)
    {
        reg_op = _reg_op;
        left = _left;
        right = _right;
        start = end = 0;
    }
};

class RegExp
{
    // 中缀表达式字符串
    std::string infix_exp;
    // 后缀表达式字符串
    std::string suffix_exp;
    // 语法分析树根节点指针
    RegTreeNode* reg_tree;
public:
    // 构造函数
    RegExp(std::string exp, int mode = 0);
    // 返回该后缀表达式字符串
    std::string get_suffix_exp();
    // 返回语法分析树根节点指针
    RegTreeNode* get_reg_tree();
    // 将后缀表达式输出到控制台
    void get_explicit_suffix_exp();
private:
    // 中缀表达式转后缀表达式
    std::string to_suffix();
    // 后缀表达式转正则树
    RegTreeNode* to_reg_tree();
    // 判断操作符优先级
    bool is_prior(char opreand1, char operand2);
    // 判断是否为操作符
    bool is_operator(char operand);
};

#endif //COMPILER_REGEXP_H
