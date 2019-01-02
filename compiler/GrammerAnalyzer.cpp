#include "GrammerAnalyzer.h"
#include <fstream>
#include <stack>
#include <assert.h>
#include <string>

GrammerAnalyzer::GrammerAnalyzer(std::vector<hebo::LexicalUnit> output_sequence) {
	this->output_sequence = output_sequence;
	this->output_sequence.push_back(hebo::LexicalUnit());
	this->output_sequence[this->output_sequence.size() - 1].name = "$";
	this->output_sequence[this->output_sequence.size() - 1].morpheme = "$";
	this->initialization();
	this->root = this->init_tree();
	this->output_tree(root, 0);
	this->optimize_final_instructions();
}

void GrammerAnalyzer::initialization() {
	std::ifstream in("lalr.txt");
	if (!in.is_open()) {
		std::cout << "Open failed!" << std::endl;
		in.close();
		return;
	}
	std::string temp;
	std::getline(in, temp);
	this->terminal_number = std::atoi(temp.c_str());
	this->terminal_list = new std::string*[this->terminal_number];
	for (int i = 0; i < this->terminal_number; i++) {
		std::getline(in, temp);
		this->terminal_list[i] = new std::string(temp);
	}
	std::getline(in, temp);
	this->non_terminal_number = std::atoi(temp.c_str());
	this->non_terminal_list = new std::string*[this->non_terminal_number];
	for (int i = 0; i < this->non_terminal_number; i++) {
		std::getline(in, temp);
		this->non_terminal_list[i] = new std::string(temp);
	}
	std::getline(in, temp);
	this->production_number = std::atoi(temp.c_str());
	this->transfer_list = new std::vector<std::pair<int, int>>[this->production_number];
	production_list = new production*[this->production_number];
	for (int i = 0; i < this->production_number; i++) {
		std::getline(in, temp);
		production_list[i] = new production();
		int start = 0;
		for (int ii = 0; ii < temp.length(); ii++) {
			if (temp[ii] == ' ') {
				production_list[i]->production_formula.push_back(new std::string(temp.substr(start, ii - start)));
				start = ii + 1;
			}
		}
	}
	std::getline(in, temp);
	this->table_number = std::atoi(temp.c_str());
	for (int i = 0; i < this->table_number; i++) {
		std::vector<std::string*> vec_temp;
		std::getline(in, temp);
		int start = 0;
		for (int ii = 0; ii < temp.length(); ii++) {
			if (temp[ii] == ' ') {
				vec_temp.push_back(new std::string(temp.substr(start, ii - start)));
				start = ii + 1;
			}
		}
		vec_temp.push_back(new std::string(temp.substr(start, temp.length() - start)));
		this->action_table.push_back(vec_temp);
	}
	for (int i = 0; i < this->table_number; i++) {
		std::vector<std::string*> vec_temp;
		std::getline(in, temp);
		int start = 0;
		for (int ii = 0; ii < temp.length(); ii++) {
			if (temp[ii] == ' ') {
				vec_temp.push_back(new std::string(temp.substr(start, ii - start)));
				start = ii + 1;
			}
		}
		vec_temp.push_back(new std::string(temp.substr(start, temp.length() - start)));
		this->goto_table.push_back(vec_temp);
	}
	std::ifstream in2("action.txt");
	if (!in2.is_open()) {
		std::cout << "TEMP Open failed!" << std::endl;
		in2.close();
		return;
	}
	std::string temp2;
	std::getline(in2, temp2);
	this->production_action_number = std::atoi(temp2.c_str());
	std::cout << this->production_action_number << std::endl;
	int temp_cnt = 0;
	for (int i = 0; i < this->production_action_number; i++) {
		std::getline(in2, temp2);
		std::vector<std::string*> temp_vec_p;
		std::vector<std::pair<int, int>> temp_vec_n;
		int start = 0;
		int cnt = 1;
		for (int ii = 0; ii <= temp2.length(); ii++) {
			if (temp2[ii] == ' ' || ii == temp2.length()) {
				std::string* temp_str = new std::string(temp2.substr(start, ii - start));
				if ((*temp_str).substr(0, 6) == "action")
				{
					temp_vec_n.push_back(std::pair<int, int>(cnt - 1, std::atoi((*temp_str).substr(6, (*temp_str).length() - 6).c_str())));
				}
				else {
					temp_vec_p.push_back(temp_str);
				}
				cnt++;
				start = ii + 1;
			}
		}
		for (int ii = 0; ii < this->production_number; ii++) {
			if (compare(this->production_list[ii]->production_formula, temp_vec_p)) {
				temp_cnt++;
				int tar = temp_vec_n.size();
				for (int t = 0; t < tar; t++) {
					this->transfer_list[ii].push_back(*temp_vec_n.begin());
					temp_vec_n.erase(temp_vec_n.begin());
				}
				break;
			}
		}
		
	}
	std::cout << temp_cnt << std::endl;
	return;
}

