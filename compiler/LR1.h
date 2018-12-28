#pragma once
#include<iostream>
#include"ContextFreeGrammar.hpp"
#include<vector>
#include<string>
#include<typeinfo>
#include<unordered_set>
#include<fstream>

namespace lr1
{
	using namespace cfg;
	using std::cin;
	using std::cout;
	using std::endl;

	using std::string;
	using std::vector;
	using std::unordered_set;

	using std::ostream;
	using std::istream;

	using std::fstream;
	using std::ofstream;
	using std::ifstream;

	class LR1Item {
	public:
		Production* production;
		int position;
		vector<Terminal*> forward;
		int productionNum;
		Symbol* expect;
		LR1Item* next;
		

		LR1Item(Production* production, int pnum, int pos = 0);
		~LR1Item();
		bool addForward(Terminal* ter);
		bool addForwards(vector<Terminal*> ters);
		bool operator==(LR1Item &a);
		friend ostream& operator<<(ostream& out, LR1Item iter);
	};

	class LR1ItemSet {
	public:
		vector<LR1Item*> itemset;

		LR1ItemSet(LR1Item* item);
		LR1ItemSet();
		~LR1ItemSet();
		std::pair<bool, bool> addItem(LR1Item* Item);
		bool addItem4NewSet(LR1Item* Item);
		bool operator==(LR1ItemSet& a);
		friend ostream& operator<<(ostream& out, LR1ItemSet iterSet);
};

	class LR1ItemSets {
	private:
		// ContextFreeGrammar grammar;
		// vector<LR1Item*> allItems;
		vector<int> Goline;
		
		void addLine();
		bool Go(LR1ItemSet* s, Symbol* x);
		LR1ItemSet* addItemSet(LR1ItemSet* itemSet);
		void closure(LR1ItemSet* itemSet);
		LR1Item* newNext(LR1Item* item);
	public:
		vector<LR1ItemSet*> itemSets;
		vector<Symbol*> symbols;
		vector<Terminal*> terminals;
		vector<Nonterminal*> nonterminals;
		vector<Production*> productions;
		vector<vector<int>> GO;

		vector<vector<string>> action_table;
		vector<vector<int>> goto_table;

		LR1ItemSets(ContextFreeGrammar grammar);

		int8_t can_merge(int status_1, int status_2);
		void merge_all();
		void merge_go_table(int status_1, int status_2);
		void merge_itemSets(int status_1, int status_2);

		void set_action_and_goto();
		void output();
		~LR1ItemSets();
		void getSets();
	};
}