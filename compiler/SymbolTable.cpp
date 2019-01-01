#include "SymbolTable.hpp"
#include<assert.h>
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



	SymbolTable::SymbolTable(std::string _name, SymbolTable* _father)
		: symbol_table_name(_name), father(_father)
	{
		if (symbol_table_name.empty())
		{
			std::stringstream ss;
			ss.clear();
			ss << symbol_table_count;
			symbol_table_name = ss.str();
		}
		if (father != nullptr)
		{
			father->son_vector.push_back(this);
		}
		symbol_table_count += 1;
	}

	SymbolTable::SymbolTable(const SymbolTable & copied)
		:father(copied.father), symbol_item_vector(copied.symbol_item_vector)
	{
		if (father != nullptr)
		{
			father->son_vector.push_back(this);
		}
	}

	void SymbolTable::put_symbol(const SymbolItem& symbol) throw(std::string)
	{
		if (!symbol.name.empty())
		{
			for (int i = 0; i < symbol_item_vector.size(); i++)
			{
				if (symbol_item_vector[i].name == symbol.name)
				{
					throw std::string("duplicated declaration");
				}
			}
		}
		symbol_item_vector.push_back(symbol);
		// 插入一个结构体和插入一个结构体数组
		if (symbol.type.find('$') != std::string::npos && symbol.type.find(' ') != std::string::npos)
			//有空格 有$ 下一步看是否有'['
		{
			if (std::string(symbol.type, 0, symbol.type.find(' ')) == "struct")
			{
				if (symbol.type.find('[') != std::string::npos&& symbol.type.find(']'))
				{
					//有'[]' 是结构体数组
					std::string struct_name_with_dollar(symbol.type, symbol.type.find(' ') + 1, symbol.type.find('[') - symbol.type.find(' ') - 1);
					std::string array_length_string(symbol.type, symbol.type.find('[') + 1, symbol.type.find(']') - symbol.type.find('[') - 1);
					// 需要知道当前结构体对象的词素和结构体名字个数组长度
					std::stringstream ss;
					int length;
					ss << array_length_string;
					ss >> length;
					put_struct_array(symbol.name, struct_name_with_dollar, length);
				}
				else
				{
					//没有'[]' 是一个结构体
					std::string struct_name(symbol.type, symbol.type.find(' ') + 1);
					// 需要知道当前结构体对象的词素和结构体名字
					put_struct(symbol.name, struct_name);
				}
			}
		}
	}

	void SymbolTable::put_struct(std::string object_name, std::string struct_name_with_dollar)
	{
		assert(struct_name_with_dollar.find('$') != std::string::npos);
		for each (auto struct_property in global_struct_table.get_struct(struct_name_with_dollar).symbol_table.symbol_item_vector)
		{
			this->put_symbol(SymbolItem(object_name + "$" + struct_property.name, struct_property.type, struct_property.offset, struct_property.width));
		}
	}

	void SymbolTable::put_struct_array(std::string array_name, std::string struct_name_with_dollar, int length)
	{
		assert(struct_name_with_dollar.find('$') != std::string::npos);
		std::string struct_name_without_dollar(struct_name_with_dollar, 0, struct_name_with_dollar.find('$'));
		int width = get_symbol(struct_name_without_dollar).width;
		for (int i = 0; i < length; i++)
		{
			put_symbol(SymbolItem(array_name + "$" + std::to_string(i), "struct " + struct_name_with_dollar, 0, width));
		}
	}

	SymbolItem& SymbolTable::get_symbol(std::string symbol_name) throw(std::string)
	{
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

	SymbolItem & SymbolTable::get_symbol_from_address(std::string symbol_address) throw(std::string)
	{
		for (SymbolTable* current_table = this; current_table != nullptr; current_table = current_table->father)
		{
			for (int i = 0; i < current_table->symbol_item_vector.size(); i++)
			{
				if (current_table->symbol_item_vector[i].address == symbol_address)
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
		std::cerr << "This SymbolItem constructor is not supposed to be called." << std::endl;
		system("pause");
	}

	SymbolItem::SymbolItem(std::string _name, std::string _type, int _offset, int _width)
		: name(_name), type(_type), offset(_offset), width(_width)
	{
		if (type == "function")
		{
			address = name;
		}
		else
		{
			std::stringstream ss;
			ss.clear();
			ss << symbol_count;
			address = name + "$" + ss.str();
			symbol_count++;
		}
		if (name.empty())
		{
			address = "temp" + address;
			name = address;
		}
	}

	StructItem::StructItem()
	{

	}


	StructItem::StructItem(std::string _name, SymbolTable _symbol_table) :name(_name), symbol_table(_symbol_table)
	{

	}




	StructItem& StructTable::put_struct(const StructItem & struct_item) throw(std::string)
	{
		for (int i = 0; i < struct_item_vector.size(); i++)
		{
			if (struct_item_vector[i].name == struct_item.name)
			{
				throw std::string("duplicated declaration for struct");
			}
		}
		struct_item_vector.push_back(struct_item);
		return struct_item_vector[struct_item_vector.size() - 1];
	}


	StructItem& StructTable::get_struct(std::string struct_name) throw(std::string)
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
		:name(_name), return_type(_return_type)
	{

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
hbst::SymbolTable global_symbol_table("global");
hbst::StructTable global_struct_table;
hbst::FunctionTable global_function_table;


auto input_function_symbol_item = hbst::SymbolItem("input", "function", 0, 0);
auto print_function_symbol_item = hbst::SymbolItem("print", "function", 0, 0);

//
//int  useless =
//(
//	global_symbol_table.put_symbol(input_function_symbol_item),
//	global_symbol_table.put_symbol(print_function_symbol_item),
//	global_function_table.put_function(hbst::FunctionItem(input_function_symbol_item.address, "void")),
//	global_function_table.put_function(hbst::FunctionItem(print_function_symbol_item.address, "int")),
//	global_function_table.get_function(print_function_symbol_item.address).add_parameter("int"),
//	1
//	);
int  useless1 =
(
	global_symbol_table.put_symbol(input_function_symbol_item),
	global_symbol_table.put_symbol(print_function_symbol_item),
	global_function_table.put_function(hbst::FunctionItem("input", "void")),
	global_function_table.put_function(hbst::FunctionItem("print", "int")),
	global_function_table.get_function("print").add_parameter("int"),
	1
	);
