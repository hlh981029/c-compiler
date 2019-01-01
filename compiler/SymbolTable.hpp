#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<sstream>
#include<map>
namespace hbst
{
	class SymbolItem
	{
		static int symbol_count;
	public:
		SymbolItem();
		std::string address;
		std::string name;
		std::string type;
		int offset;
		int width;
		SymbolItem(std::string _name, std::string _type, int _offset, int _width);
	};

	class SymbolTable
	{
		static int symbol_table_count;
		void put_struct(std::string object_name, std::string struct_name);
		void put_struct_array(std::string array_name, std::string struct_name, int length);
	public:
		SymbolTable* father;
		std::vector<SymbolItem> symbol_item_vector;
		std::string symbol_table_name;
		std::vector<SymbolTable*> son_vector;

		SymbolTable();
		SymbolTable(std::string _name, SymbolTable* _father = nullptr);
		SymbolTable(const SymbolTable& copied);

		void put_symbol(const SymbolItem& symbol) throw(std::string);
		SymbolItem& get_symbol(std::string symbol_name) throw(std::string);
		SymbolItem& get_symbol_from_address(std::string symbol_address) throw(std::string);
		


		~SymbolTable();
	};

	class StructItem
	{
	public:
		std::string name;
		SymbolTable symbol_table;

		StructItem();
		StructItem(std::string _name, SymbolTable _symbol_table);
	};


	class StructTable
	{
	public:
		std::vector<StructItem> struct_item_vector;
		StructItem& put_struct(const StructItem& struct_item) throw(std::string);
		StructItem& get_struct(std::string struct_name) throw(std::string);
		StructTable();
	};



	class FunctionItem
	{
	public:
		std::string name;
		std::string return_type;
		std::vector<std::string> parameter_vector;
		void add_parameter(std::string parameter);
		FunctionItem();
		FunctionItem(std::string _name, std::string _return_type);
	};


	class FunctionTable
	{
	public:
		std::vector<FunctionItem> function_item_vector;
		FunctionTable();
		void put_function(const FunctionItem& function_item) throw(std::string);
		FunctionItem& get_function(std::string name) throw(std::string);
	};
}
extern std::map<std::string, int> constant_map;
extern hbst::SymbolTable global_symbol_table;
extern hbst::StructTable global_struct_table;
extern hbst::FunctionTable global_function_table;