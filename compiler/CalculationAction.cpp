#include "GrammerAnalyzer.h"

void GrammerAnalyzer::action401(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[0]->attribute.addr;
	root->father->attribute.type = root->father->child_node_list[0]->attribute.type;
	root->father->attribute.array_info.name = root->father->child_node_list[0]->attribute.array_info.name;
	root->father->attribute.array_info.pos = root->father->child_node_list[0]->attribute.array_info.pos; 
	return;
}

void GrammerAnalyzer::action402(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[0]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[0]->attribute.type, "int");
		return;
	}
	if (root->father->child_node_list[2]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[2]->attribute.type, "int");
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* multiply = new three_address_instruction();
	multiply->index = this->final_instruction.size();
	multiply->op = "*";
	multiply->arg1 = root->father->child_node_list[0]->attribute.addr;
	multiply->arg2 = root->father->child_node_list[2]->attribute.addr;
	multiply->result = root->father->attribute.addr;
	this->final_instruction.push_back(multiply);
	root->father->attribute.type = "int";
	return;
}

void GrammerAnalyzer::action403(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[0]->attribute.type != "int" ) {
		this->say_error(1, root->father->child_node_list[0]->attribute.type, "int");
		return;
	}
	if (root->father->child_node_list[2]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[2]->attribute.type, "int");
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* divide = new three_address_instruction();
	divide->index = this->final_instruction.size();
	divide->op = "/";
	divide->arg1 = root->father->child_node_list[0]->attribute.addr;
	divide->arg2 = root->father->child_node_list[2]->attribute.addr;
	divide->result = root->father->attribute.addr;
	this->final_instruction.push_back(divide);
	root->father->attribute.type = "int";
	return;
}

void GrammerAnalyzer::action404(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[0]->attribute.type != "int" ) {
		this->say_error(1, root->father->child_node_list[0]->attribute.type, "int");
		return;
	}
	if (root->father->child_node_list[2]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[2]->attribute.type, "int");
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* mo = new three_address_instruction();
	mo->index = this->final_instruction.size();
	mo->op = "%";
	mo->arg1 = root->father->child_node_list[0]->attribute.addr;
	mo->arg2 = root->father->child_node_list[2]->attribute.addr;
	mo->result = root->father->attribute.addr;
	this->final_instruction.push_back(mo);
	root->father->attribute.type = "int";
	return;
}

void GrammerAnalyzer::action405(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[0]->attribute.addr;
	root->father->attribute.type = root->father->child_node_list[0]->attribute.type;
	root->father->attribute.array_info.name = root->father->child_node_list[0]->attribute.array_info.name;
	root->father->attribute.array_info.pos = root->father->child_node_list[0]->attribute.array_info.pos;
	return;
}

void GrammerAnalyzer::action406(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[0]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[0]->attribute.type, "int");
		return;
	}
	if (root->father->child_node_list[2]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[2]->attribute.type, "int");
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* add = new three_address_instruction();
	add->index = this->final_instruction.size();
	add->op = "+";
	add->arg1 = root->father->child_node_list[0]->attribute.addr;
	add->arg2 = root->father->child_node_list[2]->attribute.addr;
	add->result = root->father->attribute.addr;
	this->final_instruction.push_back(add);
	root->father->attribute.type = "int";
	return;
}

void GrammerAnalyzer::action407(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[0]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[0]->attribute.type, "int");
		return;
	}
	if (root->father->child_node_list[2]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[2]->attribute.type, "int");
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* subtract = new three_address_instruction();
	subtract->index = this->final_instruction.size();
	subtract->op = "-";
	subtract->arg1 = root->father->child_node_list[0]->attribute.addr;
	subtract->arg2 = root->father->child_node_list[2]->attribute.addr;
	subtract->result = root->father->attribute.addr;
	this->final_instruction.push_back(subtract);
	root->father->attribute.type = "int";
	return;
}

void GrammerAnalyzer::action408(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[0]->attribute.addr;
	root->father->attribute.type = root->father->child_node_list[0]->attribute.type;
	root->father->attribute.array_info.name = root->father->child_node_list[0]->attribute.array_info.name;
	root->father->attribute.array_info.pos = root->father->child_node_list[0]->attribute.array_info.pos;
	return;
}

