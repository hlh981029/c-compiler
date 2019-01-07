#ifndef COMPILER_NFA_H
#define COMPILER_NFA_H

#include <set>
#include <map>
#include <stack>
#include <vector>
#include <string>
#include "RegExp.h"

class NFA
{
public:
    NFA();
    NFA(RegExp **exps, std::string *names, int n);
    ~NFA();
    // 当前状态数
    int current_state;
    // 最大状态数
    int max_state;
    // 状态转换表
    std::vector<int>** transition;
    // 初始状态号
    int start;
    // 结束状态集
    std::map<int, std::string> end;
    // 正则树转NFA
    void to_nfa(RegTreeNode *root);
    // 转NFA调用的递归函数
    void recurse_to_nfa(RegTreeNode *root);
    // 判断是否为操作符
    bool is_operator(char operand);
    // 输出状态转换表到控制台
    void print_diagram();
};


#endif //COMPILER_NFA_H
