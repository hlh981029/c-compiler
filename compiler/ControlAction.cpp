#include "GrammerAnalyzer.h"

void GrammerAnalyzer::action501(hebo::LexicalUnit* root) {
	int now_instr = this->final_instruction.size();
	root->father->child_node_list[3]->attribute.instr = now_instr;
	return;
}

void GrammerAnalyzer::action502(hebo::LexicalUnit* root) {
	three_address_instruction* temp_test = new three_address_instruction();
	temp_test->index = this->final_instruction.size();
	temp_test->op = "JNZ";
	temp_test->arg1 = root->father->child_node_list[3]->attribute.addr;
	this->final_instruction.push_back(temp_test);
	root->father->child_node_list[3]->attribute.true_instr = this->final_instruction.size() - 1;
	root->father->child_node_list[3]->attribute.false_instr = this->final_instruction.size();
	three_address_instruction* false_instruction = new three_address_instruction();
	false_instruction->index = this->final_instruction.size();
	false_instruction->op = "JMP";
	this->final_instruction.push_back(false_instruction);
	return;
}

void GrammerAnalyzer::action503(hebo::LexicalUnit* root) {
	hebo::LexicalUnit* statement = root->father->child_node_list[7];
	hebo::LexicalUnit* expression = root->father->child_node_list[3];
	int break_instr = this->final_instruction.size();
	statement->attribute.break_instr = break_instr;
	three_address_instruction* break_instruction = new three_address_instruction();
	break_instruction->index = this->final_instruction.size();
	break_instruction->op = "JMP";
	this->final_instruction.push_back(break_instruction);
	int now_instr = this->final_instruction.size();
	statement->attribute.instr = now_instr;
	this->final_instruction[expression->attribute.true_instr]->result = std::to_string(now_instr);
	statement->attribute.con_instr = expression->attribute.instr;
	return;
}

void GrammerAnalyzer::action504(hebo::LexicalUnit* root) {
	three_address_instruction* jump_back_instruction = new three_address_instruction();
	jump_back_instruction->index = this->final_instruction.size();
	jump_back_instruction->result = std::to_string(root->father->child_node_list[3]->attribute.instr);
	jump_back_instruction->op = "JMP";
	this->final_instruction.push_back(jump_back_instruction);
	int out_instr = this->final_instruction.size();
	this->final_instruction[root->father->child_node_list[3]->attribute.false_instr]->result = std::to_string(out_instr);
	this->final_instruction[root->father->child_node_list[7]->attribute.break_instr]->result = std::to_string(out_instr);
	return;
}

void GrammerAnalyzer::action505(hebo::LexicalUnit* root) {
		int now_instr = this->final_instruction.size();
	root->father->child_node_list[4]->attribute.instr = now_instr;
	return;
}

void GrammerAnalyzer::action506(hebo::LexicalUnit* root) {
	three_address_instruction* temp_test = new three_address_instruction();
	temp_test->index = this->final_instruction.size();
	temp_test->op = "JNZ";
	temp_test->arg1 = root->father->child_node_list[4]->attribute.addr;
	this->final_instruction.push_back(temp_test);

	root->father->child_node_list[4]->attribute.true_instr = this->final_instruction.size() - 1;
	root->father->child_node_list[4]->attribute.false_instr = this->final_instruction.size();
	three_address_instruction* false_instruction = new three_address_instruction();
	false_instruction->index = this->final_instruction.size();
	false_instruction->op = "JMP";
	this->final_instruction.push_back(false_instruction);
	return;
}

void GrammerAnalyzer::action507(hebo::LexicalUnit* root) {
	int break_instr = this->final_instruction.size();
	root->father->child_node_list[8]->attribute.break_instr = break_instr;
	three_address_instruction* break_instruction = new three_address_instruction();
	break_instruction->index = this->final_instruction.size();
	break_instruction->op = "JMP";
	this->final_instruction.push_back(break_instruction);

	int now_instr = this->final_instruction.size();
	root->father->child_node_list[8]->attribute.instr = now_instr;
	this->final_instruction[root->father->child_node_list[4]->attribute.true_instr]->result = std::to_string(now_instr);
	root->father->child_node_list[8]->attribute.con_instr = root->father->child_node_list[4]->attribute.instr;
	return;
}