void GrammerAnalyzer::action409(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[0]->attribute.addr;
	root->father->attribute.type = root->father->child_node_list[0]->attribute.type;
	root->father->attribute.array_info.name = root->father->child_node_list[0]->attribute.array_info.name;
	root->father->attribute.array_info.pos = root->father->child_node_list[0]->attribute.array_info.pos;
	return;
}

void GrammerAnalyzer::action410(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[0]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[0]->attribute.type, "int");
		return;
	}
	if (root->father->child_node_list[2]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[2]->attribute.type, "int");
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* compare = new three_address_instruction();
	compare->index = this->final_instruction.size();
	compare->op = "JL";
	compare->arg1 = root->father->child_node_list[0]->attribute.addr;
	compare->arg2 = root->father->child_node_list[2]->attribute.addr;
	compare->result = std::to_string(compare->index + 3);
	this->final_instruction.push_back(compare);
	three_address_instruction* assign_false = new three_address_instruction();
	assign_false->index = this->final_instruction.size();
	assign_false->op = "=";
	assign_false->arg1 = "0";
	assign_false->arg2 = "-";
	assign_false->result = root->father->attribute.addr;
	this->final_instruction.push_back(assign_false);
	three_address_instruction* jump = new three_address_instruction();
	jump->index = this->final_instruction.size();
	jump->op = "JMP";
	jump->arg1 = "-";
	jump->arg2 = "-";
	jump->result = std::to_string(jump->index + 2);
	this->final_instruction.push_back(jump);
	three_address_instruction* assign_true = new three_address_instruction();
	assign_true->index = this->final_instruction.size();
	assign_true->op = "=";
	assign_true->arg1 = "1";
	assign_true->arg2 = "-";
	assign_true->result = root->father->attribute.addr;
	this->final_instruction.push_back(assign_true);
	root->father->attribute.type = "int";
	return;
}

void GrammerAnalyzer::action411(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[0]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[0]->attribute.type, "int");
		return;
	}
	if (root->father->child_node_list[2]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[2]->attribute.type, "int");
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* compare = new three_address_instruction();
	compare->index = this->final_instruction.size();
	compare->op = "JG";
	compare->arg1 = root->father->child_node_list[0]->attribute.addr;
	compare->arg2 = root->father->child_node_list[2]->attribute.addr;
	compare->result = std::to_string(compare->index + 3);
	this->final_instruction.push_back(compare);
	three_address_instruction* assign_false = new three_address_instruction();
	assign_false->index = this->final_instruction.size();
	assign_false->op = "=";
	assign_false->arg1 = "0";
	assign_false->arg2 = "-";
	assign_false->result = root->father->attribute.addr;
	this->final_instruction.push_back(assign_false);
	three_address_instruction* jump = new three_address_instruction();
	jump->index = this->final_instruction.size();
	jump->op = "JMP";
	jump->arg1 = "-";
	jump->arg2 = "-";
	jump->result = std::to_string(jump->index + 2);
	this->final_instruction.push_back(jump);
	three_address_instruction* assign_true = new three_address_instruction();
	assign_true->index = this->final_instruction.size();
	assign_true->op = "=";
	assign_true->arg1 = "1";
	assign_true->arg2 = "-";
	assign_true->result = root->father->attribute.addr;
	this->final_instruction.push_back(assign_true);
	root->father->attribute.type = "int";
	return;
}

void GrammerAnalyzer::action412(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[0]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[0]->attribute.type, "int");
		return;
	}
	if (root->father->child_node_list[2]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[2]->attribute.type, "int");
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* compare = new three_address_instruction();
	compare->index = this->final_instruction.size();
	compare->op = "JLE";
	compare->arg1 = root->father->child_node_list[0]->attribute.addr;
	compare->arg2 = root->father->child_node_list[2]->attribute.addr;
	compare->result = std::to_string(compare->index + 3);
	this->final_instruction.push_back(compare);
	three_address_instruction* assign_false = new three_address_instruction();
	assign_false->index = this->final_instruction.size();
	assign_false->op = "=";
	assign_false->arg1 = "0";
	assign_false->arg2 = "-";
	assign_false->result = root->father->attribute.addr;
	this->final_instruction.push_back(assign_false);
	three_address_instruction* jump = new three_address_instruction();
	jump->index = this->final_instruction.size();
	jump->op = "JMP";
	jump->arg1 = "-";
	jump->arg2 = "-";
	jump->result = std::to_string(jump->index + 2);
	this->final_instruction.push_back(jump);
	three_address_instruction* assign_true = new three_address_instruction();
	assign_true->index = this->final_instruction.size();
	assign_true->op = "=";
	assign_true->arg1 = "1";
	assign_true->arg2 = "-";
	assign_true->result = root->father->attribute.addr;
	this->final_instruction.push_back(assign_true);
	root->father->attribute.type = "int";
	return;
}

