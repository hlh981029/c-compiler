#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<set>
#include<vector>
#include<cstdlib>
#include<sstream>
#include <iomanip>
#include "SymbolTable.hpp"
namespace hebo
{
	typedef struct {
		std::string name;
		std::string element_type;
		std::string pos;
		int element_width;
		std::vector<std::string> element_addr;
	}array_info;
	typedef struct {

	}struct_info;
	class LexicalUnit
	{
	public:
		std::string name;
		bool if_action;
		int action_num;
		std::string morpheme;
		struct attribute {
			int width;
			std::string type;
			std::string addr;
			int const_value;

			std::string op_value;
			bool if_struct;

			array_info array_info;
			struct_info struct_info;

			int param_number;

			int instr;
			int next_instr;
			int true_instr;
			int false_instr;
			int con_instr;
			int break_instr;
		} attribute;
		std::vector<LexicalUnit*> child_node_list;
		LexicalUnit* father;

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
	typedef std::string morpheme;
	typedef std::string value;
	std::string uint2string(unsigned int  input);
	int string2int(const std::string& input);
	class DFA
	{
		const static int dead_status = 0;
		int init_status;
		int line__note_;
		int left__note_;
		int right_note_;
		int current_status;
		std::string current_string;

		int** matrix;
		int row_number;
		int column_number;
		std::map<int, std::string> status_to_pattern;//end status to pattern
		// Four data above should be given.

		std::map<morpheme, value> word_list;//morpheme to value

		std::ifstream cpp_source;

		int current_memory;
	public:
		DFA(std::string source_file_name, int row_number_ = 10, int column_number_ = 10);
		DFA(DFA& input);
		DFA(std::string dfa_file_name, std::string source_file_name);
		~DFA();
		std::vector<LexicalUnit> output_sequence;
		friend std::ostream& operator<<(std::ostream& my_out, const DFA& dfa);
		auto feed(char ch) -> void;
		void deal_with_multiplied_note();
		void deal_with_line_note();
		void update_output_sequence();
		void run();
		DFA& operator<<(std::ifstream& input);
		void print_current_string();
		void print_output_sequence(std::ostream& output);
	};
}

