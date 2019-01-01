#include <iostream>
#include <fstream>
#include "Nfa.h"
#include "Nfa_to_dfa.h"
#include "RegExp.h"
#include "hlhNFA.h"
#include "Min_DFA.cpp"
#include "intput_and_output.hpp"
#include "ContextFreeGrammar.hpp"
#include "GrammerAnalyzer.h"
#include "LR1.h"
#include "AsmGenerator.h"
using namespace std;
// #define GRAMMAR
 #define HB
// #define COMPILE_ASM
// #define LEX
// #define LYH

//struct HLH
//{
//	int a;
//};
//
//struct set_hash
//{
//	size_t operator()(unordered_set<int> input)const
//	{
//		int result = 0;
//		for each (int x in input)
//		{
//			result += x;
//			result = result << 2;
//		}
//		return result;
//	}
//};

int main()
{
#ifdef GRAMMAR
	cfg::ContextFreeGrammar a;
	a.input_productions("../productions.txt");
	a.set_start("argumented_translation_unit");
	a.set_first();
	a.set_follow();

	cout << "-----------terminals----------" << endl;
	for each (auto t in a.terminal_set) {
		cout << t->value << endl;
	}
	cout << "------------------------------" << endl;

	cout << "-----------nonterminals----------" << endl;
	for each (auto t in a.nonterminal_set) {
		cout << "*** " << t->value << " ***" << endl;
		cout << "first set: " << t->start_as_epsilon << endl << t->first_set << endl;
		cout << "follow set:" << endl << t->follow_set;
		cout << "***********" << endl << endl;
	}
	cout << "---------------------------------" << endl;
	lr::LALR lalr(a);
	lalr.get_kernel();
	lalr.get_spontaneous_lookaheads_and_spreading_lookaheads();
	lalr.set_spontaneous_lookaheads();
	lalr.spread_lookaheads();
	lalr.get_full_status_vector();
	lalr.serialize_symbol();
	lalr.make_action_and_go();
	lalr.output();
	system("pause");
	return 0;
#endif // GRAMMAR

#ifdef LYH
	cfg::ContextFreeGrammar a;
	a.input_productions("../productions.txt");
	a.set_start("argumented_translation_unit");
	//a.input_productions("../testh.txt");
	//a.set_start("sp");
	a.set_first();
	a.set_follow();
	lr1::LR1ItemSets lr1(a);
	lr1.getSets();
	ofstream hlhsb("2018-12-29.txt");
	int i = 0;
	for each (auto set in lr1.itemSets) {
		hlhsb << "״̬��" << i << endl << *set << endl << endl;
		i++;
	}
	hlhsb << "״̬  \t";
	for each (auto s in lr1.symbols) {
		hlhsb << *s << '\t';
	}
	hlhsb << endl;
	int sts = 0;
	for each (auto v in lr1.GO) {
		hlhsb << "״̬" << sts << "\t";
		for each (auto n in v) {
			hlhsb << n << '\t';
		}
		hlhsb << endl;
		sts++;
	}
	hlhsb << endl;
	for (int i = 0; i < lr1.productions.size(); i++)
	{
		hlhsb << i << '\t' << *lr1.productions[i] << endl;
	}
	//lr1.set_action_and_goto();
	//lr1.output();
	lr1.merge_all();
	lr1.set_action_and_goto();
	lr1.output();
	std::system("pause");

#endif // LYH


#ifdef HB

	hebo::DFA dfa("ans.txt", "test.c");
	dfa.run();
	GrammerAnalyzer* grammer_analyzer = new GrammerAnalyzer(dfa.output_sequence);
    AssemblyGenerator asmgen;
    asmgen.global_symbol_table = grammer_analyzer->out_table;
    asmgen.function_table = grammer_analyzer->function_table;
    asmgen.struct_table = grammer_analyzer->struct_table;
    asmgen.final_instruction = &grammer_analyzer->final_instruction;
    //asmgen.generate_example();
    asmgen.generate_asm();
#ifdef COMPILE_ASM
    system("compile_asm.bat");
    system("pause");
#endif // COMPILE_ASM
	return 0;
#endif // HB

#ifdef LEX
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
		"++", "INC_OP",
		"--", "DEC_OP",
		"==", "EQ_OP",
		"!=", "NE_OP",
		"<", "<",
		">", ">",
		">=", "GE_OP",
		"<=", "LE_OP",
		"&&", "AND_OP",
		"||", "OR_OP",
		"!", "!",
		"&", "&",
		"|", "|",
		"^", "^",
		"<<", "LEFT_OP",
		">>", "RIGHT_OP",
		"~", "~",
		"=", "=",
		"+=", "ADD_ASSIGN",
		"-=", "SUB_ASSIGN",
		"*=", "MUL_ASSIGN",
		"/=", "DIV_ASSIGN",
		"%=", "MOD_ASSIGN",
		"<<=", "LEFT_ASSIGN",
		">>=", "RIGHT_ASSIGN",
		"&=", "AND_ASSIGN",
		"^=", "XOR_ASSIGN",
		"|=", "OR_ASSIGN",
		"?", "?",
		":", ":",
		"->", "PTR_OP",
		"(", "(",
		")", ")",
		"{", "{",
		"}", "}",
		"[", "[",
		"]", "]",
		"\"", "\"",//
		"'", "'",
		"/*", "/*",//
		"*/", "*/",//
		"//", "//",//
		";", ";",
		",", ",",
		".", ".",
		dig + dig + "\001", "CONSTANT",
		ch + "\004" + ch + "\002" + dig + "\005\001", "IDENTIFIER",
		"\004 \002\t\002\n\005\001", "BLANK"//
	};
	string *names = new string[n];
	for (int count = 0; count < n; count++)
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
#endif // LEX

	return 0;
	}