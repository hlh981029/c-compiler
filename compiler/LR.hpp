#pragma once
#include"ContextFreeGrammar.hpp"
#include<map>
#include<queue>
#include<assert.h>
#include<sstream>
#include<fstream>
#include<unordered_map>
namespace lr
{
	using std::unordered_set;
	using std::cin;
	using std::endl;
	using std::cout;
	using std::vector;
	using std::map;
	using std::string;
	using std::unordered_map;
	using std::queue;
	class LALR1Item
	{
	public:
		struct Ter_pointer_hash
		{
			size_t operator()(cfg::Terminal* input) const {
				std::hash<std::string> hash_fn;
				return hash_fn(input->value);
			}
		};
		struct Ter_pointer_hash_compare
		{
			bool operator()(cfg::Terminal* input1, cfg::Terminal* input2) const {
				return input1->value == input2->value;
			}
		};


		cfg::Production* production;
		int position;
		std::unordered_set<cfg::Terminal*, Ter_pointer_hash, Ter_pointer_hash_compare> lookaheads;
		bool is_kernel;

		int order;

		LALR1Item();
		LALR1Item(cfg::Production* production_, int position, cfg::Terminal* sentence_ending, int order_);

	};


	class LALR
	{
	public:
		int production_number;
		struct item_pointer_hash
		{
			size_t operator()(LALR1Item* input) const {
				std::hash<std::string> hash_fn;
				string sum = input->production->left->value;
				for each(auto str in input->production->right)
				{
					sum += str->value;
				}
				return hash_fn(sum) + input->position;
			}
		};
		struct item_pointer_hash_compare
		{
			bool operator()(LALR1Item* input1, LALR1Item* input2) const {
				return
					input1->production->left == input2->production->left &&
					input1->production->right == input2->production->right &&
					input1->position == input2->position;
			}
		};

		struct unordered_set_lalr_item_hash
		{
			size_t operator()(unordered_set<LALR1Item*, item_pointer_hash, item_pointer_hash_compare> input) const
			{
				item_pointer_hash hash_func;
				size_t result = 0;
				for each (auto item in input)
				{
					result += hash_func(item);
				}
				return result;
			}
		};

		unordered_set<cfg::Terminal*, cfg::ContextFreeGrammar::Ter_pointer_hash, cfg::ContextFreeGrammar::Ter_pointer_hash_compare> terminal_set;
		unordered_set<cfg::Nonterminal*, cfg::ContextFreeGrammar::Non_pointer_hash, cfg::ContextFreeGrammar::Non_pointer_hash_compare> nonterminal_set;
		unordered_set<LALR1Item*, item_pointer_hash, item_pointer_hash_compare> lr0_item_set;
		LALR1Item* argumented_grammar_start;
		cfg::Nonterminal* start_symbol;

		vector<unordered_set<LALR1Item*, item_pointer_hash, item_pointer_hash_compare>> kernel_status_vector;
		vector<map<cfg::Symbol*, int>> kernel_goto_vector;


		cfg::Terminal* sentence_ending;

		LALR(const cfg::ContextFreeGrammar& context_free_grammar_);
		void get_kernel();

		void LR0_closure(unordered_set<LALR1Item*, item_pointer_hash, item_pointer_hash_compare>& closure_set);
		void LALR_closuer(unordered_set<LALR1Item*, item_pointer_hash, item_pointer_hash_compare>& closure_set);


		LALR();
		~LALR();

		vector<std::pair<LALR1Item*, cfg::Terminal*>> spontaneous_lookaheads_vector;
		vector<std::pair<LALR1Item*, LALR1Item*>> spreading_lookaheads_vector;

		void get_spontaneous_lookaheads_and_spreading_lookaheads();
		void set_spontaneous_lookaheads();
		void spread_lookaheads();

		vector<unordered_set<LALR1Item*, item_pointer_hash, item_pointer_hash_compare>> status_vector;

		void get_full_status_vector();

		vector<cfg::Terminal*> terminal_vector;
		vector<cfg::Nonterminal*> nonterminal_vector;

		map<cfg::Terminal*, int> terminal_to_int_map;
		map<cfg::Nonterminal*, int> nonterminal_to_int_map;

		vector<vector<string>> action_vector;
		vector<vector<int>> go_vector;

		void serialize_symbol();
		void make_action_and_go();
		void output();
	};

	std::ostream& operator<<(std::ostream& out, LALR1Item item);

}
