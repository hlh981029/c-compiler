#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<typeinfo>
#include<unordered_set>
#include<fstream>

namespace cfg
{
	namespace Identify
	{
		enum SymbolIdentify
		{
			Symbol, Nonterminal, Terminal
		};
	}

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

	template<typename T>
	ostream& operator<<(ostream& out, const vector<T*>& vec);

	template<typename T>
	ostream& operator<<(ostream& out, const unordered_set<T*>& vec);

	class Symbol;
	class Production;
	class Terminal;
	class Nonterminal;

	class Symbol
	{
	public:
		string value;
		unordered_set<Terminal*> first_set;
		bool start_as_epsilon;

		Symbol();
		Symbol(string input);
		bool operator==(const Symbol & a);
		virtual int get_id() const;
		friend ostream& operator<<(ostream& out, const Symbol& symbol);

	private:

	};

	class Terminal : public Symbol
	{
	public:
		Terminal();
		Terminal(string input);
		int get_id() const;
	private:

	};

	class Nonterminal : public Symbol
	{
	public:
		unordered_set<Terminal*> follow_set;

		Nonterminal();
		Nonterminal(string input);
		int get_id() const;

	private:
	};

	class Production
	{
	public:
		Nonterminal* left;
		vector<Symbol*> right;

		Production();
		Production(Nonterminal* start, const vector<Symbol*>& symbol);
		void init(Nonterminal* start, const vector<Symbol*>& symbol);
		friend ostream& operator<<(ostream& out, Production production);

	private:
	};

	class ContextFreeGrammar
	{
	public:
		struct Ter_pointer_hash
		{
			size_t operator()(Terminal* input) const {
				std::hash<std::string> hash_fn;
				return hash_fn(input->value);
			}
		};
		struct Ter_pointer_hash_compare
		{
			bool operator()(Terminal* input1, Terminal* input2) const {
				return input1->value == input2->value;
			}
		};
		struct Non_pointer_hash
		{
			size_t operator()(Nonterminal* input) const {
				std::hash<std::string> hash_fn;
				return hash_fn(input->value);
			}
		};
		struct Non_pointer_hash_compare
		{
			bool operator()(Nonterminal* input1, Nonterminal* input2) const {
				return input1->value == input2->value;
			}
		};
		unordered_set<Terminal*, Ter_pointer_hash, Ter_pointer_hash_compare> terminal_set;
		unordered_set<Nonterminal*, Non_pointer_hash, Non_pointer_hash_compare> nonterminal_set;
		unordered_set<Production*> production_set;
		Nonterminal* start_symbol;
		Terminal* end_symbol;

		ContextFreeGrammar();

		void set_first();
		void set_follow();
		void input_productions(string file);
		void add_production(string left, string right);
		void set_start(string s);

		void test_function();

		// deal with the context-free grammar
		// supposed to use dynamic binding
	};

}