hebo::LexicalUnit* GrammerAnalyzer::init_tree() {
	std::stack<int> status_stack;
	std::stack<hebo::LexicalUnit*> symbol_stack;
	status_stack.push(0);
	hebo::LexicalUnit* end = new hebo::LexicalUnit();
	end->name = "$";
	symbol_stack.push(end);
	hebo::LexicalUnit* root = new hebo::LexicalUnit();
	int step = 0;
	while (1) {
		std::cout << ++step<<"£º";
		if (step == 10) {
			std::cout << std::endl;
		}
		hebo::LexicalUnit* temp_unit = new hebo::LexicalUnit();
		if (this->output_sequence.size() > 0) {
			temp_unit->child_node_list = this->output_sequence.begin()->child_node_list;
			temp_unit->morpheme = this->output_sequence.begin()->morpheme;
			temp_unit->name = this->output_sequence.begin()->name;
		}
		else {
			temp_unit->name = '$';
		}
		std::string temp_name = temp_unit->name;

		int temp_status = status_stack.top();
		int pos_num = 0;
		for (; pos_num < this->terminal_number; pos_num++) {
			if (*this->terminal_list[pos_num] == temp_name) {
				break;
			}
		}
		std::string temp_str = (*this->action_table[temp_status][pos_num]);
		if (this->action_table[temp_status][pos_num][0][0] == 's') {
			this->output_sequence.erase(this->output_sequence.begin());
			std::cout << this->action_table[temp_status][pos_num][0] << std::endl;
			status_stack.push(std::atoi(temp_str.substr(1, temp_str.length() - 1).c_str()));
			symbol_stack.push(temp_unit);
		}
		else if (this->action_table[temp_status][pos_num][0][0] == 'r') {
			int formula_number = std::atoi(temp_str.substr(1, temp_str.length() - 1).c_str());
			std::cout << "R:" << formula_number << ":";
			for (int i = 0; i < this->production_list[formula_number]->production_formula.size(); i++) {
				std::cout << *this->production_list[formula_number]->production_formula[i]<<' ';
			}
			std::cout << std::endl;
			size_t temp_pop_number = this->production_list[formula_number]->production_formula.size() - 1;
			root = new hebo::LexicalUnit();
			root->name = *this->production_list[formula_number]->production_formula[0];
			std::stack<hebo::LexicalUnit*> temp_symbol_stack;
			for (int i = 0; i < temp_pop_number; i++) {
				status_stack.pop();
				temp_symbol_stack.push(symbol_stack.top());
				symbol_stack.pop();
			}
			int trans_cnt = 0;
			int push_cnt = 0;
			int target_num = -1;
			int formula_num = -1;
			if (this->transfer_list[formula_number].size() > 0) {
				target_num = this->transfer_list[formula_number][trans_cnt].first;
				formula_num = this->transfer_list[formula_number][trans_cnt].second;
			}
			for (int i = 0; i <= temp_pop_number; i++) {
				push_cnt++;
				if (target_num != -1) {
					if (push_cnt == target_num) {
						hebo::LexicalUnit* temp_action_unit = new hebo::LexicalUnit;
						temp_action_unit->if_action = true;
						temp_action_unit->action_num = formula_num;
						temp_action_unit->father = root;
						root->child_node_list.push_back(temp_action_unit);
						if (trans_cnt < this->transfer_list[formula_number].size() - 1) {
							push_cnt++;
							trans_cnt++;
							target_num = this->transfer_list[formula_number][trans_cnt].first;
							formula_num = this->transfer_list[formula_number][trans_cnt].second;
						}
					}
				}
				if (i == temp_pop_number) {
					break;
				}
				temp_symbol_stack.top()->father = root;
				root->child_node_list.push_back(temp_symbol_stack.top());
				temp_symbol_stack.pop();
			}
			symbol_stack.push(root);
			int now_status = status_stack.top();
			int pos_num = 0;
			for (; pos_num < this->non_terminal_number; pos_num++) {
				if (*this->non_terminal_list[pos_num] == root->name) {
					break;
				}
			}
			status_stack.push(std::atoi(this->goto_table[now_status][pos_num]->c_str()));
			std::cout <<'\t'<< status_stack.top() << std::endl;
		}
			else if (this->action_table[temp_status][pos_num][0][0] == 'a') {
			std::cout << "acc" << std::endl;
			break;
		}
			else if (this->action_table[temp_status][pos_num][0][0] == 'e') {
			std::cout << "Standard Error!" << std::endl;
		}
		else
		{
			std::cout << "Error" << std::endl;
			break;
		}
	}
	hebo::LexicalUnit* augmented_root = new hebo::LexicalUnit();
	hebo::LexicalUnit* augmented_action = new hebo::LexicalUnit();
	augmented_root->name = "argumented_translation_unit";
	augmented_root->if_action = false;
	augmented_root->child_node_list.push_back(augmented_action);
	augmented_root->child_node_list.push_back(root);
	augmented_action->if_action = true;
	augmented_action->action_num = 113;
	augmented_action->father = augmented_root;
	root->father = augmented_root;
	root->if_action = false;
	return augmented_root;
}