void GrammerAnalyzer::action413(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[0]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[0]->attribute.type, "int");
		return;
	}
	if (root->father->child_node_list[2]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[2]->attribute.type, "int");
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* compare = new three_address_instruction();
	compare->index = this->final_instruction.size();
	compare->op = "JGE";
	compare->arg1 = root->father->child_node_list[0]->attribute.addr;
	compare->arg2 = root->father->child_node_list[2]->attribute.addr;
	compare->result = std::to_string(compare->index + 3);
	this->final_instruction.push_back(compare);
	three_address_instruction* assign_false = new three_address_instruction();
	assign_false->index = this->final_instruction.size();
	assign_false->op = "=";
	assign_false->arg1 = "0";
	assign_false->arg2 = "-";
	assign_false->result = root->father->attribute.addr;
	this->final_instruction.push_back(assign_false);
	three_address_instruction* jump = new three_address_instruction();
	jump->index = this->final_instruction.size();
	jump->op = "JMP";
	jump->arg1 = "-";
	jump->arg2 = "-";
	jump->result = std::to_string(jump->index + 2);
	this->final_instruction.push_back(jump);
	three_address_instruction* assign_true = new three_address_instruction();
	assign_true->index = this->final_instruction.size();
	assign_true->op = "=";
	assign_true->arg1 = "1";
	assign_true->arg2 = "-";
	assign_true->result = root->father->attribute.addr;
	this->final_instruction.push_back(assign_true);
	root->father->attribute.type = "int";
	return;
}

void GrammerAnalyzer::action414(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[0]->attribute.addr;
	root->father->attribute.type = root->father->child_node_list[0]->attribute.type;
	root->father->attribute.array_info.name = root->father->child_node_list[0]->attribute.array_info.name;
	root->father->attribute.array_info.pos = root->father->child_node_list[0]->attribute.array_info.pos;
	return;
}

void GrammerAnalyzer::action415(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[0]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[0]->attribute.type, "int");
		return;
	}
	if (root->father->child_node_list[2]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[2]->attribute.type, "int");
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* compare = new three_address_instruction();
	compare->index = this->final_instruction.size();
	compare->op = "JE";
	compare->arg1 = root->father->child_node_list[0]->attribute.addr;
	compare->arg2 = root->father->child_node_list[2]->attribute.addr;
	compare->result = std::to_string(compare->index + 3);
	this->final_instruction.push_back(compare);
	three_address_instruction* assign_false = new three_address_instruction();
	assign_false->index = this->final_instruction.size();
	assign_false->op = "=";
	assign_false->arg1 = "0";
	assign_false->arg2 = "-";
	assign_false->result = root->father->attribute.addr;
	this->final_instruction.push_back(assign_false);
	three_address_instruction* jump = new three_address_instruction();
	jump->index = this->final_instruction.size();
	jump->op = "JMP";
	jump->arg1 = "-";
	jump->arg2 = "-";
	jump->result = std::to_string(jump->index + 2);
	this->final_instruction.push_back(jump);
	three_address_instruction* assign_true = new three_address_instruction();
	assign_true->index = this->final_instruction.size();
	assign_true->op = "=";
	assign_true->arg1 = "1";
	assign_true->arg2 = "-";
	assign_true->result = root->father->attribute.addr;
	this->final_instruction.push_back(assign_true);
	root->father->attribute.type = "int";
	return;
}

