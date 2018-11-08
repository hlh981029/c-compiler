#include "Nfa_to_dfa.h"
#include "Nfa.h"
#include <stack>
#include <set>
#include <map>
#include <string>
#include <iostream>
using namespace std;

class Dstate {
public:
	int index;
	set<int>* state;
	bool marked;
	friend bool operator<(const Dstate& former, const Dstate& input) {
		return former.index < input.index;
	}
	Dstate() {
		this->index = -1;
		this->marked = false;
	}
	Dstate(const Dstate& input) {
		this->index = input.index;
		this->state = input.state;
		this->marked = input.marked;
	}
};

NfaToDfa::NfaToDfa(Nfa nfa) {
	this->nfa = nfa;
	this->wordlist = nfa.wordlist;
	int i, j;
	for (i = 0; nfa.nfa_map[i] != nullptr; i++);
	for (j = 0; nfa.wordlist[j] != -1; j++);
	this->dfa_map = new int*[j];
	for (int t = 0; t < j; t++) {
		dfa_map[t] = new int[i];
		for (int tt = 0; tt < i; tt++) {
			dfa_map[t][tt] = 0;
		}
	}
}


NfaToDfa::~NfaToDfa() {
}

set<int> NfaToDfa::closure(set<int> T) {
	stack<int> st;
	set<int> closure = T;
	for (set<int>::iterator iter = T.begin(); iter != T.end(); iter++) {
		st.push(*iter);
	}
	while (!st.empty()) {
		int t = st.top();
		st.pop();
		for (int i = 0; this->nfa.nfa_map[t][0][i] != -1; i++) {
			int tt = this->nfa.nfa_map[t][0][i];
			if (tt != 0 && closure.insert(this->nfa.nfa_map[t][0][i]).second) {
				st.push(this->nfa.nfa_map[t][0][i]);
			}
		}
	}
	return closure;
}

set<int> NfaToDfa::next(int head, int character) {
	set<int> ne;
	for (int i = 0; this->nfa.nfa_map[head][character][i] != -1; i++) {
		int t = this->nfa.nfa_map[head][character][i];
		if (t != 0) {
			ne.insert(t);
		}
	}
	return ne;
}

void NfaToDfa::transform() {

	set<Dstate> dfa_states;

	set<int> s0;
	s0.insert(this->nfa.s);
	Dstate s;
	s.index = 1;
	s.state = new set<int>(closure(s0));
	s.marked = false;
	dfa_states.insert(s);
	this->dfa_s = 1;
	int index = 2;
	for (map<int, string>::iterator e = nfa.nfa_end.begin(); e != nfa.nfa_end.end(); e++) {
		if ((*(s.state)).find((*e).first) != (*(s.state)).end()) {
			dfa_end.insert(pair<int, string>(s.index, (*e).second));
		}
	}
	for (set<Dstate>::iterator iter = dfa_states.begin(); iter != dfa_states.end(); iter++) {
		if (!(*iter).marked) {
			Dstate temp = (*iter);
			dfa_states.erase(*iter);
			temp.marked = true;
			dfa_states.insert(temp);
			for (int i = 1; wordlist[i] != -1; i++) {
				set<int> temp_next;
				for (set<int>::iterator j = (*(temp.state)).begin(); j != (*(temp.state)).end(); j++) {
					set<int> temp_j_next = next(*j, wordlist[i]);
					for (set<int>::iterator m = temp_j_next.begin(); m != temp_j_next.end(); m++) {
						temp_next.insert(*m);
					}
				}
				if (temp_next.size() == 0) {
					continue;
				}
				set<int> U = closure(temp_next);
				bool have = false;
				Dstate newstate;
				for (set<Dstate>::iterator j = dfa_states.begin(); j != dfa_states.end(); j++) {
					set<int> thestate = *(*j).state;
					if (U == thestate) {
						have = true;
						newstate = *j;
						break;
					}
				}
				if (!have) {
					newstate.index = index;
					newstate.state = new set<int>(U);
					newstate.marked = false;
					for (map<int, string>::iterator e = nfa.nfa_end.begin(); e != nfa.nfa_end.end(); e++) {
						if (U.find((*e).first) != U.end()) {
							dfa_end.insert(pair<int, string>(newstate.index, (*e).second));
						}
					}
					dfa_states.insert(newstate);
					/*for (set<Dstate>::iterator it = dfa_states.begin(); it != dfa_states.end(); it++) {
						cout << "dfa state " << (*it).index << ": ";
						for (set<int>::iterator pr = (*(*it).state).begin(); pr != (*(*it).state).end(); pr++) {
							cout << *pr << " ";
						}
						cout << endl;
					}
					cout << endl;*/
					index++;
				}
				dfa_map[wordlist[i]][temp.index] = newstate.index;
			}
			iter = dfa_states.begin();
		}
	}
	this->n_dfa_states = index;
	int chars;
	for (chars = 0; wordlist[chars] != -1; chars++);
	this->n_chars = chars;
	int **temp_map = new int*[n_chars];
	for (int i = 0; i < n_chars; i++) {
		temp_map[i] = new int[n_dfa_states];
		for (int j = 0; j < n_dfa_states; j++) {
			temp_map[i][j] = dfa_map[i][j];
		}
	}
	dfa_map = temp_map;
}