void GrammerAnalyzer::output_tree(hebo::LexicalUnit* root, int num) {

	for (int i = 0; i < num; i++) {
		std::cout << "  ";
	}
	std::cout << "|-";

	if (root->if_action == true) {
		execute_action(root->action_num, root);
		std::cout << "ACTION" << root->action_num << ": EXECUTED!" << std::endl;
	}
	else if (root->if_action == false) {
		std::cout << root->name << std::endl;
	}
	else {
		std::cout << "SEVERE ERROR" << std::endl;
		system("pause");
	}

	if (root->child_node_list.size() > 0) {
		for (int i = 0; i < root->child_node_list.size(); i++) {
			this->output_tree(root->child_node_list[i], num + 1);
		}
	}
	if (num == 0) {
		std::cout << "acc" << std::endl;
	}
}

bool GrammerAnalyzer::compare(std::vector<std::string*>from, std::vector<std::string*>to) {
	if (from.size() != to.size()) {
		return false;
	}
	for (int i = 0; i < from.size(); i++) {
		if (*from[i] != *to[i]) {
			return false;
		}
	}
	return true;
}

void GrammerAnalyzer::say_error(int error_type, std::string left_type, std::string right_type) {
	std::cout << "NEED A " << right_type << " GET A " << left_type << std::endl;
	system("pause");
	return;
}

bool GrammerAnalyzer::check_type(std::string function_name, std::vector<std::string> parameter_list) {
	return function_table->get_function(function_name).parameter_vector == parameter_list;
}

void GrammerAnalyzer::clean_param_list() {
	this->parameter_list.clear();
	return;
}

void GrammerAnalyzer::optimize_final_instructions()
{
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
	cnt = 0;
	for (int i1 = 0; i1 < this->final_instruction.size(); i1++) {
		three_address_instruction* temp_instruction = this->final_instruction[i1];
		if (temp_instruction->op == "=") {
			std::string temp_name = temp_instruction->result;
			bool flag = false;
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
			if (flag == true) {
				continue;
			}
			else {
				temp_instruction->op = "-";
				std::cout << "NO: " << i1 << " Instructions: Optimized For UnUsed Variables" << std::endl;
				cnt++;
			}
		}
	}
	std::cout << "Optimize instructions: " << cnt << std::endl;
}
