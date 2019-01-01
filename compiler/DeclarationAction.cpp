#include "GrammerAnalyzer.h"

void GrammerAnalyzer::action201(hebo::LexicalUnit* root) {
	root->father->attribute.type = "void";
	root->father->attribute.width = 0;
	root->father->attribute.if_struct = false;
	return;
}

void GrammerAnalyzer::action202(hebo::LexicalUnit* root) {
	root->father->attribute.type = "char";
	root->father->attribute.width = 1;
	root->father->attribute.if_struct = false;
	return;
}

void GrammerAnalyzer::action203(hebo::LexicalUnit* root) {
	root->father->attribute.type = "int";
	root->father->attribute.width = 4;
	root->father->attribute.if_struct = false;
	return;
}

void GrammerAnalyzer::action204(hebo::LexicalUnit* root) {
	hebo::LexicalUnit* to = root->father;
	hebo::LexicalUnit* from = root->father->child_node_list[0];
	to->attribute.type = from->attribute.type;
	to->attribute.width = from->attribute.width;
	root->father->attribute.if_struct = true;
	return;
}

void GrammerAnalyzer::action211(hebo::LexicalUnit* root) {
	root->father->morpheme = root->father->child_node_list[0]->morpheme;
	root->father->attribute.type = root->father->attribute.type;
	root->father->attribute.width = root->father->attribute.width;
	return;
}

void GrammerAnalyzer::action212(hebo::LexicalUnit* root) {
	root->father->attribute.type = root->father->attribute.type + "[" + root->father->child_node_list[2]->attribute.addr + "]";
	root->father->attribute.width = root->father->attribute.width * std::atoi(root->father->child_node_list[2]->attribute.addr.c_str());
	return;
}

void GrammerAnalyzer::action213(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[1]->attribute.addr;
	root->father->attribute.type = root->father->child_node_list[1]->attribute.type;
	root->father->attribute.width = root->father->child_node_list[1]->attribute.width;
	return;
}

void GrammerAnalyzer::action214(hebo::LexicalUnit* root) {
	root->father->child_node_list[1]->attribute.type = root->father->attribute.type;
	root->father->child_node_list[1]->attribute.width = root->father->attribute.width;
	return;
}

void GrammerAnalyzer::action215(hebo::LexicalUnit* root) {
	root->father->morpheme = root->father->child_node_list[1]->morpheme;
	root->father->attribute.type = root->father->child_node_list[1]->attribute.type;
	root->father->attribute.width = root->father->child_node_list[1]->attribute.width;
	return;
}

void GrammerAnalyzer::action216(hebo::LexicalUnit* root) {
	hebo::LexicalUnit* to = root->father->child_node_list[1];
	hebo::LexicalUnit* from = root->father;
	if (from->attribute.if_struct == true) {
		to->attribute.struct_info = from->attribute.struct_info;
	}
	to->attribute.if_struct = from->attribute.if_struct;
	to->attribute.type = from->attribute.type;
	to->attribute.width = from->attribute.width;
	return;
}

void GrammerAnalyzer::action217(hebo::LexicalUnit* root) {
	hebo::LexicalUnit* child = root->father->child_node_list[1];
	hebo::LexicalUnit* parent = root->father;
	if (child->attribute.if_struct == true) {
		this->out_table->put_symbol(hbst::SymbolItem(child->morpheme, child->attribute.type, 0, child->attribute.width));
	}
	else {
		this->out_table->put_symbol(hbst::SymbolItem(child->morpheme, child->attribute.type, 0, child->attribute.width));
	}
	return;
}

void GrammerAnalyzer::action218(hebo::LexicalUnit* root) {
	hebo::LexicalUnit* child1 = root->father->child_node_list[0];
	hebo::LexicalUnit* child2 = root->father->child_node_list[2];
	if (child1->attribute.if_struct == true) {
		child2->attribute.struct_info = child1->attribute.struct_info;
	}
	child2->attribute.if_struct = child1->attribute.if_struct;
	child2->attribute.type = child1->attribute.type;
	child2->attribute.width = child1->attribute.width;
	return;
}

void GrammerAnalyzer::action219(hebo::LexicalUnit* root) {
	hebo::LexicalUnit* parent = root->father;
	hebo::LexicalUnit* child = root->father->child_node_list[1];
	if (parent->attribute.if_struct == true) {
		child->attribute.struct_info = parent->attribute.struct_info;
	}
	child->attribute.width = parent->attribute.width;
	child->attribute.type = parent->attribute.type;
	child->attribute.if_struct = parent->attribute.if_struct;
	return;
}


void GrammerAnalyzer::action220(hebo::LexicalUnit* root) {
	hebo::LexicalUnit* parent = root->father;
	hebo::LexicalUnit* child_list = root->father->child_node_list[1];
	if (parent->attribute.if_struct == true) {
		child_list->attribute.struct_info = parent->attribute.struct_info;
	}
	child_list->attribute.width = parent->attribute.width;
	child_list->attribute.type = parent->attribute.type;
	child_list->attribute.if_struct = parent->attribute.if_struct;
	return;
}

void GrammerAnalyzer::action221(hebo::LexicalUnit* root) {
	hebo::LexicalUnit* parent = root->father;
	hebo::LexicalUnit* child = root->father->child_node_list[4];
	if (parent->attribute.if_struct == true) {
		child->attribute.struct_info = parent->attribute.struct_info;
	}
	child->attribute.width = parent->attribute.width;
	child->attribute.type = parent->attribute.type;
	child->attribute.if_struct = parent->attribute.if_struct;
	return;
}

void GrammerAnalyzer::action222(hebo::LexicalUnit* root) {
	root->father->attribute.type = root->father->child_node_list[0]->attribute.type;
	return;
}