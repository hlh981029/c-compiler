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
namespace hebo
{
	class LexicalUnit
	{
	public:
		std::string name;
		std::string morpheme;
		std::string value;
		std::vector<LexicalUnit*> child_node_list;
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
		value update_word_list();
		void run();
		DFA& operator<<(std::ifstream& input);
		void print_current_string();
		void print_output_sequence();
	};
}

