#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdarg.h>
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
        SymbolItem(std::string _name, std::string _type, int _width, std::string _addr);
	};

	class SymbolTable
	{
		static int symbol_table_count;
	public:
		SymbolTable* father;
		std::vector<SymbolItem> symbol_item_vector;
		std::string symbol_table_name;
		std::vector<SymbolTable*> son_vector;

		SymbolTable();
		SymbolTable(SymbolTable* _father);
		SymbolTable(const SymbolTable& copied);

		void put_symbol(const SymbolItem& symbol) throw(std::string);
		SymbolItem& get_symbol(std::string symbol_name) throw(std::string);

		~SymbolTable();
	};

	class StructItem
	{
	public:
		std::string name;
		SymbolTable symbol_table;
		StructItem();
		StructItem(std::string _name);
	};


	class StructTable
	{
	public:
		std::vector<StructItem> struct_item_vector;
		void put_struct(const StructItem& function_item) throw(std::string);
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

