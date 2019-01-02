#include "GrammerAnalyzer.h"
using namespace hbst;

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
	to->attribute.if_struct = true;
	to->attribute.struct_info = from->attribute.struct_info;	
	return;
}

void GrammerAnalyzer::action211(hebo::LexicalUnit* root) {
	root->father->morpheme = root->father->child_node_list[0]->morpheme;
	root->father->attribute.type = root->father->attribute.type;
	root->father->attribute.width = root->father->attribute.width;
	return;
}

void GrammerAnalyzer::action212(hebo::LexicalUnit* root) {
	root->father->morpheme = root->father->child_node_list[0]->morpheme;
	root->father->attribute.type = root->father->attribute.type + "[" + std::to_string(constant_map[root->father->child_node_list[2]->attribute.addr]) + "]";
	root->father->attribute.width = root->father->attribute.width * constant_map[root->father->child_node_list[2]->attribute.addr];
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

void GrammerAnalyzer::action223(hebo::LexicalUnit* root) {
	hebo::LexicalUnit* init_declarator = root->father;
	hebo::LexicalUnit* declarator = root->father->child_node_list[1];
	hebo::LexicalUnit* initializer = root->father->child_node_list[3];
	if (init_declarator->attribute.if_struct == true) {
		declarator->attribute.struct_info = init_declarator->attribute.struct_info;
	}
	declarator->attribute.if_struct = init_declarator->attribute.if_struct;
	declarator->attribute.type = init_declarator->attribute.type;
	declarator->attribute.width = init_declarator->attribute.width;
	return;
}

void GrammerAnalyzer::action224(hebo::LexicalUnit* root) {
	hebo::LexicalUnit* declarator = root->father->child_node_list[1];
	hebo::LexicalUnit* initializer = root->father->child_node_list[3];
	hbst::SymbolItem temp_item = hbst::SymbolItem(declarator->morpheme, declarator->attribute.type, 0, declarator->attribute.width);
	this->out_table->put_symbol(temp_item);
	declarator->attribute.addr = temp_item.address;
	if (initializer->attribute.type == "") {
		initializer->attribute.type = this->out_table->get_symbol_from_address(initializer->attribute.addr).type;
	}
	if (declarator->attribute.type != initializer->attribute.type) {
		this->say_error(1, initializer->attribute.type, declarator->attribute.type);
	}
	else {
		std::string type = root->father->child_node_list[1]->attribute.type;
		if (type.substr(0, 6) == "struct" && type[type.size() - 1] != ']') {
			three_address_instruction* assign = new three_address_instruction();
			assign->index = this->final_instruction.size();
			assign->op = "=";
			assign->arg1 = initializer->attribute.addr;
			assign->arg2 = "-";
			assign->result = declarator->attribute.addr;
			this->final_instruction.push_back(assign);
		}
		else if (type.substr(0, 6) == "struct" && type[type.size() - 1] == ']') {
			this->say_error(1, "struct[]", "struct");
		}
		else if (type.substr(0, 4) == "int[") {
			int temp_size = initializer->attribute.array_info.element_addr.size();
			if (temp_size == 0) {
				this->say_error(1, "Array Is Empty", "Array Is Empty");
			}
			else {
				if (declarator->attribute.width / 4 != temp_size) {
					this->say_error(1, "Array Out Of Bounds!", "Array Out Of Bounds!");
				}
				else {
					for (int tt = 0; tt < temp_size; tt++) {
						three_address_instruction* copy = new three_address_instruction();
						copy->index = this->final_instruction.size();
						copy->op = "[]=";
						copy->arg1 = declarator->attribute.addr;
						copy->arg2 = std::to_string(tt*4);
						copy->result = initializer->attribute.array_info.element_addr[tt];
						this->final_instruction.push_back(copy);
					}
				}
			}
		}
		else if (type == "int")
		{
			three_address_instruction* copy = new three_address_instruction();
			copy->index = this->final_instruction.size();
			copy->op = "=";
			copy->arg1 = initializer->attribute.addr;
			copy->result = declarator->attribute.addr;
			this->final_instruction.push_back(copy);
		}
		else {
			this->say_error(1, type, "NOWAY");
		}
	}
	return;
}

void GrammerAnalyzer::action225(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[0]->attribute.addr;
	return;
}

void GrammerAnalyzer::action226(hebo::LexicalUnit* root) {
	root->father->attribute.array_info.element_addr = root->father->child_node_list[1]->attribute.array_info.element_addr;
	root->father->attribute.type = "int[" + std::to_string(root->father->child_node_list[1]->attribute.array_info.element_addr.size()) + "]";
	return;
}

void GrammerAnalyzer::action227(hebo::LexicalUnit* root) {
	root->father->attribute.array_info.element_addr = root->father->child_node_list[1]->attribute.array_info.element_addr;
	return;
}

void GrammerAnalyzer::action228(hebo::LexicalUnit* root) {
	hebo::LexicalUnit* assignment = root->father->child_node_list[0];
	root->father->attribute.array_info.element_addr.push_back(assignment->attribute.addr);
	assignment->attribute.type = this->out_table->get_symbol_from_address(assignment->attribute.addr).type;
	if (assignment->attribute.type != "int") {
		this->say_error(1, assignment->attribute.type, "int");
	}
	return;
}

void GrammerAnalyzer::action229(hebo::LexicalUnit* root) {
	hebo::LexicalUnit* assignment = root->father->child_node_list[2];
	assignment->attribute.type = this->out_table->get_symbol_from_address(assignment->attribute.addr).type;
	root->father->attribute.array_info.element_addr = root->father->child_node_list[0]->attribute.array_info.element_addr;
	root->father->attribute.array_info.element_addr.push_back(assignment->attribute.addr);
	if (assignment->attribute.type != "int") {
		this->say_error(1, assignment->attribute.type, "int");
	}
	return;
}

void GrammerAnalyzer::action230(hebo::LexicalUnit* root) {
	SymbolTable *temp_table = this->out_table;
	this->out_table = temp_table->father;
	this->out_table->son_vector.pop_back();
	root->father->attribute.width = root->father->child_node_list[4]->attribute.width;
	root->father->attribute.if_struct = true;
	hbst::SymbolItem temp_item(root->father->child_node_list[1]->morpheme, "struct", 0, root->father->attribute.width);
	this->out_table->put_symbol(temp_item);
	std::string temp_address = this->out_table->get_symbol(root->father->child_node_list[1]->morpheme).address;
	this->struct_table->put_struct(hbst::StructItem(temp_address, *temp_table));
	root->father->attribute.type = "struct " + temp_address;
	root->father->attribute.struct_info = struct_table->get_struct(temp_address);
	return;
}

void GrammerAnalyzer::action231(hebo::LexicalUnit* root) {
	SymbolTable *temp_table = new SymbolTable("", this->out_table);
	this->out_table = temp_table;
}

void GrammerAnalyzer::action232(hebo::LexicalUnit* root) {
	SymbolTable *temp_table = new SymbolTable("", this->out_table);
	this->out_table = temp_table;
}

void GrammerAnalyzer::action233(hebo::LexicalUnit* root) {
	SymbolTable *temp_table = this->out_table;
	this->out_table = temp_table->father;
	this->out_table->son_vector.pop_back();
	root->father->attribute.width = root->father->child_node_list[3]->attribute.width;
	root->father->attribute.if_struct = true;
	hbst::SymbolItem temp_item("", "struct", 0, root->father->attribute.width);
	this->out_table->put_symbol(temp_item);
	std::string temp_address = temp_item.address;
	this->struct_table->put_struct(hbst::StructItem(temp_address, *temp_table));
	root->father->attribute.type = "struct " + temp_address;
	root->father->attribute.struct_info = struct_table->get_struct(temp_address);
	return;
}

void GrammerAnalyzer::action234(hebo::LexicalUnit* root) {
	root->father->attribute.if_struct = true;
	std::string temp = this->out_table->get_symbol(root->father->child_node_list[1]->morpheme).address;
	root->father->attribute.struct_info = struct_table->get_struct(temp);
	root->father->attribute.type = "string " + root->father->attribute.struct_info.name;
	root->father->attribute.width = this->out_table->get_symbol(root->father->child_node_list[1]->morpheme).width;
	return;
}

void GrammerAnalyzer::action235(hebo::LexicalUnit* root) {
	root->father->attribute.width = root->father->child_node_list[0]->attribute.width;
	return;
}

void GrammerAnalyzer::action236(hebo::LexicalUnit* root) {
	root->father->attribute.width = root->father->child_node_list[0]->attribute.width + root->father->child_node_list[1]->attribute.width;
	return;
}

void GrammerAnalyzer::action237(hebo::LexicalUnit* root) {
	root->father->child_node_list[2]->attribute.type = root->father->child_node_list[0]->attribute.type;
	root->father->child_node_list[2]->attribute.width = root->father->child_node_list[0]->attribute.width;
	return;
}

void GrammerAnalyzer::action238(hebo::LexicalUnit* root) {
	root->father->attribute.width = root->father->child_node_list[2]->attribute.width;
	root->father->attribute.type = root->father->child_node_list[0]->attribute.type;
	return;
}

void GrammerAnalyzer::action239(hebo::LexicalUnit* root) {
	root->father->child_node_list[1]->attribute.type = root->father->attribute.type;
	root->father->child_node_list[1]->attribute.width = root->father->attribute.width;
	return;
}

void GrammerAnalyzer::action240(hebo::LexicalUnit* root) {
	root->father->attribute.width = root->father->child_node_list[1]->attribute.width;
	return;
}

void GrammerAnalyzer::action241(hebo::LexicalUnit* root) {
	root->father->child_node_list[1]->attribute.type = root->father->attribute.type;
	root->father->child_node_list[1]->attribute.width = root->father->attribute.width;
	root->father->child_node_list[3]->attribute.type = root->father->attribute.type;
	root->father->child_node_list[3]->attribute.width = root->father->attribute.width;
	return;
}

void GrammerAnalyzer::action242(hebo::LexicalUnit* root) {
	root->father->attribute.width = root->father->child_node_list[1]->attribute.width + root->father->child_node_list[3]->attribute.width;
	return;
}