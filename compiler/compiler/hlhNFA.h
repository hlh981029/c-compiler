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
    int current_state;
    int max_state;
    std::vector<int>** transition;
    int start;
    std::map<int, std::string> end;
    void to_nfa(RegTreeNode *root);
    void recurse_to_nfa(RegTreeNode *root);
    bool is_operator(char operand);
    void print_diagram();
};


#endif //COMPILER_NFA_H
