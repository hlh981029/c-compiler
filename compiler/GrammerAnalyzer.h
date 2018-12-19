#pragma once
#include "intput_and_output.hpp"
#include <string>
#include <vector>

class GrammerAnalyzer {
private:
	typedef struct production {
		std::vector<std::string*> production_formula;
		production() {}
	}production;

	std::vector<hebo::LexicalUnit> output_sequence;
	int terminal_number;
	std::string** terminal_list;
	int non_terminal_number;
	std::string** non_terminal_list;
	int production_number;
	production** production_list;
	int table_number;
	std::vector<std::vector<std::string*>> action_table;
	std::vector<std::vector<std::string*>> goto_table;

public:
	GrammerAnalyzer(std::vector<hebo::LexicalUnit>);
	hebo::LexicalUnit* root;

private:
	void initialization();
	hebo::LexicalUnit* init_tree();
	void output_tree(hebo::LexicalUnit*, int);
};