void GrammerAnalyzer::action416(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[0]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[0]->attribute.type, "int");
		return;
	}
	if (root->father->child_node_list[2]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[2]->attribute.type, "int");
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* compare = new three_address_instruction();
	compare->index = this->final_instruction.size();
	compare->op = "JNE";
	compare->arg1 = root->father->child_node_list[0]->attribute.addr;
	compare->arg2 = root->father->child_node_list[2]->attribute.addr;
	compare->result = std::to_string(compare->index + 3);
	this->final_instruction.push_back(compare);
	three_address_instruction* assign_false = new three_address_instruction();
	assign_false->index = this->final_instruction.size();
	assign_false->op = "=";
	assign_false->arg1 = "0";
	assign_false->arg2 = "-";
	assign_false->result = root->father->attribute.addr;
	this->final_instruction.push_back(assign_false);
	three_address_instruction* jump = new three_address_instruction();
	jump->index = this->final_instruction.size();
	jump->op = "JMP";
	jump->arg1 = "-";
	jump->arg2 = "-";
	jump->result = std::to_string(jump->index + 2);
	this->final_instruction.push_back(jump);
	three_address_instruction* assign_true = new three_address_instruction();
	assign_true->index = this->final_instruction.size();
	assign_true->op = "=";
	assign_true->arg1 = "1";
	assign_true->arg2 = "-";
	assign_true->result = root->father->attribute.addr;
	this->final_instruction.push_back(assign_true);
	root->father->attribute.type = "int";
	return;
}

void GrammerAnalyzer::action417(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[0]->attribute.addr;
	root->father->attribute.type = root->father->child_node_list[0]->attribute.type;
	root->father->attribute.array_info.name = root->father->child_node_list[0]->attribute.array_info.name;
	root->father->attribute.array_info.pos = root->father->child_node_list[0]->attribute.array_info.pos;
	return;
}

void GrammerAnalyzer::action418(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[0]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[0]->attribute.type, "int");
		return;
	}
	if (root->father->child_node_list[2]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[2]->attribute.type, "int");
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* operation = new three_address_instruction();
	operation->index = this->final_instruction.size();
	operation->op = "^";
	operation->arg1 = root->father->child_node_list[0]->attribute.addr;
	operation->arg2 = root->father->child_node_list[2]->attribute.addr;
	operation->result = root->father->attribute.addr;
	this->final_instruction.push_back(operation);
	root->father->attribute.type = "int";
	return;
}

void GrammerAnalyzer::action419(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[0]->attribute.addr;
	root->father->attribute.type = root->father->child_node_list[0]->attribute.type;
	root->father->attribute.array_info.name = root->father->child_node_list[0]->attribute.array_info.name;
	root->father->attribute.array_info.pos = root->father->child_node_list[0]->attribute.array_info.pos;
	return;
}

void GrammerAnalyzer::action420(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[0]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[0]->attribute.type, "int");
		return;
	}
	if (root->father->child_node_list[2]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[2]->attribute.type, "int");
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* operation = new three_address_instruction();
	operation->index = this->final_instruction.size();
	operation->op = "JZ";
	operation->arg1 = root->father->child_node_list[0]->attribute.addr;
	operation->arg2 = "-";
	operation->result = std::to_string(operation->index + 4);
	this->final_instruction.push_back(operation);
	three_address_instruction* operation2 = new three_address_instruction();
	operation2->index = this->final_instruction.size();
	operation2->op = "JZ";
	operation2->arg1 = root->father->child_node_list[2]->attribute.addr;
	operation2->arg2 = "-";
	operation2->result = std::to_string(operation2->index + 3);
	this->final_instruction.push_back(operation2);
	three_address_instruction* assign_true = new three_address_instruction();
	assign_true->index = this->final_instruction.size();
	assign_true->op = "=";
	assign_true->arg1 = "1";
	assign_true->arg2 = "-";
	assign_true->result = root->father->attribute.addr;
	this->final_instruction.push_back(assign_true);
	three_address_instruction* jump = new three_address_instruction();
	jump->index = this->final_instruction.size();
	jump->op = "JMP";
	jump->arg1 = "-";
	jump->arg2 = "-";
	jump->result = std::to_string(jump->index + 2);
	this->final_instruction.push_back(jump);
	three_address_instruction* assign_false = new three_address_instruction();
	assign_false->index = this->final_instruction.size();
	assign_false->op = "=";
	assign_false->arg1 = "0";
	assign_false->arg2 = "-";
	assign_false->result = root->father->attribute.addr;
	this->final_instruction.push_back(assign_false);
	root->father->attribute.type = "int";
	return;
}