void GrammerAnalyzer::action508(hebo::LexicalUnit* root) {
	three_address_instruction* jump_back_instruction = new three_address_instruction();
	jump_back_instruction->index = this->final_instruction.size();
	jump_back_instruction->op = "JMP";
	jump_back_instruction->result = std::to_string(root->father->child_node_list[4]->attribute.instr);
	this->final_instruction.push_back(jump_back_instruction);

	int out_instr = this->final_instruction.size();
	this->final_instruction[root->father->child_node_list[4]->attribute.false_instr]->result = std::to_string(out_instr);
	this->final_instruction[root->father->child_node_list[8]->attribute.break_instr]->result = std::to_string(out_instr);
	return;
}

void GrammerAnalyzer::action509(hebo::LexicalUnit* root) {
	int now_instr = this->final_instruction.size();
	root->father->child_node_list[4]->attribute.instr = now_instr;
	return;
}

void GrammerAnalyzer::action510(hebo::LexicalUnit* root) {
	three_address_instruction* temp_test = new three_address_instruction();
	temp_test->index = this->final_instruction.size();
	temp_test->op = "JNZ";
	temp_test->arg1 = root->father->child_node_list[4]->attribute.addr;
	this->final_instruction.push_back(temp_test);

	root->father->child_node_list[4]->attribute.true_instr = this->final_instruction.size() - 1;
	root->father->child_node_list[4]->attribute.false_instr = this->final_instruction.size();
	three_address_instruction* false_instruction = new three_address_instruction();
	false_instruction->index = this->final_instruction.size();
	false_instruction->op = "JMP";
	this->final_instruction.push_back(false_instruction);
	int expression_instr = this->final_instruction.size();
	root->father->child_node_list[6]->attribute.instr = expression_instr;
	return;
}

void GrammerAnalyzer::action511(hebo::LexicalUnit* root) {
	int jump_to_expression2_instr = this->final_instruction.size();
	root->father->child_node_list[6]->attribute.next_instr = jump_to_expression2_instr;
	three_address_instruction* jump_instruction = new three_address_instruction();
	jump_instruction->index = this->final_instruction.size();
	jump_instruction->op = "JMP";
	jump_instruction->result = std::to_string(root->father->child_node_list[4]->attribute.instr);
	this->final_instruction.push_back(jump_instruction);
	return;
}

void GrammerAnalyzer::action512(hebo::LexicalUnit* root) {
	int break_instr = this->final_instruction.size();
	root->father->child_node_list[10]->attribute.break_instr = break_instr;
	three_address_instruction* break_instruction = new three_address_instruction();
	break_instruction->index = this->final_instruction.size();
	break_instruction->op = "JMP";
	this->final_instruction.push_back(break_instruction);

	int instr = this->final_instruction.size();
	root->father->child_node_list[10]->attribute.instr = instr;
	this->final_instruction[root->father->child_node_list[4]->attribute.true_instr]->result = std::to_string(instr);
	root->father->child_node_list[10]->attribute.con_instr = root->father->child_node_list[4]->attribute.instr;
	return;
}

void GrammerAnalyzer::action513(hebo::LexicalUnit* root) {
	three_address_instruction* jump_back_instruction = new three_address_instruction();
	jump_back_instruction->index = this->final_instruction.size();
	jump_back_instruction->op = "JMP";
	jump_back_instruction->result = std::to_string(root->father->child_node_list[6]->attribute.instr);
	this->final_instruction.push_back(jump_back_instruction);

	int out_instr = this->final_instruction.size();
	this->final_instruction[root->father->child_node_list[4]->attribute.false_instr]->result = std::to_string(out_instr);
	this->final_instruction[root->father->child_node_list[10]->attribute.break_instr]->result = std::to_string(out_instr);
	return;
}

void GrammerAnalyzer::action514(hebo::LexicalUnit* root) {
	three_address_instruction* temp_test = new three_address_instruction();
	temp_test->index = this->final_instruction.size();
	temp_test->op = "JNZ";
	temp_test->arg1 = root->father->child_node_list[2]->attribute.addr;
	this->final_instruction.push_back(temp_test);

	root->father->child_node_list[2]->attribute.true_instr = this->final_instruction.size() - 1;
	root->father->child_node_list[2]->attribute.false_instr = this->final_instruction.size();
	three_address_instruction* false_instruction = new three_address_instruction();
	false_instruction->index = this->final_instruction.size();
	false_instruction->op = "JMP";
	this->final_instruction.push_back(false_instruction);

	return;
}

