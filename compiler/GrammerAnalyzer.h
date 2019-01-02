#pragma once
#include "intput_and_output.hpp"
#include <string>
#include <vector>

class GrammerAnalyzer {
private:
	typedef struct production {
		std::vector<std::string*> production_formula;
		production() {}
	}production;

	std::vector<hebo::LexicalUnit> output_sequence;
	int terminal_number;
	std::string** terminal_list;
	int non_terminal_number;
	std::string** non_terminal_list;
	int production_number;
	int production_action_number;
	std::vector<std::pair<int, int>>* transfer_list;
	production** production_list;
	int table_number;
	std::vector<std::vector<std::string*>> action_table;
	std::vector<std::vector<std::string*>> goto_table;
	std::vector<std::string> parameter_list;

public:
    typedef struct {
        int index = -1;
        std::string op;
        std::string arg1;
        std::string arg2;
        std::string result;
    }three_address_instruction;
    std::vector<three_address_instruction*> final_instruction;
    hbst::SymbolTable* out_table;
    hbst::StructTable* struct_table;
    hbst::FunctionTable* function_table;
	GrammerAnalyzer(std::vector<hebo::LexicalUnit>);
	hebo::LexicalUnit* root;
private:
	void initialization();
	hebo::LexicalUnit* init_tree();
	void output_tree(hebo::LexicalUnit*, int);
	bool compare(std::vector<std::string*>, std::vector<std::string*>);
	void execute_action(int, hebo::LexicalUnit*);
	void say_error(int, std::string, std::string);
	bool check_type(std::string, std::vector<std::string>);
	void clean_param_list();

private:
	void action1(hebo::LexicalUnit*);
	void action2(hebo::LexicalUnit*);
	void action3(hebo::LexicalUnit*);
	void action4(hebo::LexicalUnit*);
	void action5(hebo::LexicalUnit*);
	void action6(hebo::LexicalUnit*);
	void action7(hebo::LexicalUnit*);
	void action8(hebo::LexicalUnit*);
	void action9(hebo::LexicalUnit*);
	void action10(hebo::LexicalUnit*);
	void action11(hebo::LexicalUnit*);
	void action12(hebo::LexicalUnit*);
	void action13(hebo::LexicalUnit*);
	void action14(hebo::LexicalUnit*);
	void action15(hebo::LexicalUnit*);
	void action16(hebo::LexicalUnit*);
	void action17(hebo::LexicalUnit*);
	void action18(hebo::LexicalUnit*);
	void action19(hebo::LexicalUnit*);
	void action20(hebo::LexicalUnit*);
	void action21(hebo::LexicalUnit*);
	void action22(hebo::LexicalUnit*);
	void action23(hebo::LexicalUnit*);
	void action24(hebo::LexicalUnit*);
	void action25(hebo::LexicalUnit*);
	void action26(hebo::LexicalUnit*);
	void action27(hebo::LexicalUnit*);


	void action101(hebo::LexicalUnit*);
	void action102(hebo::LexicalUnit*);
	void action103(hebo::LexicalUnit*);
	void action104(hebo::LexicalUnit*);
	void action105(hebo::LexicalUnit*);
	void action106(hebo::LexicalUnit*);
	void action107(hebo::LexicalUnit*);
	void action108(hebo::LexicalUnit*);
	void action109(hebo::LexicalUnit*);
	void action110(hebo::LexicalUnit*);
	void action111(hebo::LexicalUnit*);
	void action112(hebo::LexicalUnit*);
	void action113(hebo::LexicalUnit*);


	void action201(hebo::LexicalUnit*);
	void action202(hebo::LexicalUnit*);
	void action203(hebo::LexicalUnit*);
	void action204(hebo::LexicalUnit*);

	void action211(hebo::LexicalUnit*);
	void action212(hebo::LexicalUnit*);
	void action213(hebo::LexicalUnit*);

	void action214(hebo::LexicalUnit*);
	void action215(hebo::LexicalUnit*);


