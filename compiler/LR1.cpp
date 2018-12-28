#include "LR1.h"
#include<map>
#include<assert.h>
#include<sstream>
namespace lr1{
	using std::map;
	using std::make_pair;
	using std::stringstream;
	LR1Item::LR1Item(Production* production, int pnum, int pos)
	{
		this->production = production;
		this->position = pos;
		this->productionNum = pnum;	
		for (int n = 0; n < this->production->right.size(); n++) {
			if (n == pos) {
				this->expect = this->production->right[n];
				break;
			}
			else if (n == production->right.size() - 1) {
				this->expect = nullptr;
				break;
			}
		}
	}
	LR1Item::~LR1Item()
	{
	}
	bool LR1Item::addForward(Terminal* ter)
	{
		bool have_it = false;
		for (int i = 0; i < this->forward.size(); i++) {
			if (this->forward[i]->value == ter->value) {
				have_it = true;
				return false;
			}
		}
		if (!have_it) {
			this->forward.push_back(ter);
			return true;
		}
		//xiajibajiade
		else {
			std::cout << "addForward exception" << endl;
			return false;
		}
	}
	bool LR1Item::addForwards(vector<Terminal*> ters)
	{
		bool added = false;
		for (int i = 0; i < ters.size(); i++) {
			bool have_it = false;
			for (int j = 0; j < this->forward.size(); j++) {
				if (ters[i]->value == this->forward[j]->value) {
					have_it = true;
					break;
				}
			}
			if (!have_it) {
				this->addForward(ters[i]);
				added = true;
			}
		}
		return added;
	}
	bool LR1Item::operator==(LR1Item & a)
	{
		if (this->production == a.production && this->position == a.position) {
			for (int i = 0; i < a.forward.size(); i++) {
				bool have_it = false;
				for (int j = 0; j < this->forward.size(); j++) {
					if (a.forward[i]->value == this->forward[j]->value) {
						have_it = true;
						break;
					}
				}
				if (!have_it) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}


	LR1ItemSet::LR1ItemSet(LR1Item* item)
	{
		this->itemset.push_back(item);
	}
	LR1ItemSet::LR1ItemSet()
	{
	}
	LR1ItemSet::~LR1ItemSet()
	{
	}
	std::pair<bool, bool> LR1ItemSet::addItem(LR1Item * Item)
	{
		bool have_it = false;
		for (int i = 0; i < this->itemset.size(); i++) {
			if (this->itemset[i]->production == Item->production && this->itemset[i]->position == Item->position) {
				have_it = true;
				bool a = this->itemset[i]->addForwards(Item->forward);
				// first��ʶ״̬���Ƿ����ı䣬second��ʶ�Ƿ�Ӧ��delete Item
				std::pair<bool, bool> p(a, true);
				return p;
			}
		}
		if (!have_it) {
			this->itemset.push_back(Item);
			std::pair<bool, bool> p(true, false);
			return p;
		}
		// xiajibajiade
		else {
			std::cout << "addItem exception" << endl;
			std::pair<bool, bool> p(false, false);
			return p;
		}
		//
	}
	bool LR1ItemSet::addItem4NewSet(LR1Item* Item) {
		this->itemset.push_back(Item);
		return true;
	}
	bool LR1ItemSet::operator==(LR1ItemSet& a)
	{
		if (this->itemset.size() == a.itemset.size()) {
			for (int i = 0; i < this->itemset.size(); i++) {
				bool have_it = false;
				for (int j = 0; j != a.itemset.size(); j++) {
					if (*this->itemset[i] == *a.itemset[j]) {
						have_it = true;
						break;
					}
				}
				if (!have_it) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}


	void LR1ItemSets::addLine()
	{
		this->GO.push_back(this->Goline);
	}
	bool LR1ItemSets::Go(LR1ItemSet* s, Symbol* x)
	{
		LR1ItemSet* newSet = new LR1ItemSet();
		for (int i = 0; i < s->itemset.size(); i++) {
			if (s->itemset[i]->expect && s->itemset[i]->expect == x) {
				if (this->newNext(s->itemset[i])) {
					newSet->addItem4NewSet(s->itemset[i]->next);
				}
				else {
					std::cout << "There is a expect symbol but no next";
				}
			}
		}
		if (newSet->itemset.size() != 0) {
			this->closure(newSet);
			LR1ItemSet* temp = this->addItemSet(newSet);
			bool flag;
			if (temp != newSet) {
				delete newSet;
				flag = false;
			}
			else {
				this->addLine();
				// std::cout << *newSet << "added a line!!" << endl << endl;
				flag = true;
			}
			int from = 0, to = 0, via = 0;
			for (int i = 0; i < this->itemSets.size(); i++) {
				if (*s == *this->itemSets[i]) {
					from = i;
				}
				if (*temp == *this->itemSets[i]) {
					to = i;
				}
			}
			for (int j = 0; j < this->symbols.size(); j++) {
				if (x == this->symbols[j]) {
					via = j;
				}
			}
			this->GO[from][via] = to;
			return flag;
		}
		else {
			delete newSet;
			return false;
		}
	}
	LR1ItemSet* LR1ItemSets::addItemSet(LR1ItemSet* itemSet)
	{
		bool have_it = false;
		for (int i = 0; i < this->itemSets.size(); i++) {
			if (*itemSet == *this->itemSets[i]) {
				have_it = true;
				return this->itemSets[i];
			}
		}
		if (!have_it) {
			this->itemSets.push_back(itemSet);
			return itemSet;
		}
		// xiajibajiade 
		else {
			std::cout << "addItemSet exception" << endl;
			return itemSet;
		}
	}
	void LR1ItemSets::closure(LR1ItemSet* itemSet)
	{
		bool flag = true;
		while (flag) {
			flag = false;
			for (int i = 0; i < itemSet->itemset.size(); i++) {
				if (itemSet->itemset[i]->expect && itemSet->itemset[i]->expect->get_id() == Identify::Nonterminal) {
					for (int j = 0; j < this->productions.size(); j++) {
						if (this->productions[j]->left == itemSet->itemset[i]->expect) {
							LR1Item* newItem = new LR1Item(this->productions[j], j);
							int size = itemSet->itemset[i]->production->right.size();
							if (itemSet->itemset[i]->position == size - 1) {
								newItem->addForwards(itemSet->itemset[i]->forward);
							}
							else {
								int afterPos = itemSet->itemset[i]->position + 1;
								Symbol* after = itemSet->itemset[i]->production->right[afterPos];
								for each (Terminal* f in after->first_set) {
									newItem->addForward(f);
								}
								if (after->start_as_epsilon) {
									newItem->addForwards(itemSet->itemset[i]->forward);
								}
							}
							std::pair<bool, bool> p = itemSet->addItem(newItem);
							if (p.first) {
								flag = true;
							}
							if (p.second) {
								delete newItem;
							}
						}
					}
				}
			}
		}
	}
	LR1Item* LR1ItemSets::newNext(LR1Item* item)
	{
		int sum = item->production->right.size();
		if (item->position < sum) {
			LR1Item* next = new LR1Item(item->production, item->productionNum, item->position + 1);
			next->forward = item->forward;
			item->next = next;
			return next;
		}
		else {
			item->next = nullptr;
			return nullptr;
		}
	}
	LR1ItemSets::LR1ItemSets(ContextFreeGrammar grammar)
	{
		int nSym = 0;
		for each (Terminal* x in grammar.terminal_set) {
			this->terminals.push_back(x);
			this->symbols.push_back(x);
			nSym++;
		}
		for each (Nonterminal* x in grammar.nonterminal_set) {
			this->nonterminals.push_back(x);
			this->symbols.push_back(x);
			nSym++;
		}
		this->Goline = vector<int>(nSym);
		for (int i = 0; i < nSym; i++) {
			this->Goline[i] = -1;
		}
		for each (Production* x in grammar.production_set) {
			this->productions.push_back(x);
		}
		for (int i = 0; i < this->productions.size(); i++) {
			if (this->productions[i]->left == grammar.start_symbol) {
				LR1Item* newItem = new LR1Item(this->productions[i], i);
				newItem->addForward(grammar.end_symbol);
				LR1ItemSet* firstItemSet = new LR1ItemSet(newItem);
				this->itemSets.push_back(firstItemSet);
				this->addLine();
				this->closure(firstItemSet);
				break;
			}
		}
	}
	int8_t LR1ItemSets::can_merge(int status_1, int status_2)
	{
		/*if (itemSets[status_1]->itemset.size() != itemSets[status_2]->itemset.size())
		{
			return 0;
		}
		map<int, int> status_1_equivalence;
		map<int, int> status_2_equivalence;

		int size = itemSets[status_1]->itemset.size();
		for (int i = 0; i < size; i++)
		{
			status_1_equivalence.insert(
				make_pair(
					itemSets[status_1]->itemset[i]->productionNum,
					itemSets[status_1]->itemset[i]->position));
			status_2_equivalence.insert(
				make_pair(
					itemSets[status_2]->itemset[i]->productionNum,
					itemSets[status_2]->itemset[i]->position));
		}
		return status_1_equivalence == status_2_equivalence;*/
		
		if (itemSets[status_1]->itemset.size() != itemSets[status_2]->itemset.size())
		{
			return 0;
		}

		assert(status_2 < status_1);
		assert(itemSets[status_1]->itemset.size() == itemSets[status_2]->itemset.size());

		map<int, int> correspondence;
		int size = itemSets[status_1]->itemset.size();
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (
					itemSets[status_1]->itemset[i]->productionNum ==
					itemSets[status_2]->itemset[j]->productionNum &&
					itemSets[status_1]->itemset[i]->position ==
					itemSets[status_2]->itemset[j]->position)
				{
					correspondence.insert(make_pair(i, j));
				}
			}
		}
		return correspondence.size() == size;
	}
	void LR1ItemSets::merge_all()
	{
		for (int i = 0; i < itemSets.size(); i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (can_merge(i, j))
				{
					merge_go_table(i, j);
					merge_itemSets(i, j);
					i--;
					break;
				}
				assert(GO.size() == itemSets.size());
				
			}
		}
	}
	void LR1ItemSets::merge_go_table(int status_1, int status_2)
	{
		assert(status_2 < status_1);
		for (int i = 0; i < GO.size(); i++)
		{
			for (int j = 0; j < GO[i].size(); j++)
			{
				if (GO[i][j] == status_1)
				{
					GO[i][j] = status_2;
				}
				else if (GO[i][j] > status_1)
				{
					GO[i][j] -= 1;
				}
			}
		}
		GO.erase(GO.begin() + status_1);
	}
	void LR1ItemSets::merge_itemSets(int status_1, int status_2)
	{
		assert(status_2 < status_1);
		assert(itemSets[status_1]->itemset.size() == itemSets[status_2]->itemset.size());
		map<int, int> correspondence;
		int size = itemSets[status_1]->itemset.size();
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (
					itemSets[status_1]->itemset[i]->productionNum ==
					itemSets[status_2]->itemset[j]->productionNum &&
					itemSets[status_1]->itemset[i]->position ==
					itemSets[status_2]->itemset[j]->position)
				{
					correspondence.insert(make_pair(i, j));
				}
			}
		}
		assert(correspondence.size() == size);
		int count = 0;
		for each(auto it in correspondence)
		{
			for each(auto terminal in itemSets[status_1]->itemset[it.first]->forward)
			{
				bool been_in = false;
				for (int i = 0; i < itemSets[status_2]->itemset[it.second]->forward.size(); i++)
				{
					if (itemSets[status_2]->itemset[it.second]->forward[i] == terminal)
					{
						been_in = true;
						break;
					}
				}
				if(!been_in)
				{
					itemSets[status_2]->itemset[it.second]->forward.push_back(terminal);
				}
			}
			count++;
		}
		assert(count == size);
		itemSets.erase(itemSets.begin() + status_1);
	}
	void LR1ItemSets::set_action_and_goto()
	{
		terminals.clear();
		nonterminals.clear();
		for (int i = 0; i < symbols.size(); i++)
		{
			if (symbols[i]->get_id() == cfg::Identify::Terminal)
			{
				terminals.push_back(dynamic_cast<Terminal*>(symbols[i]));
			}
			else
			{
				break;
			}
		}
		for (int i = terminals.size(); i < symbols.size(); i++)
		{
			nonterminals.push_back(dynamic_cast<Nonterminal*>(symbols[i]));
		}



		action_table = vector<vector<string>>(itemSets.size(), vector<string>(terminals.size(), "e"));
		goto_table = vector<vector<int>>(itemSets.size(), vector<int>(nonterminals.size(), -1));

		stringstream ssss;
		
		for (int i = 0; i < itemSets.size(); i++)
		{
			for (int j = 0; j < terminals.size(); j++)
			{
				if (GO[i][j] == -1)
				{
					continue;
				}
				ssss << GO[i][j];
				action_table[i][j] = "s" + ssss.str();
				ssss.str("");
			}
		}
		for (int i = 0; i < itemSets.size(); i++)
		{
			for (int j = 0; j < nonterminals.size(); j++)
			{
				goto_table[i][j] = GO[i][j + terminals.size()];
			}
		}
		map<Terminal*, int> terminal_to_int;
		for (int i = 0; i < terminals.size(); i++)
		{
			terminal_to_int.insert(make_pair(terminals[i], i));
		}

		for (int i = 0; i < itemSets.size(); i++)
		{
			for (int j = 0; j < itemSets[i]->itemset.size(); j++)
			{
				if (itemSets[i]->itemset[j]->production->right.size() == itemSets[i]->itemset[j]->position)
				{
					for (int k = 0; k < itemSets[i]->itemset[j]->forward.size(); k++)
					{
						if (action_table[i][terminal_to_int[itemSets[i]->itemset[j]->forward[k]]] != "e")
						{
							cout << action_table[i][terminal_to_int[itemSets[i]->itemset[j]->forward[k]]] << endl;
							cout << "chong tu" << endl;
							ssss.str("");
							ssss << itemSets[i]->itemset[j]->productionNum;
							action_table[i][terminal_to_int[itemSets[i]->itemset[j]->forward[k]]] += "r" + ssss.str();
							cout << "r" + ssss.str();
						}
						else
						{
							ssss.str("");
							ssss << itemSets[i]->itemset[j]->productionNum;
							action_table[i][terminal_to_int[itemSets[i]->itemset[j]->forward[k]]] = "r" + ssss.str();
						}
						if (itemSets[i]->itemset[j]->production->left->value == "argumented_translation_unit" && itemSets[i]->itemset[j]->position == 1)
						//if (itemSets[i]->itemset[j]->production->left->value == "sp" && itemSets[i]->itemset[j]->position == 1)
						{
							action_table[i][terminal_to_int[itemSets[i]->itemset[j]->forward[k]]] = "acc";
						}
					}
				}
			}
		}

	}
	void LR1ItemSets::output()
	{
		ofstream lalr("lalr.txt");
		lalr << terminals.size() << endl;
		for (int i = 0; i < terminals.size(); i++)
		{
			lalr << *terminals[i] << endl;
		}
		lalr << nonterminals.size() << endl;
		for (int i = 0; i < nonterminals.size(); i++)
		{
			lalr << *nonterminals[i] << endl;
		}
		lalr << productions.size() << endl;
		for (int i = 0; i < productions.size(); i++)
		{
			lalr << *(productions[i]->left) << ' ';
			for (int j = 0; j < productions[i]->right.size(); j++)
			{
				lalr << *(productions[i]->right[j]) << ' ';
			}
			lalr << endl;
		}
		lalr << action_table.size() << endl;
		for (int i = 0; i < action_table.size(); i++)
		{
			assert(terminals.size() == action_table[i].size());
			for (int j = 0; j < terminals.size(); j++)
			{
				lalr << action_table[i][j] << ' ';
			}
			lalr << endl;
		}
		for (int i = 0; i < goto_table.size(); i++)
		{
			assert(nonterminals.size() == goto_table[i].size());
			for (int j = 0; j < nonterminals.size(); j++)
			{
				lalr << goto_table[i][j] << ' ';
			}
			lalr << endl;
		}
	}
	LR1ItemSets::~LR1ItemSets()
	{

	}
	void LR1ItemSets::getSets()
	{
		for (int i = 0; i < this->itemSets.size(); i++) {
			for (int j = 0; j < this->symbols.size(); j++) {
				if (this->symbols[j]->value!="$" && this->Go(this->itemSets[i], this->symbols[j])) {
				}
			}
		}
	}

	ostream & operator<<(ostream & out, LR1Item iter)
	{
		out << iter.production->left->value << "->";
		int i = 0;
		for each (auto sybom_pointer in iter.production->right)
		{
			if (i == iter.position) {
				out << '@' << sybom_pointer->value << ' ';
			}
			else if (i == iter.position - 1) {
				out << sybom_pointer->value << ' ' << '@';
			}
			else {
				out << sybom_pointer->value << ' ';
			}
			i++;
		}
		out << ", ";
		for each (auto sybom_pointer in iter.forward) {
			out << sybom_pointer->value << ' ';
		}
		return out;
	}

	ostream & operator<<(ostream & out, LR1ItemSet iterSet)
	{
		out << "****size: " << iterSet.itemset.size() << " ****" << endl;
		for each (auto item in iterSet.itemset)
		{
			out << *item << endl;
		}
		out << "****************";
		return out;
	}

}


// �ϲ���Ŀ����ʱ�� ��ǰ����ȥ��
// go��ĺϲ� 