void GrammerAnalyzer::action515(hebo::LexicalUnit* root) {
	int instr = this->final_instruction.size();
	this->final_instruction[root->father->child_node_list[2]->attribute.true_instr]->result = std::to_string(instr);
	return;
}

void GrammerAnalyzer::action516(hebo::LexicalUnit* root) {
	int instr = this->final_instruction.size();
	this->final_instruction[root->father->child_node_list[2]->attribute.false_instr]->result = std::to_string(instr);

	return;
}

void GrammerAnalyzer::action517(hebo::LexicalUnit* root) {
	three_address_instruction* temp_test = new three_address_instruction();
	temp_test->index = this->final_instruction.size();
	temp_test->op = "JNZ";
	temp_test->arg1 = root->father->child_node_list[2]->attribute.addr;
	this->final_instruction.push_back(temp_test);

	root->father->child_node_list[2]->attribute.true_instr = this->final_instruction.size() - 1;
	root->father->child_node_list[2]->attribute.false_instr = this->final_instruction.size();
	three_address_instruction* false_instruction = new three_address_instruction();
	false_instruction->index = this->final_instruction.size();
	false_instruction->op = "JMP";
	this->final_instruction.push_back(false_instruction);

	return;
}

void GrammerAnalyzer::action518(hebo::LexicalUnit* root) {
	int instr = this->final_instruction.size();
	this->final_instruction[root->father->child_node_list[2]->attribute.true_instr]->result = std::to_string(instr);
	return;
}

void GrammerAnalyzer::action519(hebo::LexicalUnit* root) {
	root->father->child_node_list[6]->attribute.next_instr = this->final_instruction.size();
	three_address_instruction* out_instruction = new three_address_instruction();
	out_instruction->index = this->final_instruction.size();
	out_instruction->op = "JMP";
	this->final_instruction.push_back(out_instruction);
	return;
}

void GrammerAnalyzer::action520(hebo::LexicalUnit* root) {
	int instr = this->final_instruction.size();
	this->final_instruction[root->father->child_node_list[2]->attribute.false_instr]->result = std::to_string(instr);
	return;
}

void GrammerAnalyzer::action521(hebo::LexicalUnit* root) {
	int out_instr = this->final_instruction.size();
	this->final_instruction[root->father->child_node_list[6]->attribute.next_instr]->result = std::to_string(out_instr);

	return;
}

void GrammerAnalyzer::action522(hebo::LexicalUnit* root) {
	three_address_instruction* continue_jump = new three_address_instruction();
	continue_jump->index = this->final_instruction.size();
	continue_jump->op = "JMP";
	continue_jump->result = std::to_string(root->father->attribute.con_instr);
	this->final_instruction.push_back(continue_jump);
	return;
}

void GrammerAnalyzer::action523(hebo::LexicalUnit* root) {
    three_address_instruction* break_jump = new three_address_instruction();
    break_jump->index = this->final_instruction.size();
    break_jump->op = "JMP";
    break_jump->result = std::to_string(root->father->attribute.break_instr);
    this->final_instruction.push_back(break_jump);
    return;
}

void GrammerAnalyzer::action524(hebo::LexicalUnit* root) {
    three_address_instruction* return_jump = new three_address_instruction();
    return_jump->index = this->final_instruction.size();
    return_jump->op = "RET";
    return_jump->arg1 = "-";
    return_jump->arg2 = "-";
    return_jump->result = "-";
    this->final_instruction.push_back(return_jump);
    return;
}

void GrammerAnalyzer::action525(hebo::LexicalUnit* root) {
    if (root->father->child_node_list[1]->attribute.type != function_table->get_function(curr_func_name).return_type) {
        //say_error("返回值类型不匹配");
    }
    three_address_instruction* return_jump = new three_address_instruction();
    return_jump->index = this->final_instruction.size();
    return_jump->op = "RET";
    return_jump->arg1 = root->father->child_node_list[1]->attribute.addr;
    return_jump->arg2 = "-";
    return_jump->result = "-";
    this->final_instruction.push_back(return_jump);
    return;
}
