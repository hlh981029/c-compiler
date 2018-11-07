#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<set>
#include<vector>
#include<cstdlib>
#include<sstream>
// hlhlsadjfka;fj;laskdj
// the std::ifstream cpp_source had better be set as a member variable, maybe.
namespace hebo
{
	typedef std::string morpheme;
	typedef std::string value;
	std::string int2string(int input)
	{
		std::stringstream trans;
		trans << input;
		return trans.str();
	}
	class DFA
	{
	private:
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
		std::vector<std::string> output_sequence;

		std::ifstream cpp_source;

		int current_memory;
	public:
		DFA(std::string source_file_name, int row_number_ = 10, int column_number_ = 10)
			:current_status(1), current_memory(0), row_number(row_number_), column_number(column_number_)
		{
			cpp_source.open(source_file_name);
			if (!cpp_source.is_open())
			{
				std::cerr << "Not open the source file." << std::endl;
			}
			matrix = new int*[row_number];
			for (int i = 0; i < row_number; i++)
			{
				matrix[i] = new int[column_number];
				for (int j = 0; j < column_number; j++)
				{
					matrix[i][j] = i * 10 + j;
				}
			}
		}

		DFA(DFA& input) :current_status(0)
		{
			row_number = input.row_number;
			column_number = input.column_number;
			matrix = new int*[row_number];
			for (int i = 0; i < row_number; i++)
			{
				matrix[i] = new int[column_number];
				for (int j = 0; j < column_number; j++)
				{
					matrix[i][j] = input.matrix[i][j];
				}
			}
			status_to_pattern = input.status_to_pattern;
		}

		DFA(std::string& dfa_file_name, std::string source_file_name)
		{
			cpp_source.open(source_file_name);
			std::ifstream dfa_file(dfa_file_name);
			if (!cpp_source.is_open() || !dfa_file.is_open())
			{
				std::cerr << "Not open files" << std::endl;
			}
			dfa_file >> row_number >> column_number;
			matrix = new int*[row_number];
			for (int i = 0; i < row_number; i++)
			{
				matrix[i] = new int[column_number];
				for (int j = 0; j < column_number; j++)
				{
					dfa_file >> matrix[i][j];
				}
			}
			int end_status;
			std::string pattern;
			while (dfa_file >> end_status >> pattern)
			{
				status_to_pattern.insert(std::make_pair(end_status, pattern));
				if (pattern == "LINE_NOTE")
				{
					line__note_ = end_status;
				}
				else if (pattern == "LEFT_NOTE")
				{
					left__note_ = end_status;
				}
				else if (pattern == "RIGHT_NOTE")
				{
					right_note_ = end_status;
				}
			}
		}

		~DFA()
		{
			for (int i = 0; i < row_number; i++)
			{
				delete[] matrix[i];
				matrix[i] = nullptr;
			}
			delete[] matrix;
			matrix = nullptr;
			status_to_pattern.clear();
			row_number = 0;
			column_number = 0;
			word_list.clear();
		}

		friend std::ostream& operator<<(std::ostream& my_out, const DFA& dfa)
		{
			for (int i = 0; i < dfa.row_number; i++)
			{
				for (int j = 0; j < dfa.column_number; j++)
				{
					my_out << dfa.matrix[i][j] << ' ';
				}
				my_out << std::endl;
			}
			return my_out;
		}

		/*

		-> means turn into

		input
		the current character
		the current string { member variable }
		the current status { member variable }
		output



		modify
		the current status -> the next status
		the current string -> the next string = the current string + the character { update member variable }
		word_list if dead status and new morpheme then append a (morpheme, value)
		output_sequence if dead status and new morpheme then append a unit
		*/

		//feed a single character from the source file to the dfa matrix and monitor the transition of the status
		auto feed(char ch) -> void
		{
			int next_status = matrix[current_status][ch];
			bool is_dead = (next_status == dead_status);
			bool is_line = (next_status == line__note_);
			bool is_left = (next_status == left__note_);
			if (!(is_dead||is_line||is_left))
			{
				current_string += ch;
				current_status = next_status;
			}
			else if(is_dead)
			{
				update_output_sequence();
				current_string = ch;
				current_status = matrix[init_status][ch];
			}
			else if (is_line)
			{
				deal_with_line_note();
			}
			else if (is_left)
			{
				deal_with_multiplied_note();
			}
		}

		void deal_with_multiplied_note()
		{
			current_status = init_status;
			char ch;
			while (1)
			{
				ch = cpp_source.get();
				current_status = matrix[current_status][ch];
				if (current_status == dead_status)
				{
					current_status = init_status;
				}
				else if (current_status == right_note_)
				{
					break;
				}
			}
			current_status = init_status;
			current_string.clear();
		}


		void deal_with_line_note()
		{
			std::getline(cpp_source, std::string());
			current_string.clear();
			current_status = init_status;
		}

		void update_output_sequence()
		{
			std::string pattern = status_to_pattern[current_status];
			std::string output_string = pattern + "\t" + current_string + "\t";
			if (pattern == "ID")
			{
				output_string += update_word_list();
			}
			else if (pattern == "NUMBER")
			{
				output_string += current_string;
			}
			output_sequence.push_back(output_string);
			current_status = init_status;
			current_string.clear();
		}

		value update_word_list()
		{
			if (!word_list.count(current_string))
			{
				word_list.insert(std::make_pair(current_string, int2string(current_memory += 4)));
			}
			return word_list[current_string];
		}

		void run()
		{
			char ch;
			while ((ch = cpp_source.get()) != -1)
			{
				feed(ch);
			}
		}


		DFA& operator<<(std::ifstream& input)
		{
			char ch;
			while ((ch = input.get()) != -1)
			{
				std::cout << ch;
			}
		}

		void print_current_string()
		{
			std::cout << current_string << std::endl;
		}
		void print_output_sequence()
		{
			for (int i = 0; i < output_sequence.size(); i++)
			{
				std::cout << output_sequence[i] << std::endl;
			}
		}
	};
}
