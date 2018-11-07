#include "RegExp.h"
#include <stack>
#include <iostream>
#include <string>

RegExp::RegExp(std::string exp, int mode)
{
    if(mode == 0)
    {
        infix_exp = exp;
        reg_tree = nullptr;
        suffix_exp = to_suffix();
        reg_tree = to_reg_tree();
    }
    else if(mode == 1)
    {
        infix_exp = exp;
        suffix_exp = exp;
        reg_tree = to_reg_tree();
    }

}

std::string RegExp::get_suffix_exp()
{
    return suffix_exp;
}

RegTreeNode* RegExp::get_reg_tree()
{
    return reg_tree;
}

std::string RegExp::to_suffix()
{
    for(int count = 0; count < infix_exp.length()-1; count++)
    {
        if(!is_operator(infix_exp[count]) && !is_operator(infix_exp[count + 1]) && infix_exp[count + 1] != '\5' && infix_exp[count] != '\4')
        {
            infix_exp.insert(count + 1, 1, '\3');
            count++;
        }
        else if(infix_exp[count]=='\1' && !is_operator(infix_exp[count + 1]) && infix_exp[count + 1] != '\5' )
        {
            infix_exp.insert(count + 1, 1, '\3');
            count++;
        }
    }
    std::stack<char> operator_stack;
    std::string suffix;
    for(int count = 0; count < infix_exp.length(); count++)
    {
        if(is_operator(infix_exp[count]))
        {
            if(!operator_stack.empty() && !is_prior(operator_stack.top(), infix_exp[count]))
            {
                while(!operator_stack.empty()&&operator_stack.top()!='\4')
                {
                    suffix.append(1, operator_stack.top());
                    operator_stack.pop();
                }
            }
            operator_stack.push(infix_exp[count]);
        }
        else if(infix_exp[count] == '\4')
        {
            operator_stack.push(infix_exp[count]);
        }
        else if(infix_exp[count] == '\5')
        {
            while(operator_stack.top() != '\4')
            {
                suffix.append(1, operator_stack.top());
                operator_stack.pop();
            }
            operator_stack.pop();
        }
        else
        {
            suffix.append(1, infix_exp[count]);
        }
    }
    while(!operator_stack.empty())
    {
        suffix.append(1, operator_stack.top());
        operator_stack.pop();
    }
    return suffix;
}

RegTreeNode* RegExp::to_reg_tree()
{
    std::stack<RegTreeNode*> node_stack;
    RegTreeNode *temp, *left_child, *right_child;
    for(int count = 0; count<suffix_exp.length(); count++)
    {
        temp = new RegTreeNode(suffix_exp[count]);
        if(is_operator(suffix_exp[count]))
        {
            if(suffix_exp[count] != '\1')
            {
                right_child = node_stack.top();
                node_stack.pop();
                temp->right = right_child;
            }
            left_child = node_stack.top();
            node_stack.pop();
            temp->left = left_child;
        }
        node_stack.push(temp);
    }
    return node_stack.top();
}

bool RegExp::is_prior(char opreand1, char operand2)
{
    if(operand2 == '\1')
    {
        return opreand1 != '\1';
    }
    else if(operand2 == '\2')
    {
        return !(opreand1 == '\1' || opreand1 == '\2');
    }
    else
    {
        return false;
    }
}

bool RegExp::is_operator(char operand)
{
    return operand == '\1' || operand == '\2' || operand == '\3';
}

void RegExp::get_explicit_suffix_exp()
{
    for(int count = 0; count<suffix_exp.length(); count++)
    {
        switch(suffix_exp[count]){
            case '\1': std::cout<<'*'; break;
            case '\2': std::cout<<'|'; break;
            case '\3': std::cout<<'.'; break;
            case '\4': std::cout<<'('; break;
            case '\5': std::cout<<')'; break;
            default: std::cout<<suffix_exp[count]; break;
        }
    }
}