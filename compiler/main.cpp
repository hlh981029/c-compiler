#include <iostream>
#include <fstream>
#include "Nfa.h"
#include "Nfa_to_dfa.h"
#include "RegExp.h"
#include "hlhNFA.h"
#include "Min_DFA.cpp"
#include "intput_and_output.hpp"
using namespace std;

int main()
{



	RegExp **exps;
	int n = 3;
	exps = new RegExp*[n]; 
	string data[3][2] = { "aa","a","bb","b","cc","c" };
	string *names = new string[n];
	for (int count = 0; count<n; count++)
	{
		exps[count] = new RegExp(data[count][0]);
		names[count] = data[count][1];
	}
	NFA nfa(exps, names, n);
	nfa.print_diagram();
	cout << endl << endl << endl;
	Nfa mynfa(nfa);
	//for (int i = 0; mynfa.nfa_map[i] != nullptr; i++) {
	//	for (int j = 0; mynfa.nfa_map[i][j] != nullptr; j++) {
	//		int f = 0;
	//		for (int k = 0; mynfa.nfa_map[i][j][k] != -1; k++) {
	//			cout << i << ", " << j << ": " << mynfa.nfa_map[i][j][k] << " ";
	//			f = 1;
	//		}
	//		if (f == 1) {
	//			cout << endl;
	//		}
	//	}
	//}
	NfaToDfa ntd(mynfa);
	ntd.transform();
	/*for (int i = 0; i < ntd.n_chars; i++) {
		for (int j = 0; j < ntd.n_dfa_states; j++) {
			cout << ntd.dfa_map[i][j] << " ";
		}
		cout << endl;
	}*/
	Min_DFA mdfa(ntd.dfa_end, ntd.dfa_map, ntd.dfa_s, ntd.n_dfa_states, ntd.n_chars);
	system("pause");
	return 0;
}