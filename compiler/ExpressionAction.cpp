#include "GrammerAnalyzer.h"

void GrammerAnalyzer::action1(hebo::LexicalUnit* root) {
	root->father->attribute.addr = this->out_table->get_symbol(root->father->child_node_list[0]->morpheme).address;
	root->father->attribute.type = this->out_table->get_symbol(root->father->child_node_list[0]->morpheme).type;
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
	root->father->attribute.type = "int";
	constant_map.insert(std::make_pair(temp.address, std::atoi(root->father->child_node_list[0]->morpheme.c_str())));
	three_address_instruction* assignment = new three_address_instruction();
	assignment->index = this->final_instruction.size();
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
	root->father->attribute.type = root->father->child_node_list[1]->attribute.type;
	root->father->attribute.array_info.name = root->father->child_node_list[1]->attribute.array_info.name;
	root->father->attribute.array_info.pos = root->father->child_node_list[1]->attribute.array_info.pos;
	root->father->attribute.array_info.element_width = root->father->child_node_list[1]->attribute.array_info.element_width;
	root->father->attribute.array_info.element_type = root->father->child_node_list[1]->attribute.array_info.element_type;
	root->father->attribute.array_info.element_addr = root->father->child_node_list[1]->attribute.array_info.element_addr;
	return;
}

void GrammerAnalyzer::action5(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[0]->attribute.addr;
	root->father->attribute.type = root->father->child_node_list[0]->attribute.type;
	root->father->attribute.array_info.name = root->father->child_node_list[0]->attribute.array_info.name;
	root->father->attribute.array_info.pos = root->father->child_node_list[0]->attribute.array_info.pos;
	root->father->attribute.array_info.element_width = root->father->child_node_list[0]->attribute.array_info.element_width;
	root->father->attribute.array_info.element_type = root->father->child_node_list[0]->attribute.array_info.element_type;
	root->father->attribute.array_info.element_addr = root->father->child_node_list[0]->attribute.array_info.element_addr;

	return;
}

void GrammerAnalyzer::action6(hebo::LexicalUnit* root) {
	std::string type = this->out_table->get_symbol(root->father->child_node_list[0]->morpheme).type;
	if (type[type.size() - 1] != ']') {
		this->say_error();
	}
	if (this->out_table->get_symbol_from_address(root->father->child_node_list[2]->attribute.addr).type != "int") {
		this->say_error();
	}
	if (type.substr(0, 3) == "int") {
		hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
        hbst::SymbolItem offset = hbst::SymbolItem("", "int", 0, 4);
        this->out_table->put_symbol(offset);
        this->out_table->put_symbol(temp);
        root->father->attribute.addr = temp.address;
		root->father->attribute.array_info.name = this->out_table->get_symbol(root->father->child_node_list[0]->morpheme).address;
		three_address_instruction* assignment = new three_address_instruction();
		assignment->index = this->final_instruction.size();
		assignment->op = "*";
		assignment->arg1 = std::to_string(4);
		assignment->arg2 = root->father->child_node_list[2]->attribute.addr;
		assignment->result = offset.name;
		this->final_instruction.push_back(assignment);
        three_address_instruction* get_addr = new three_address_instruction();
        get_addr->index = this->final_instruction.size();
        get_addr->op = "=[]";
        get_addr->arg1 = root->father->attribute.array_info.name;
        get_addr->arg2 = offset.name;
        get_addr->result = root->father->attribute.addr;
        this->final_instruction.push_back(get_addr);
		root->father->attribute.array_info.pos = offset.name;
		root->father->attribute.type = "int";
	}
	else if (type.substr(0, 6) == "struct" && type[type.size() - 1] == ']') {
		std::string name = root->father->child_node_list[0]->morpheme + "$" + std::to_string(constant_map[root->father->child_node_list[2]->attribute.addr]);
		root->father->attribute.addr = this->out_table->get_symbol(name).address;
		root->father->attribute.type = type.substr(0, type.rfind('['));
	}
	return;
}

void GrammerAnalyzer::action7(hebo::LexicalUnit* root) {
    std::string temp_type = function_table->get_function(root->father->child_node_list[0]->attribute.addr).return_type;
    hbst::SymbolItem temp;
    if (temp_type == "void") {
        three_address_instruction* call = new three_address_instruction();
        call->index = this->final_instruction.size();
        call->op = "CALL";
        call->arg1 = root->father->child_node_list[0]->attribute.addr;
        call->arg2 = "-";
        call->result = "-";
        this->final_instruction.push_back(call);
        root->father->attribute.type = temp_type;
        return;
    }
    else if (temp_type == "int") {
        temp = hbst::SymbolItem("", "int", 0, 4);
    }
    else {
        temp = hbst::SymbolItem("", temp_type, 0, out_table->get_symbol(temp_type.substr(0, temp_type.find("$"))).width);
    }
	this->out_table->put_symbol(temp);
	three_address_instruction* call = new three_address_instruction();
	call->index = this->final_instruction.size();
	call->op = "CALL";
	call->arg1 = root->father->child_node_list[0]->attribute.addr;
	call->arg2 = "-";
	call->result = temp.address;
	this->final_instruction.push_back(call);
    root->father->attribute.addr = temp.address;
    root->father->attribute.type = temp.type;
    return;
}

