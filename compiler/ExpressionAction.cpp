#include "GrammerAnalyzer.h"

void GrammerAnalyzer::action1(hebo::LexicalUnit* root) {
	root->father->attribute.addr = this->out_table->get_symbol(root->father->child_node_list[0]->morpheme).address;
	three_address_instruction* no_use = new three_address_instruction();
	no_use->index = this->final_instruction.size();
	no_use->op = "JZ";
	no_use->arg1 = "1";
	no_use->arg2 = "-";
	no_use->result = std::to_string(no_use->index);
	this->final_instruction.push_back(no_use);
	return;
}

void GrammerAnalyzer::action2(hebo::LexicalUnit* root) {
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* assignment = new three_address_instruction();
	assignment->op = "=";
	assignment->arg1 = root->father->child_node_list[0]->morpheme;
	assignment->arg2 = "-";
	assignment->result = root->father->attribute.addr;
	this->final_instruction.push_back(assignment);
	return;
}

void GrammerAnalyzer::action3(hebo::LexicalUnit* root) {
	return;
}

void GrammerAnalyzer::action4(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[1]->attribute.addr;
	return;
}

void GrammerAnalyzer::action5(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[0]->attribute.addr;
	return;
}

void GrammerAnalyzer::action6(hebo::LexicalUnit* root) {
	std::string type = this->out_table->get_symbol(root->father->child_node_list[0]->morpheme).type;
	if (type[type.size() - 1] != ']') {
		this->say_error();
	}
	if (root->father->child_node_list[2]->attribute.type != "int") {
		this->say_error();
	}
	root->father->attribute.type = root->father->attribute.array_info.element_type;
	if (root->father->attribute.type == "int") {
		hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
		this->out_table->put_symbol(temp);
		root->father->attribute.addr = temp.address;
		root->father->attribute.array_info.name = this->out_table->get_symbol(root->father->child_node_list[0]->morpheme).address;
		root->father->attribute.array_info.pos = root->father->child_node_list[2]->attribute.addr;
	}
	else if (root->father->attribute.type.substr(0, 6) == "struct" && root->father->attribute.type[root->father->attribute.type.size() - 1] != ']') {
		std::string name = root->father->child_node_list[0]->morpheme + "$" + root->father->child_node_list[2]->attribute.addr;
		root->father->attribute.addr = this->out_table->get_symbol(name).address;
	}
	three_address_instruction* assignment = new three_address_instruction();
	assignment->op = "*";
	assignment->arg1 = std::to_string(root->father->attribute.array_info.element_width);
	assignment->arg2 = root->father->child_node_list[2]->attribute.addr;
	assignment->result = root->father->attribute.addr;
	this->final_instruction.push_back(assignment);
	return;
}

void GrammerAnalyzer::action7(hebo::LexicalUnit* root) {
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* call = new three_address_instruction();
	call->op = "CALL";
	call->arg1 = root->father->child_node_list[0]->attribute.addr;
	call->arg2 = "-";
	call->result = root->father->attribute.addr;
	this->final_instruction.push_back(call);
	return;
}

void GrammerAnalyzer::action8(hebo::LexicalUnit* root) {
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	if (this->check_type(root->father->child_node_list[0]->attribute.addr, this->parameter_list) == false) {
		this->say_error();
	}
	else {
		three_address_instruction* call = new three_address_instruction();
		call->op = "CALL";
		call->arg1 = root->father->child_node_list[0]->attribute.addr;
		call->arg2 = std::to_string(this->parameter_list.size());
		call->result = root->father->attribute.addr;
		this->final_instruction.push_back(call);
	}
	this->clean_param_list();
	return;
}

void GrammerAnalyzer::action9(hebo::LexicalUnit* root) {
	return;
}

void GrammerAnalyzer::action10(hebo::LexicalUnit* root) {
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* assignment = new three_address_instruction();
	assignment->op = "=";
	assignment->arg1 = root->father->child_node_list[0]->attribute.addr;
	assignment->arg2 = "-";
	assignment->result = root->father->attribute.addr;
	this->final_instruction.push_back(assignment);
	three_address_instruction* add = new three_address_instruction();
	add->op = "++";
	add->arg1 = root->father->child_node_list[0]->attribute.addr;
	add->arg2 = "-";
	add->result = root->father->child_node_list[0]->attribute.addr;
	this->final_instruction.push_back(add);
	return;
}

void GrammerAnalyzer::action11(hebo::LexicalUnit* root) {
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* assignment = new three_address_instruction();
	assignment->op = "=";
	assignment->arg1 = root->father->child_node_list[0]->attribute.addr;
	assignment->arg2 = "-";
	assignment->result = root->father->attribute.addr;
	this->final_instruction.push_back(assignment);
	three_address_instruction* subtract = new three_address_instruction();
	subtract->op = "--";
	subtract->arg1 = root->father->child_node_list[0]->attribute.addr;
	subtract->arg2 = "-";
	subtract->result = root->father->child_node_list[0]->attribute.addr;
	this->final_instruction.push_back(subtract);
	return;
}

void GrammerAnalyzer::action12(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[0]->attribute.addr;
	return;
}