	void action216(hebo::LexicalUnit*);
	void action217(hebo::LexicalUnit*);
	void action218(hebo::LexicalUnit*);

	void action219(hebo::LexicalUnit*);
	void action220(hebo::LexicalUnit*);
	void action221(hebo::LexicalUnit*);
	void action222(hebo::LexicalUnit*);

	void action223(hebo::LexicalUnit*);
	void action224(hebo::LexicalUnit*);

	void action225(hebo::LexicalUnit*);
	void action226(hebo::LexicalUnit*);
	void action227(hebo::LexicalUnit*);
	void action228(hebo::LexicalUnit*);
	void action229(hebo::LexicalUnit*);
	void action230(hebo::LexicalUnit*);
	void action231(hebo::LexicalUnit*);
	void action232(hebo::LexicalUnit*);
	void action233(hebo::LexicalUnit*);
	void action234(hebo::LexicalUnit*);
	void action235(hebo::LexicalUnit*);
	void action236(hebo::LexicalUnit*);
	void action237(hebo::LexicalUnit*);
	void action238(hebo::LexicalUnit*);
	void action239(hebo::LexicalUnit*);
	void action240(hebo::LexicalUnit*);
	void action241(hebo::LexicalUnit*);
	void action242(hebo::LexicalUnit*);

	void action301(hebo::LexicalUnit*);
	void action302(hebo::LexicalUnit*);
	void action303(hebo::LexicalUnit*);
	void action304(hebo::LexicalUnit*);
	void action305(hebo::LexicalUnit*);


	void action401(hebo::LexicalUnit*);
	void action402(hebo::LexicalUnit*);
	void action403(hebo::LexicalUnit*);
	void action404(hebo::LexicalUnit*);

	void action405(hebo::LexicalUnit*);
	void action406(hebo::LexicalUnit*);
	void action407(hebo::LexicalUnit*);

	void action408(hebo::LexicalUnit*);
	void action409(hebo::LexicalUnit*);

	void action410(hebo::LexicalUnit*);
	void action411(hebo::LexicalUnit*);
	void action412(hebo::LexicalUnit*);
	void action413(hebo::LexicalUnit*);
	void action414(hebo::LexicalUnit*);
	void action415(hebo::LexicalUnit*);
	void action416(hebo::LexicalUnit*);
	void action417(hebo::LexicalUnit*);
	void action418(hebo::LexicalUnit*);
	void action419(hebo::LexicalUnit*);
	void action420(hebo::LexicalUnit*);
	void action421(hebo::LexicalUnit*);
	void action422(hebo::LexicalUnit*);
	void action423(hebo::LexicalUnit*);
	void action424(hebo::LexicalUnit*);

	void action425(hebo::LexicalUnit*);
	void action426(hebo::LexicalUnit*);
	void action427(hebo::LexicalUnit*);


	void action501(hebo::LexicalUnit*);
	void action502(hebo::LexicalUnit*);
	void action503(hebo::LexicalUnit*);
	void action504(hebo::LexicalUnit*);

	void action505(hebo::LexicalUnit*);
	void action506(hebo::LexicalUnit*);
	void action507(hebo::LexicalUnit*);
	void action508(hebo::LexicalUnit*);

	void action509(hebo::LexicalUnit*);
	void action510(hebo::LexicalUnit*);
	void action511(hebo::LexicalUnit*);
	void action512(hebo::LexicalUnit*);
	void action513(hebo::LexicalUnit*);

	void action514(hebo::LexicalUnit*);
	void action515(hebo::LexicalUnit*);
	void action516(hebo::LexicalUnit*);

	void action517(hebo::LexicalUnit*);
	void action518(hebo::LexicalUnit*);
	void action519(hebo::LexicalUnit*);
	void action520(hebo::LexicalUnit*);
	void action521(hebo::LexicalUnit*);

	void action522(hebo::LexicalUnit*);

	void action523(hebo::LexicalUnit*);
};