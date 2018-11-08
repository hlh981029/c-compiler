#include <iostream>
#include <fstream>
#include "Nfa.h"
#include "Nfa_to_dfa.h"
#include "RegExp.h"
#include "hlhNFA.h"
#include "Min_DFA.cpp"
#include "intput_and_output.hpp"
using namespace std;
#define HB
int main()
{
#ifdef HB
	hebo::DFA dfa("ans.txt", "test.c");
	dfa.run();
	return 0;
#endif // HB
	RegExp **exps;
	int n = 85;
	exps = new RegExp*[n]; 
	string dig = "\0040\0021\0022\0023\0024\0025\0026\0027\0028\0029\005";
	string ch1 = "\004A\002B\002C\002D\002E\002F\002G\002H\002I\002J\002K\002L\002M\002N\002O\002P\002Q\002R\002S\002T\002U\002V\002W\002X\002Y\002Z";
	string ch2 = "\002a\002b\002c\002d\002e\002f\002g\002h\002i\002j\002k\002l\002m\002n\002o\002p\002q\002r\002s\002t\002u\002v\002w\002x\002y\002z\002_\005";
	string ch = ch1 + ch2;
	string data[][2] = {
		"int", "INT",
		"long", "LONG",
		"short", "SHORT",
		"float", "FLOAT",
		"double", "DOUBLE",
		"char", "CHAR",
		"unsigned", "UNSIGNED",
		"signed", "SIGNED",
		"const", "CONST",
		"void", "VOID",
		"volatile", "VOLATILE",
		"enum", "ENUM",
		"struct", "STRUCT",
		"union", "UNION",
		"if", "IF",
		"else", "ELSE",
		"goto", "GOTO",
		"switch", "SWITCH",
		"case", "CASE",
		"do", "DO",
		"while", "WHILE",
		"for", "FOR",
		"continue", "CONTINUE",
		"break", "BREAK",
		"return", "RETURN",
		"default", "DEFAULT",
		"typedef", "TYPEDEF",
		"auto", "AUTO",
		"register", "REGISTER",
		"extern", "EXTERN",
		"static", "STATIC",
		"sizeof", "SIZEOF",
		"+", "+",
		"-", "-",
		"*", "*",
		"/", "/",
		"%", "%",
		"++", "++",
		"--", "--",
		"==", "==",
		"!=", "!=",
		"<", "<",
		">", ">",
		">=", ">=",
		"<=", "<=",
		"&&", "&&",
		"||", "||",
		"!", "!",
		"&", "&",
		"|", "|",
		"^", "^",
		"<<", "<<",
		">>", ">>",
		"~", "~",
		"=", "=",
		"+=", "+=",
		"-=", "-=",
		"*=", "*=",
		"/=", "/=",
		"%=", "%=",
		"<<=", "<<=",//
		">>=", ">>=",//
		"&=", "&=",//
		"^=", "^=",//
		"|=", "|=",//
		"?", "?",
		":", ":",
		"->", "->",
		"(", "(",
		")", ")",
		"{", "{",
		"}", "}",
		"[", "[",
		"]", "]",
		"\"", "\"",
		"'", "'",
		"/*", "/*",
		"*/", "*/",
		"//", "//",
		";", ";",
		",", ",",
		".", ".",
		dig + dig + "\001", "NUMBER",
		ch + "\004" + ch + "\002" + dig + "\005\001", "ID",
		"\004 \002\t\002\n\005\001", "BLANK"
	};
	string *names = new string[n];
	for (int count = 0; count<n; count++)
	{
		exps[count] = new RegExp(data[count][0]);
		names[count] = data[count][1];
	}
	NFA nfa(exps, names, n);
	//nfa.print_diagram();
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