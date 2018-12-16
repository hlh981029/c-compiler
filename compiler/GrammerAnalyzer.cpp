#include "GrammerAnalyzer.h"
#include <fstream>
#include <stack>
#include <string>

#define DQ_TEST

GrammerAnalyzer::GrammerAnalyzer(std::vector<hebo::LexicalUnit> output_sequence) {
	this->output_sequence = output_sequence;
#ifdef DQ_TEST
	this->output_sequence[0].name = "id";
	this->output_sequence[1].name = "*";
	this->output_sequence[2].name = "id";
	this->output_sequence[3].name = "+";
	this->output_sequence[4].name = "id";
	this->output_sequence[5].name = "$";
#endif // DQ_TEST
	this->initialization();
	this->root = this->init_tree();
}

void GrammerAnalyzer::initialization() {
	std::ifstream in("to_dq.txt");
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
		production_list[i]->production_formula.push_back(new std::string(temp.substr(start, temp.length() - start)));
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
	return;
}

hebo::LexicalUnit* GrammerAnalyzer::init_tree() {
	std::stack<int> status_stack;
	std::stack<hebo::LexicalUnit*> symbol_stack;
	status_stack.push(0);
	hebo::LexicalUnit* root = new hebo::LexicalUnit();
	while (1) {
		hebo::LexicalUnit* temp_unit = new hebo::LexicalUnit();
		temp_unit->child_node_list = this->output_sequence.begin()->child_node_list;
		temp_unit->morpheme = this->output_sequence.begin()->morpheme;
		temp_unit->name = this->output_sequence.begin()->name;
		temp_unit->value = this->output_sequence.begin()->value;
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
			status_stack.push(std::atoi(temp_str.substr(1, temp_str.length() - 1).c_str()));
			symbol_stack.push(temp_unit);
		}
		else if (this->action_table[temp_status][pos_num][0][0] == 'r') {
			int formula_number = std::atoi(temp_str.substr(1, temp_str.length() - 1).c_str());
			size_t temp_pop_number = this->production_list[formula_number - 1]->production_formula.size() - 1;
			root = new hebo::LexicalUnit();
			root->name = *this->production_list[formula_number - 1]->production_formula[0];
			for (int i = 0; i < temp_pop_number; i++) {
				status_stack.pop();
				root->child_node_list.push_back(symbol_stack.top());
				symbol_stack.pop();
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
		}
		else if (this->action_table[temp_status][pos_num][0][0] == 'a') {
			std::cout << "acc" << std::endl;
			break;
		}
		else {
			std::cout << "Error!" << std::endl;
		}
	}
	return root;
}