void GrammerAnalyzer::action8(hebo::LexicalUnit* root) {
    std::string temp_type = function_table->get_function(root->father->child_node_list[0]->attribute.addr).return_type;
    if (this->check_type(root->father->child_node_list[0]->attribute.addr, this->parameter_list) == false) {
    	    this->say_error();
    }
    this->clean_param_list();
    hbst::SymbolItem temp;
    if (temp_type == "void") {
        three_address_instruction* call = new three_address_instruction();
        call->index = this->final_instruction.size();
        call->op = "CALL";
        call->arg1 = root->father->child_node_list[0]->attribute.addr;
        call->arg2 = "-";
        call->result = "-";
        this->final_instruction.push_back(call);
        root->father->attribute.type = temp_type;
        return;
    }
    else if (temp_type == "int") {
        temp = hbst::SymbolItem("", "int", 0, 4);
    }
    else {
        temp = hbst::SymbolItem("", temp_type, 0, out_table->get_symbol(temp_type.substr(0, temp_type.find("$"))).width);
    }
    this->out_table->put_symbol(temp);
    three_address_instruction* call = new three_address_instruction();
    call->index = this->final_instruction.size();
    call->op = "CALL";
    call->arg1 = root->father->child_node_list[0]->attribute.addr;
    call->arg2 = "-";
    call->result = temp.address;
    this->final_instruction.push_back(call);
    root->father->attribute.addr = temp.address;
    root->father->attribute.type = temp.type;
    return;
}

void GrammerAnalyzer::action9(hebo::LexicalUnit* root) {
	std::string temp_address = this->out_table->get_symbol(root->father->child_node_list[0]->morpheme).address;
	std::string type = this->out_table->get_symbol(root->father->child_node_list[0]->morpheme).type;
	if ((type.rfind("struct") >= type.size()) || (type.find('[') < type.size())) {
		this->say_error();
	}
	std::string target = root->father->child_node_list[0]->morpheme + "$" + root->father->child_node_list[2]->morpheme;
	root->father->attribute.addr = this->out_table->get_symbol(target).address;
	root->father->attribute.type = this->struct_table->get_struct(temp_address).symbol_table.get_symbol(root->father->child_node_list[2]->morpheme).type;
	return;
}

void GrammerAnalyzer::action10(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[0]->attribute.type != "int") {
		this->say_error();
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* assignment = new three_address_instruction();
	assignment->index = this->final_instruction.size();
	assignment->op = "=";
	assignment->arg1 = root->father->child_node_list[0]->attribute.addr;
	assignment->arg2 = "-";
	assignment->result = root->father->attribute.addr;
	this->final_instruction.push_back(assignment);
	three_address_instruction* add = new three_address_instruction();
    add->index = this->final_instruction.size();
	add->op = "++";
	add->arg1 = root->father->child_node_list[0]->attribute.addr;
	add->arg2 = "-";
	add->result = root->father->child_node_list[0]->attribute.addr;
	this->final_instruction.push_back(add);
	root->father->attribute.type = "int";
	return;
}

void GrammerAnalyzer::action11(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[0]->attribute.type != "int") {
		this->say_error();
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* assignment = new three_address_instruction();
	assignment->index = this->final_instruction.size();
	assignment->op = "=";
	assignment->arg1 = root->father->child_node_list[0]->attribute.addr;
	assignment->arg2 = "-";
	assignment->result = root->father->attribute.addr;
	this->final_instruction.push_back(assignment);
	three_address_instruction* subtract = new three_address_instruction();
	subtract->index = this->final_instruction.size();
	subtract->op = "--";
	subtract->arg1 = root->father->child_node_list[0]->attribute.addr;
	subtract->arg2 = "-";
	subtract->result = root->father->child_node_list[0]->attribute.addr;
	this->final_instruction.push_back(subtract);
	root->father->attribute.type = "int";
	return;
}

void GrammerAnalyzer::action12(hebo::LexicalUnit* root) {
	root->father->attribute.addr = root->father->child_node_list[0]->attribute.addr;
	root->father->attribute.type = root->father->child_node_list[0]->attribute.type;
	root->father->attribute.array_info.name = root->father->child_node_list[0]->attribute.array_info.name;
	root->father->attribute.array_info.pos = root->father->child_node_list[0]->attribute.array_info.pos;
	return;
}

