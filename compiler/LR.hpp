#pragma once
#include"LRItem.hpp"
#include<map>
#include<queue>
#include<assert.h>
#include<sstream>
#include<fstream>
namespace lr
{
	using std::unordered_set;
	using std::cin;
	using std::endl;
	using std::cout;
	using std::vector;
	using std::map;
	using std::string;
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
		std::unordered_set<cfg::Terminal*, Ter_pointer_hash, Ter_pointer_hash_compare> foreword;


		LALR1Item();
		LALR1Item(cfg::Production* production_, int position);

	};




	class LALR
	{
	public:
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
					input1->position == input2->position  &&
					input1->foreword == input2->foreword;
			}
		};

		unordered_set<cfg::Terminal*, cfg::ContextFreeGrammar::Ter_pointer_hash, cfg::ContextFreeGrammar::Ter_pointer_hash_compare> terminal_set;
		unordered_set<cfg::Nonterminal*, cfg::ContextFreeGrammar::Non_pointer_hash, cfg::ContextFreeGrammar::Non_pointer_hash_compare> nonterminal_set;
		unordered_set<LALR1Item*, item_pointer_hash, item_pointer_hash_compare> item_set;
		LALR1Item* argumented_grammar_start;
		cfg::Nonterminal* start_symbol;

		vector<unordered_set<LALR1Item*, item_pointer_hash, item_pointer_hash_compare>> kernel_status_vector;
		vector<map<cfg::Terminal*, string>> kernel_action_table;
		vector<map<cfg::Nonterminal*, int>> kernel_goto_table;
		
		LALR(const cfg::ContextFreeGrammar& context_free_grammar_);
		void get_kernel();

		void LR0_closure(unordered_set<LALR1Item*, item_pointer_hash, item_pointer_hash_compare>& closure_set);

		LALR();
		~LALR();

	};

	std::ostream& operator<<(std::ostream& out, LALR1Item item);


}
