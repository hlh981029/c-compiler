#include "SymbolTable.hpp"

namespace hbst
{
	int SymbolItem::symbol_count = 0;
	int SymbolTable::symbol_table_count = 0;
	SymbolTable::SymbolTable() :father(nullptr)
	{
		std::stringstream ss;
		ss.clear();
		ss << symbol_table_count;
		symbol_table_name = ss.str();

		symbol_table_count += 1;
	}

	SymbolTable::SymbolTable(SymbolTable* _father)
		:father(_father)
	{
		std::stringstream ss;
		ss.clear();
		ss << symbol_table_count;
		symbol_table_name = ss.str();
		father->son_vector.push_back(this);
		symbol_table_count += 1;
	}

	SymbolTable::SymbolTable(const SymbolTable & copied)
		:father(copied.father), symbol_item_vector(copied.symbol_item_vector)
	{
		std::stringstream ss;
		ss.clear();
		ss << symbol_table_count;
		symbol_table_name = ss.str();
		father->son_vector.push_back(this);
		std::cerr << "The copied constructor is not supposed to be called." << std::endl;
		system("pause");
		symbol_table_count += 1;
	}

	void SymbolTable::put_symbol(const SymbolItem& symbol) throw(std::string)
	{
		for (int i = 0; i < symbol_item_vector.size(); i++)
		{
			if (symbol_item_vector[i].name == symbol.name)
			{
				throw std::string("duplicated declaration");
			}
		}
		symbol_item_vector.push_back(symbol);
	}

	SymbolItem & SymbolTable::get_symbol(std::string symbol_name) throw(std::string)
	{
		// TODO: 在此处插入 return 语句
		for (SymbolTable* current_table = this; current_table != nullptr; current_table = current_table->father)
		{
			for (int i = 0; i < current_table->symbol_item_vector.size(); i++)
			{
				if (current_table->symbol_item_vector[i].name == symbol_name)
				{
					return current_table->symbol_item_vector[i];
				}
			}
		}
		throw std::string("no such symbol in this symbol table");
	}


	SymbolTable::~SymbolTable()
	{

	}




	SymbolItem::SymbolItem()
	{
		//std::stringstream ss;
		//ss.clear();
		//ss << symbol_count;
		//address = name + "$" + ss.str();
		//symbol_count += 1;

	}

	SymbolItem::SymbolItem(std::string _name, std::string _type, int _offset, int _width)
		: name(_name), type(_type), offset(_offset), width(_width)
	{
		std::stringstream ss;
		ss.clear();
		ss << symbol_count;
		address = name + "$" + ss.str();
		symbol_count += 1;
	}

    SymbolItem::SymbolItem(std::string _name, std::string _type, int _width, std::string _addr)
        : name(_name), type(_type), offset(0), width(_width), address(_addr)
    {
    }

	StructItem::StructItem()
	{

	}
	StructItem::StructItem(std::string _name) :name(_name)
	{

	}
	void StructTable::put_struct(const StructItem & function_item) throw(std::string)
	{
		for (int i = 0; i < struct_item_vector.size(); i++)
		{
			if (struct_item_vector[i].name == function_item.name)
			{
				throw std::string("duplicated declaration for struct");
			}
		}
		struct_item_vector.push_back(function_item);
	}

	StructItem & StructTable::get_struct(std::string struct_name) throw(std::string)
	{
		for (int i = 0 * struct_item_vector.size(); i < struct_item_vector.size(); i++)
		{
			if (struct_item_vector[i].name == struct_name)
			{
				return struct_item_vector[i];
			}
		}
		throw std::string("no such struct in this struct table");
	}

	StructTable::StructTable()
	{

	}
	FunctionItem::FunctionItem()
	{

	}

    FunctionItem::FunctionItem(std::string _name, std::string _return_type)
    {
        name = _name;
        return_type = _return_type;
    }

	void FunctionItem::add_parameter(std::string parameter)
	{
		parameter_vector.push_back(parameter);
	}

	FunctionTable::FunctionTable()
	{

	}

	void FunctionTable::put_function(const FunctionItem & function_item)throw(std::string)
	{
		for (int i = 0; i < function_item_vector.size(); i++)
		{
			if (function_item.name == function_item_vector[i].name)
			{
				throw std::string("duplicated declaration for function");
			}
		}
		function_item_vector.push_back(function_item);
	}
	FunctionItem & FunctionTable::get_function(std::string name)throw(std::string)
	{
		// TODO: 在此处插入 return 语句
		for (int i = 0; i < function_item_vector.size(); i++)
		{
			if (function_item_vector[i].name == name)
			{
				return function_item_vector[i];
			}
		}
		throw std::string("no such function in this function table");

	}
}


