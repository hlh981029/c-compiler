#include "Nfa.h"
#include <set>
#include <map>
#include <string>
using namespace std;
#pragma once
class NfaToDfa
{
public:
	NfaToDfa(Nfa nfa);
	~NfaToDfa();

	Nfa nfa;
	int* wordlist;

	int** dfa_map;
	int dfa_s;
	int n_dfa_states;
	int n_chars;
	map<int, string> dfa_end;

	set<int> closure(set<int> T);
	set<int> next(int head, int character);
	void transform();
};
