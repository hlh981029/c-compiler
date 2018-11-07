#include "hlhNFA.h"
#include "RegExp.h"
#include <set>
#include <map>
#include <stack>
#include <vector>
#include <string>
#include <iostream>

NFA::NFA(RegExp **exps, std::string *names, int n)
{
    current_state = 2;
    max_state = 1;
    start = 1;
    for(int count = 0; count<n; count++)
    {
        max_state+=(exps[count]->get_suffix_exp().length()*2);
    }
    transition = new std::vector<int>*[max_state];
    for(int count = 0; count<max_state; count++)
    {
        transition[count] = new std::vector<int>[128];
    }
    RegTreeNode *temp;
    RegTreeNode *start_node = new RegTreeNode('\2');
    start_node->start = 1;
    for(int count = 0; count<n; count++)
    {
        temp = (exps[count]->get_reg_tree());
        to_nfa(temp);
        end.insert(std::pair<int, std::string>(temp->end, names[count]));
        transition[1][0].push_back(temp->start);
    }
}

void NFA::to_nfa(RegTreeNode *root)
{
    recurse_to_nfa(root);
}

void NFA::recurse_to_nfa(RegTreeNode *root)
{
    if(root->left != nullptr)
    {
        recurse_to_nfa(root->left);
    }
    if(root->right!= nullptr)
    {
        recurse_to_nfa(root->right);
    }
    if(!is_operator(root->reg_op))
    {
        root->start = current_state++;
        root->end = current_state++;
        transition[root->start][(int)(root->reg_op)].push_back(root->end);
    }
    else if(root->reg_op == '\3')
    {
        root->start = root->left->start;
        root->end = root->right->end;
        transition[root->left->end][0].push_back(root->right->start);
    }
    else if(root->reg_op == '\2')
    {
        root->start = current_state++;
        root->end = current_state++;
        transition[root->start][0].push_back(root->left->start);
        transition[root->start][0].push_back(root->right->start);
        transition[root->left->end][0].push_back(root->end);
        transition[root->right->end][0].push_back(root->end);
    }
    else if(root->reg_op == '\1')
    {
        root->start = current_state++;
        root->end = current_state++;
        transition[root->start][0].push_back(root->left->start);
        transition[root->start][0].push_back(root->end);
        transition[root->left->end][0].push_back(root->left->start);
        transition[root->left->end][0].push_back(root->end);
    }
}

bool NFA::is_operator(char operand)
{
    return operand == '\1' || operand == '\2' || operand == '\3';
}

void NFA::print_diagram()
{
        std::cout << current_state << std::endl;
        for (int i = 0; i < current_state; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                if (!transition[i][j].empty())
                {
                    std::cout << i << '-';
                    if (j == 0) {
						std::cout << "empty";
                    }
                    else
                    {
                        std::cout << char(j);
                    }
                    std::cout << "->[";
                    for (int k = 0; k < transition[i][j].size(); k++) {
                        std::cout << transition[i][j][k] << ",";
                    }
                    std::cout << "]";
                }
            }
            std::cout << std::endl;
        }
}

NFA::~NFA()
{

}

NFA::NFA()
{

}
