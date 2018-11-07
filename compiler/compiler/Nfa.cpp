#include "Nfa.h"
using namespace std;


Nfa::Nfa()
{
}

Nfa::Nfa(NFA hlh) {
	this->wordlist = new int[129];
	for (int i = 0; i < 128; i++) {
		wordlist[i] = i;
	}
	wordlist[128] = -1;
	this->nfa_map = new int**[hlh.current_state + 1];
	this->nfa_map[hlh.current_state] = nullptr;
	for (int i = 0; i < hlh.current_state; i++) {
		this->nfa_map[i] = new int*[129];
		this->nfa_map[i][128] = nullptr;
		for (int j = 0; j < 128; j++) {
			int size = hlh.transition[i][j].size();
			if (size == 0) {
				this->nfa_map[i][j] = new int[2];
				this->nfa_map[i][j][1] = -1;
				this->nfa_map[i][j][0] = 0;
			}
			else {
				this->nfa_map[i][j] = new int[size + 1];
				this->nfa_map[i][j][size] = -1;
				for (int k = 0; k < size; k++) {
					this->nfa_map[i][j][k] = hlh.transition[i][j][k];
				}
			}
		}
	}
	this->s = hlh.start;
	this->nfa_end = hlh.end;
}


Nfa::~Nfa() {
}