void GrammerAnalyzer::action421(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[0]->attribute.addr;
	root->father->attribute.type = root->father->child_node_list[0]->attribute.type;
	root->father->attribute.array_info.name = root->father->child_node_list[0]->attribute.array_info.name;
	root->father->attribute.array_info.pos = root->father->child_node_list[0]->attribute.array_info.pos;
	return;
}

void GrammerAnalyzer::action422(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[0]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[0]->attribute.type, "int");
		return;
	}
	if (root->father->child_node_list[2]->attribute.type != "int") {
		this->say_error(1, root->father->child_node_list[2]->attribute.type, "int");
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* operation = new three_address_instruction();
	operation->index = this->final_instruction.size();
	operation->op = "JNZ";
	operation->arg1 = root->father->child_node_list[0]->attribute.addr;
	operation->arg2 = "-";
	operation->result = std::to_string(operation->index + 4);
	this->final_instruction.push_back(operation);
	three_address_instruction* operation2 = new three_address_instruction();
	operation2->index = this->final_instruction.size();
	operation2->op = "JNZ";
	operation2->arg1 = root->father->child_node_list[2]->attribute.addr;
	operation2->arg2 = "-";
	operation2->result = std::to_string(operation2->index + 3);
	this->final_instruction.push_back(operation2);
	three_address_instruction* assign_false = new three_address_instruction();
	assign_false->index = this->final_instruction.size();
	assign_false->op = "=";
	assign_false->arg1 = "0";
	assign_false->arg2 = "-";
	assign_false->result = root->father->attribute.addr;
	this->final_instruction.push_back(assign_false);
	three_address_instruction* jump = new three_address_instruction();
	jump->index = this->final_instruction.size();
	jump->op = "JMP";
	jump->arg1 = "-";
	jump->arg2 = "-";
	jump->result = std::to_string(jump->index + 2);
	this->final_instruction.push_back(jump);
	three_address_instruction* assign_true = new three_address_instruction();
	assign_true->index = this->final_instruction.size();
	assign_true->op = "=";
	assign_true->arg1 = "1";
	assign_true->arg2 = "-";
	assign_true->result = root->father->attribute.addr;
	this->final_instruction.push_back(assign_true);
	root->father->attribute.type = "int";
	return;
}

void GrammerAnalyzer::action423(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[0]->attribute.addr;
	root->father->attribute.type = root->father->child_node_list[0]->attribute.type;
	root->father->attribute.array_info.name = root->father->child_node_list[0]->attribute.array_info.name;
	root->father->attribute.array_info.pos = root->father->child_node_list[0]->attribute.array_info.pos;
	return;
}

