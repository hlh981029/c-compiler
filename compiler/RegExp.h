#ifndef COMPILER_REGEXP_H
#define COMPILER_REGEXP_H

#include <string>

struct RegTreeNode
{
    char reg_op; // '\1'='*'    '\2'='|'    '\3'='.'    '\4'='('    '\5'=')'
    RegTreeNode* left;
    RegTreeNode* right;
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
    std::string infix_exp;
    std::string suffix_exp;
    RegTreeNode* reg_tree;
public:
    RegExp(std::string exp, int mode = 0);
    std::string get_suffix_exp();
    RegTreeNode* get_reg_tree();
    void get_explicit_suffix_exp();
private:
    std::string to_suffix();
    RegTreeNode* to_reg_tree();
    bool is_prior(char opreand1, char operand2);
    bool is_operator(char operand);
};

#endif //COMPILER_REGEXP_H
