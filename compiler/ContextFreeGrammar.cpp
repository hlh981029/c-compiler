#include"ContextFreeGrammar.hpp"
namespace cfg
{

	ostream& operator<<(ostream& out, const Symbol& symbol)
	{
		return out << symbol.value;
	}

	ostream& operator<<(ostream& out, Production production)
	{
		out << production.left->value << " -> ";
		for each (auto sybom_pointer in production.right)
		{
			out << sybom_pointer->value << ' ';
		}
		return out;
	}

	template<typename T>
	ostream& operator<<(ostream& out, const unordered_set<T*>& vec)
	{
		for each (auto x in vec)
		{
			out << *x << "\n";
		}
		return out;
	}

	template<typename T>
	ostream& operator<<(ostream& out, const vector<T*>& vec)
	{

		for each (auto x in vec)
		{
			out << *x << "\t";
		}
		return out;
	}

	Symbol::Symbol()
	{

	}

	Symbol::Symbol(string input) : value(input)
	{

	}

	bool Symbol::operator==(const Symbol & a)
	{
		return value == a.value;
	}

	int Symbol::get_id() const
	{
		return Identify::Symbol;
	}

	Terminal::Terminal() :Symbol()
	{
		start_as_epsilon = false;
	}

	Terminal::Terminal(string input) : Symbol(input)
	{
		start_as_epsilon = false;
	}

	int Terminal::get_id() const
	{
		return Identify::Terminal;
	}

	Nonterminal::Nonterminal() :Symbol()
	{
		start_as_epsilon = false;
	}

	Nonterminal::Nonterminal(string input) : Symbol(input)
	{
		start_as_epsilon = false;
	}

	int Nonterminal::get_id() const
	{
		return Identify::Nonterminal;
	}

	Production::Production()
	{

	}
	Production::Production(Nonterminal* start, const vector<Symbol*>& symbol) :left(start), right(symbol)
	{

	}
	void Production::init(Nonterminal* start, const vector<Symbol*>& symbol)
	{
		left = start;
		right = symbol;
	}

	ContextFreeGrammar::ContextFreeGrammar() :start_symbol(nullptr) {
		Terminal* end = new Terminal("$");
		this->end_symbol = end;
		terminal_set.insert(end);
	}

	void ContextFreeGrammar::test_function()
	{
		Symbol S;

		Terminal* a = new Terminal("a");
		Terminal* b = new Terminal("b");
		Terminal* c = new Terminal("c");
		Terminal* d = new Terminal("d");

		Nonterminal* A = new Nonterminal("A");
		Nonterminal* B = new Nonterminal("B");
		Nonterminal* C = new Nonterminal("C");

		vector<Symbol*> vec;
		vec.push_back(a);
		vec.push_back(B);
		vec.push_back(C);
		Production* p1 = new Production(C, vec);
		vec.push_back(c);
		Production* p2 = new Production(B, vec);
		a->first_set.insert(a);
		b->first_set.insert(b);
		c->first_set.insert(c);
		d->first_set.insert(d);

		A->first_set.insert(a);
		A->first_set.insert(b);
		B->first_set.insert(a);
		B->first_set.insert(c);
		C->first_set.insert(d);

		A->follow_set.insert(b);
		B->follow_set.insert(b);
		C->follow_set.insert(d);



		cout << *p1 << endl;
		cout << *p2 << endl;


		cout << *a << "\nfirst_set:\n" << a->first_set << endl;
		cout << *b << "\nfirst_set:\n" << b->first_set << endl;
		cout << *c << "\nfirst_set:\n" << c->first_set << endl;
		cout << *d << "\nfirst_set:\n" << d->first_set << endl;

		cout
			<< *A
			<< "\nfirst_set:\n" << A->first_set << endl
			<< "\nfollow_set:\n" << A->follow_set << endl;
		cout
			<< *B
			<< "\nfirst_set:\n" << B->first_set << endl
			<< "\nfollow_set:\n" << B->follow_set << endl;
		cout
			<< *C
			<< "\nfirst_set:\n" << C->first_set << endl
			<< "\nfollow_set:\n" << C->follow_set << endl;

		a->value = "aaa";
		b->value = "bbbb";
		c->value = "cccc";
		d->value = "ddddddd";
		A->value = "AAAA";
		B->value = "BB";
		C->value = "CCC";


		cout << *p1 << endl;
		cout << *p2 << endl;


		cout << *a << "\nfirst_set:\n" << a->first_set << endl;
		cout << *b << "\nfirst_set:\n" << b->first_set << endl;
		cout << *c << "\nfirst_set:\n" << c->first_set << endl;
		cout << *d << "\nfirst_set:\n" << d->first_set << endl;

		cout
			<< *A
			<< "\nfirst_set:\n" << A->first_set << endl
			<< "\nfollow_set:\n" << A->follow_set << endl;
		cout
			<< *B
			<< "\nfirst_set:\n" << B->first_set << endl
			<< "\nfollow_set:\n" << B->follow_set << endl;
		cout
			<< *C
			<< "\nfirst_set:\n" << C->first_set << endl
			<< "\nfollow_set:\n" << C->follow_set << endl;

		cout << (p1->left == C) << endl;

		system("pause");
	}