void GrammerAnalyzer::action424(hebo::LexicalUnit* root) {
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	if (root->father->child_node_list[0]->attribute.type != root->father->child_node_list[2]->attribute.type) {
		this->say_error(1, root->father->child_node_list[2]->attribute.type, root->father->child_node_list[0]->attribute.type);
		return;
	}
	std::string temp_type = root->father->child_node_list[0]->attribute.type;
	root->father->attribute.type = temp_type;
	if (temp_type == "int") {
		if (root->father->child_node_list[0]->attribute.array_info.name == "") {
			if (root->father->child_node_list[2]->attribute.array_info.name == "") {
				three_address_instruction* assign_1 = new three_address_instruction();
				assign_1->index = this->final_instruction.size();
				assign_1->op = "=";
				assign_1->arg1 = root->father->child_node_list[2]->attribute.addr;
				assign_1->arg2 = "-";
				assign_1->result = root->father->child_node_list[0]->attribute.addr;
				this->final_instruction.push_back(assign_1);
				three_address_instruction* assign_2 = new three_address_instruction();
				assign_2->index = this->final_instruction.size();
				assign_2->op = "=";
				assign_2->arg1 = root->father->child_node_list[2]->attribute.addr;
				assign_2->arg2 = "-";
				assign_2->result = root->father->attribute.addr;
				this->final_instruction.push_back(assign_2);
			}
			else {
				three_address_instruction* assign_1 = new three_address_instruction();
				assign_1->index = this->final_instruction.size();
				assign_1->op = "=[]";
				assign_1->arg1 = root->father->child_node_list[2]->attribute.array_info.name;
				assign_1->arg2 = root->father->child_node_list[2]->attribute.array_info.pos;
				assign_1->result = root->father->child_node_list[0]->attribute.addr;
				this->final_instruction.push_back(assign_1);
				three_address_instruction* assign_2 = new three_address_instruction();
				assign_2->index = this->final_instruction.size();
				assign_2->op = "=[]";
				assign_2->arg1 = root->father->child_node_list[2]->attribute.array_info.name;
				assign_2->arg2 = root->father->child_node_list[2]->attribute.array_info.pos;
				assign_2->result = root->father->attribute.addr;
				this->final_instruction.push_back(assign_2);
			}

		}
		else {
			if (root->father->child_node_list[2]->attribute.array_info.name == "") {
				three_address_instruction* assign_1 = new three_address_instruction();
				assign_1->index = this->final_instruction.size();
				assign_1->op = "[]=";
				assign_1->arg1 = root->father->child_node_list[0]->attribute.array_info.name;
				assign_1->arg2 = root->father->child_node_list[0]->attribute.array_info.pos;
				assign_1->result = root->father->child_node_list[2]->attribute.addr;
				this->final_instruction.push_back(assign_1);
				three_address_instruction* assign_2 = new three_address_instruction();
				assign_2->index = this->final_instruction.size();
				assign_2->op = "=";
				assign_2->arg1 = root->father->child_node_list[2]->attribute.addr;
				assign_2->arg2 = "-";
				assign_2->result = root->father->attribute.addr;
				this->final_instruction.push_back(assign_2);
			}
			else {
				hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
				this->out_table->put_symbol(temp);
				three_address_instruction* assign_1 = new three_address_instruction();
				assign_1->index = this->final_instruction.size();
				assign_1->op = "=[]";
				assign_1->arg1 = root->father->child_node_list[2]->attribute.array_info.name;
				assign_1->arg2 = root->father->child_node_list[2]->attribute.array_info.pos;
				assign_1->result = temp.address;
				this->final_instruction.push_back(assign_1);
				three_address_instruction* assign_2 = new three_address_instruction();
				assign_2->index = this->final_instruction.size();
				assign_2->op = "[]=";
				assign_2->arg1 = root->father->child_node_list[0]->attribute.array_info.name;
				assign_2->arg2 = root->father->child_node_list[0]->attribute.array_info.pos;
				assign_2->result = temp.address;
				this->final_instruction.push_back(assign_2);
				three_address_instruction* assign_3 = new three_address_instruction();
				assign_3->index = this->final_instruction.size();
				assign_3->op = "=";
				assign_3->arg1 = temp.address;
				assign_3->arg2 = "-";
				assign_3->result = root->father->attribute.addr;
				this->final_instruction.push_back(assign_3);
			}
		}
	}
	else if (temp_type.substr(0, 6) == "struct" && temp_type[temp_type.size() - 1] != ']') {
		three_address_instruction* assign_1 = new three_address_instruction();
		assign_1->index = this->final_instruction.size();
		assign_1->op = "=";
		assign_1->arg1 = root->father->child_node_list[2]->attribute.addr;
		assign_1->arg2 = "-";
		assign_1->result = root->father->child_node_list[0]->attribute.addr;
		this->final_instruction.push_back(assign_1);
		three_address_instruction* assign_2 = new three_address_instruction();
		assign_2->index = this->final_instruction.size();
		assign_2->op = "=";
		assign_2->arg1 = root->father->child_node_list[2]->attribute.addr;
		assign_2->arg2 = "-";
		assign_2->result = root->father->attribute.addr;
		this->final_instruction.push_back(assign_2);
	}
	else {
		this->say_error(1, temp_type, "NOWAY");
	}
	return;
}

void GrammerAnalyzer::action425(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[0]->attribute.addr;
	root->father->attribute.type = root->father->child_node_list[0]->attribute.type;
	root->father->attribute.array_info.name = root->father->child_node_list[0]->attribute.array_info.name;
	root->father->attribute.array_info.pos = root->father->child_node_list[0]->attribute.array_info.pos;
	return;
}

void GrammerAnalyzer::action426(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[2]->attribute.addr;
	root->father->attribute.type = root->father->child_node_list[0]->attribute.type;
	root->father->attribute.array_info.name = root->father->child_node_list[0]->attribute.array_info.name;
	root->father->attribute.array_info.pos = root->father->child_node_list[0]->attribute.array_info.pos;
	return;
}

void GrammerAnalyzer::action427(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[0]->attribute.addr;
	return;
}
