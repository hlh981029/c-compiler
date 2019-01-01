#include "GrammerAnalyzer.h"

void GrammerAnalyzer::action101(hebo::LexicalUnit* root) {
	return;
}

void GrammerAnalyzer::action102(hebo::LexicalUnit* root) {
	root->father->child_node_list[2]->attribute.con_instr = root->father->attribute.con_instr;
	root->father->child_node_list[2]->attribute.break_instr = root->father->attribute.break_instr;
	return;
}

void GrammerAnalyzer::action103(hebo::LexicalUnit* root) {
	return;
}

void GrammerAnalyzer::action104(hebo::LexicalUnit* root) {
	return;
}

void GrammerAnalyzer::action109(hebo::LexicalUnit* root) {
	return;
}

void GrammerAnalyzer::action110(hebo::LexicalUnit* root) {
	return;
}

void GrammerAnalyzer::action111(hebo::LexicalUnit* root) {
	return;
}

void GrammerAnalyzer::action112(hebo::LexicalUnit* root) {
	return;
}

void GrammerAnalyzer::action113(hebo::LexicalUnit* root) {
	this->out_table = &global_symbol_table;
	this->struct_table = &global_struct_table;
	this->function_table = &global_function_table;
	return;
}