void GrammerAnalyzer::action13(hebo::LexicalUnit* root) {
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* add = new three_address_instruction();
	add->op = "++";
	add->arg1 = root->father->child_node_list[1]->attribute.addr;
	add->arg2 = "-";
	add->result = root->father->child_node_list[1]->attribute.addr;
	this->final_instruction.push_back(add);
	three_address_instruction* assignment = new three_address_instruction();
	assignment->op = "=";
	assignment->arg1 = root->father->child_node_list[1]->attribute.addr;
	assignment->arg2 = "-";
	assignment->result = root->father->attribute.addr;
	this->final_instruction.push_back(assignment);
	return;
}

void GrammerAnalyzer::action14(hebo::LexicalUnit* root) {
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* add = new three_address_instruction();
	add->op = "--";
	add->arg1 = root->father->child_node_list[1]->attribute.addr;
	add->arg2 = "-";
	add->result = root->father->child_node_list[1]->attribute.addr;
	this->final_instruction.push_back(add);
	three_address_instruction* assignment = new three_address_instruction();
	assignment->op = "=";
	assignment->arg1 = root->father->child_node_list[1]->attribute.addr;
	assignment->arg2 = "-";
	assignment->result = root->father->attribute.addr;
	this->final_instruction.push_back(assignment);
	return;
}

void GrammerAnalyzer::action15(hebo::LexicalUnit* root) {
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	if (root->father->child_node_list[0]->attribute.op_value == "-") {
		three_address_instruction* minus = new three_address_instruction();
		minus->op = "MINUS";
		minus->arg1 = root->father->child_node_list[2]->attribute.addr;
		minus->arg2 = "-";
		minus->result = root->father->attribute.addr;
		this->final_instruction.push_back(minus);
	}
	else if (root->father->child_node_list[0]->attribute.op_value == "!") {
		three_address_instruction* fei = new three_address_instruction();
		fei->op = "!";
		fei->arg1 = root->father->child_node_list[2]->attribute.addr;
		fei->arg2 = "-";
		fei->result = root->father->attribute.addr;
		this->final_instruction.push_back(fei);
	}
	else {
		this->say_error();
	}
	return;
}

void GrammerAnalyzer::action16(hebo::LexicalUnit* root) {
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* assignment = new three_address_instruction();
	assignment->op = "=";
	assignment->arg1 = root->father->child_node_list[1]->attribute.width;
	assignment->arg2 = "-";
	assignment->result = root->father->attribute.addr;
	this->final_instruction.push_back(assignment);
	return;
}

void GrammerAnalyzer::action17(hebo::LexicalUnit* root) {
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* assignment = new three_address_instruction();
	assignment->op = "=";
	assignment->arg1 = root->father->child_node_list[2]->attribute.width;
	assignment->arg2 = "-";
	assignment->result = root->father->attribute.addr;
	this->final_instruction.push_back(assignment);
	return;
}

void GrammerAnalyzer::action18(hebo::LexicalUnit* root) {
	root->father->attribute.op_value = "&";
	return;
}

void GrammerAnalyzer::action19(hebo::LexicalUnit* root) {
	root->father->attribute.op_value = "*";
	return;
}

void GrammerAnalyzer::action20(hebo::LexicalUnit* root) {
	root->father->attribute.op_value = "+";
	return;
}

void GrammerAnalyzer::action21(hebo::LexicalUnit* root) {
	root->father->attribute.op_value = "-";
	return;
}

void GrammerAnalyzer::action22(hebo::LexicalUnit* root) {
	root->father->attribute.op_value = "~";
	return;
}

void GrammerAnalyzer::action23(hebo::LexicalUnit* root) {
	root->father->attribute.op_value = "!";
	return;
}

void GrammerAnalyzer::action24(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[0]->attribute.addr;
	return;
}

void GrammerAnalyzer::action25(hebo::LexicalUnit* root) {
	hbst::SymbolItem temp = hbst::SymbolItem("", root->father->child_node_list[1]->attribute.type, 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* assignment = new three_address_instruction();
	assignment->op = "=";
	assignment->arg1 = root->father->child_node_list[0]->attribute.addr;
	assignment->arg2 = "-";
	assignment->result = root->father->attribute.addr;
	this->final_instruction.push_back(assignment);
	return;
}

void GrammerAnalyzer::action26(hebo::LexicalUnit* root) {
	three_address_instruction* param = new three_address_instruction();
	param->op = "PARAM";
	param->arg1 = root->father->child_node_list[0]->attribute.addr;
	param->arg2 = "-";
	param->result = "-";
	this->final_instruction.push_back(param);
	this->parameter_list.push_back(this->out_table->get_symbol_from_address(root->father->child_node_list[0]->attribute.addr).type);
	root->father->attribute.param_number = 1;
	return;
}

void GrammerAnalyzer::action27(hebo::LexicalUnit* root) {
	three_address_instruction* param = new three_address_instruction();
	param->op = "PARAM";
	param->arg1 = root->father->child_node_list[0]->attribute.addr;
	param->arg2 = "-";
	param->result = "-";
	this->final_instruction.push_back(param);
	this->parameter_list.push_back(this->out_table->get_symbol_from_address(root->father->child_node_list[0]->attribute.addr).type);
	root->father->attribute.param_number += 1;
	return;
}