void GrammerAnalyzer::action13(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[1]->attribute.type != "int") {
		this->say_error();
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* add = new three_address_instruction();
	add->index = this->final_instruction.size();
	add->op = "++";
	add->arg1 = root->father->child_node_list[1]->attribute.addr;
	add->arg2 = "-";
	add->result = root->father->child_node_list[1]->attribute.addr;
	this->final_instruction.push_back(add);
	three_address_instruction* assignment = new three_address_instruction();
	assignment->index = this->final_instruction.size();
	assignment->op = "=";
	assignment->arg1 = root->father->child_node_list[1]->attribute.addr;
	assignment->arg2 = "-";
	assignment->result = root->father->attribute.addr;
	this->final_instruction.push_back(assignment);
	root->father->attribute.type = "int";
	return;
}

void GrammerAnalyzer::action14(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[1]->attribute.type != "int") {
		this->say_error();
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* add = new three_address_instruction();
	add->index = this->final_instruction.size();
	add->op = "--";
	add->arg1 = root->father->child_node_list[1]->attribute.addr;
	add->arg2 = "-";
	add->result = root->father->child_node_list[1]->attribute.addr;
	this->final_instruction.push_back(add);
	three_address_instruction* assignment = new three_address_instruction();
	assignment->index = this->final_instruction.size();
	assignment->op = "=";
	assignment->arg1 = root->father->child_node_list[1]->attribute.addr;
	assignment->arg2 = "-";
	assignment->result = root->father->attribute.addr;
	this->final_instruction.push_back(assignment);
	root->father->attribute.type = "int";
	return;
}

void GrammerAnalyzer::action15(hebo::LexicalUnit* root) {
	if (root->father->child_node_list[1]->attribute.type != "int") {
		this->say_error();
		return;
	}
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	if (root->father->child_node_list[0]->attribute.op_value == "-") {
		three_address_instruction* minus = new three_address_instruction();
		minus->index = this->final_instruction.size();
		minus->op = "MINUS";
		minus->arg1 = root->father->child_node_list[1]->attribute.addr;
		minus->arg2 = "-";
		minus->result = root->father->attribute.addr;
		this->final_instruction.push_back(minus);
	}
	else if (root->father->child_node_list[0]->attribute.op_value == "!") {
		three_address_instruction* fei = new three_address_instruction();
		fei->index = this->final_instruction.size();
		fei->op = "!";
		fei->arg1 = root->father->child_node_list[2]->attribute.addr;
		fei->arg2 = "-";
		fei->result = root->father->attribute.addr;
		this->final_instruction.push_back(fei);
	}
	else {
		this->say_error();
	}
	root->father->attribute.type = "int";
	return;
}

void GrammerAnalyzer::action16(hebo::LexicalUnit* root) {
	hbst::SymbolItem temp = hbst::SymbolItem("", "int", 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* assignment = new three_address_instruction();
	assignment->index = this->final_instruction.size();
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
	assignment->index = this->final_instruction.size();
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
	root->father->attribute.type = root->father->child_node_list[0]->attribute.type;
	root->father->attribute.array_info.name = root->father->child_node_list[0]->attribute.array_info.name;
	root->father->attribute.array_info.pos = root->father->child_node_list[0]->attribute.array_info.pos;
	return;
}

void GrammerAnalyzer::action25(hebo::LexicalUnit* root) {
	hbst::SymbolItem temp = hbst::SymbolItem("", root->father->child_node_list[1]->attribute.type, 0, 4);
	this->out_table->put_symbol(temp);
	root->father->attribute.addr = temp.address;
	three_address_instruction* assignment = new three_address_instruction();
	assignment->index = this->final_instruction.size();
	assignment->op = "=";
	assignment->arg1 = root->father->child_node_list[0]->attribute.addr;
	assignment->arg2 = "-";
	assignment->result = root->father->attribute.addr;
	this->final_instruction.push_back(assignment);
	return;
}

void GrammerAnalyzer::action26(hebo::LexicalUnit* root) {
	three_address_instruction* param = new three_address_instruction();
	param->index = this->final_instruction.size();
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
	param->index = this->final_instruction.size();
	param->op = "PARAM";
	param->arg1 = root->father->child_node_list[2]->attribute.addr;
	param->arg2 = "-";
	param->result = "-";
	this->final_instruction.push_back(param);
	this->parameter_list.push_back(this->out_table->get_symbol_from_address(root->father->child_node_list[2]->attribute.addr).type);
	root->father->attribute.param_number += 1;
	return;
}