#pragma once
#include <set>
#include <map>
#include <string>
#include "hlhNFA.h"
using namespace std;
class Nfa
{
public:
	Nfa();
	Nfa(NFA hlh);
	~Nfa();
	int*** nfa_map;
	int s;
	map<int, string> nfa_end;
	int* wordlist;
};