	void ContextFreeGrammar::set_first() {
		// first set for terminal symbols
		unordered_set<Terminal*>::iterator it = terminal_set.begin();
		for (; it != terminal_set.end(); it++) {
			(*it)->first_set.insert((*it));
		}
		// first set for nonterminal symbols
		bool if_more = true;
		while (if_more) {
			if_more = false;
			unordered_set<Production*>::iterator ip = production_set.begin();
			// traverse all the productions
			for (; ip != production_set.end(); ip++) {
				// right is empty
				if ((*ip)->right.size() == 0) {
					(*ip)->left->start_as_epsilon = true;
				}
				else {
					vector<Symbol*>::iterator is = (*ip)->right.begin();
					// traverse all the symbols at the right side
					for (; is != (*ip)->right.end(); is++) {
						unordered_set<Terminal*>::iterator iff = (*is)->first_set.begin();
						// traverse all the symbols in first set of is
						for (; iff != (*is)->first_set.end(); iff++) {
							bool success = (*ip)->left->first_set.insert(*iff).second;
							if (success) {
								if_more = true;
							}
						}
						if (!(*is)->start_as_epsilon) {
							break;
						}
						if (is == (*ip)->right.end() - 1) {
							(*ip)->left->start_as_epsilon = true;
						}
					}
				}
			}
		}
	}

	void ContextFreeGrammar::set_follow() {
		//add $ to the follow set of S
		unordered_set<Terminal*>::iterator e = terminal_set.begin();
		for (; e != terminal_set.end(); e++) {
			if ((*e)->value == "$") {
				start_symbol->follow_set.insert(*e);
			}
		}
		bool flag = true;  //if there's any other elements to add to the follow sets
		while (flag) {
			flag = false;
			//traverse the productions
			unordered_set<Production*>::iterator ip = production_set.begin();
			for (; ip != production_set.end(); ip++) {
				vector<Symbol*>::iterator is = (*ip)->right.begin();
				//traverse the right part of a production
				for (; is != (*ip)->right.end(); is++) {
					//find a nonterminal symbol
					if ((*is)->get_id() == Identify::Nonterminal) {
						//at the end
						if (is == (*ip)->right.end() - 1) {
							unordered_set<Terminal*>::iterator itf = (*ip)->left->follow_set.begin();
							for (; itf != (*ip)->left->follow_set.end(); itf++) {
								bool b = ((Nonterminal*)*is)->follow_set.insert(*itf).second;
								if (b == true) {
									flag = true;
								}
							}
						}
						//not at the end
						else {
							vector<Symbol*>::iterator isn = is + 1;
							unordered_set<Terminal*>::iterator itf = (*isn)->first_set.begin();
							//add elements in first set of the next symbol to this follow set 
							for (; itf != (*isn)->first_set.end(); itf++) {
								bool b = ((Nonterminal*)*is)->follow_set.insert(*itf).second;
								if (b == true) {
									flag = true;
								}
							}
							//if ep in first set of the next symbol, add its next to this next set
							if ((*isn)->start_as_epsilon) {
								if ((*isn)->get_id() != Identify::Nonterminal) {
									cout << "error: the next symble is not a nonterminal symble" << endl;
								}
								unordered_set<Terminal*>::iterator iitf = ((Nonterminal*)*isn)->follow_set.begin();
								for (; iitf != ((Nonterminal*)*isn)->follow_set.end(); iitf++) {
									bool b = ((Nonterminal*)*is)->follow_set.insert(*iitf).second;
									if (b == true) {
										flag = true;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	void ContextFreeGrammar::input_productions(string filename) {
		fstream file;
		file.open(filename, std::ios::in);
		while (!file.eof()) {
			string left, right;
			while (getline(file, left)) {
				if (left != "") {
					break;
				}
			}
			while (getline(file, right)) {
				if (right == ";;") {
					break;
				}
				else {
					add_production(left, right);
				}
			}
		}
		file.close();
	}

	void ContextFreeGrammar::add_production(string left, string right) {
		Production* p = new Production();

		Nonterminal* le = new Nonterminal(left);
		std::pair<unordered_set<Nonterminal*>::iterator, bool> pp;
		pp = nonterminal_set.insert(le);
		if (!pp.second) {
			delete le;
		}
		Nonterminal* l = *(pp.first);

		vector<Symbol*> ri;
		if (right == "") {
			p->init(l, ri);
		}
		else {
			char * buf;
			char* t = strtok_s((char*)right.data(), " ", &buf);
			while (t) {
				string tstr = t;
				if (islower(tstr[0])) {
					Nonterminal* new_nonter = new Nonterminal(tstr);
					std::pair<unordered_set<Nonterminal*>::iterator, bool> ppn;
					ppn = nonterminal_set.insert(new_nonter);
					if (!ppn.second) {
						delete new_nonter;
					}
					ri.push_back(*(ppn.first));
				}
				else {
					Terminal* new_ter = new Terminal(tstr);
					std::pair<unordered_set<Terminal*>::iterator, bool> ppt;
					ppt = terminal_set.insert(new_ter);
					if (!ppt.second) {
						delete new_ter;
					}
					ri.push_back(*(ppt.first));
				}
				t = strtok_s(buf, " ", &buf);
			}
			p->init(l, ri);
		}
		cout << "production:" << *p << endl;
		production_set.insert(p);
	}

	void ContextFreeGrammar::set_start(string s)
	{
		for each (Nonterminal* t in nonterminal_set) {
			if ((*t).value == s) {
				start_symbol = t;
			}
		}
	}
}