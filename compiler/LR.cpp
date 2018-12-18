#include "LR.hpp"

namespace lr
{

	LALR1Item::LALR1Item()
	{

	}


	LALR1Item::LALR1Item(cfg::Production* production_, int position_)
		:production(production_), position(position_)
	{

	}






	LALR::LALR(const cfg::ContextFreeGrammar & context_free_grammar_) :
		terminal_set(context_free_grammar_.terminal_set),
		nonterminal_set(context_free_grammar_.nonterminal_set),
		start_symbol(context_free_grammar_.start_symbol)
	{
		for each(auto production in context_free_grammar_.production_set)
		{
			for (int i = 0; i < production->right.size() + 1; i++)
			{
				item_set.insert(new LALR1Item(production, i));
			}
		}
		for each(auto item in item_set)
		{
			if (item->production->left == start_symbol && item->position == 0)
			{
				argumented_grammar_start = item;
				break;
			}
		}
	}

	void LALR::get_kernel()
	{
		std::ofstream lalr_txt("lalr.txt");
		lalr_txt << terminal_set.size() << '\t' << nonterminal_set.size() << '\t' << item_set.size() << endl;
		unordered_set<LALR1Item*, item_pointer_hash, item_pointer_hash_compare> first_set;
		first_set.insert(argumented_grammar_start);
		kernel_status_vector.push_back(first_set);
		//对于每一个项目集核
		//先求闭包, 然后找GO函数
		for (int i = 0; i < kernel_status_vector.size(); i++)
		{
			cout << i << endl;
			auto closure_set = kernel_status_vector[i];
			LR0_closure(closure_set);
			lalr_txt << i << endl;
			for each (auto item in kernel_status_vector[i])
			{
				lalr_txt << *item << endl;
			}
			lalr_txt << endl;

			kernel_action_table.push_back(map<cfg::Terminal*, string>());
			kernel_goto_table.push_back(map < cfg::Nonterminal*, int>());

			for each(auto terminal in terminal_set)
			{
				unordered_set<LALR1Item*, item_pointer_hash, item_pointer_hash_compare> kernel_set;
				for each (auto item in closure_set)
				{
					if (item->production->right.size() == item->position)
					{
						continue;
					}
					if (item->production->right[item->position] == terminal)
					{
						auto my_next = new LALR1Item(item->production, item->position + 1);
						auto result = item_set.insert(my_next);
						assert(!result.second);
						kernel_set.insert(*result.first);
					}
				}
				if (!kernel_set.empty())
				{
					int order = 0;
					bool need_pushing_back = true;
					// 去重操作 vector遍历 慢
					// map<unordered_set, int> 怎么样？
					for (order = 0; order < kernel_status_vector.size(); order++)
					{
						if (kernel_status_vector[order] == kernel_set)
						{
							need_pushing_back = false;
							break;
						}
					}
					if (need_pushing_back)
					{
						kernel_status_vector.push_back(kernel_set);
					}
					std::stringstream ss;
					ss.clear();
					ss << order;
					kernel_action_table[i].insert(std::make_pair(terminal, "s" + ss.str()));
				}
			}
			for each (auto nonterminal in nonterminal_set)
			{
				unordered_set<LALR1Item*, item_pointer_hash, item_pointer_hash_compare> kernel_set;
				for each (auto item in closure_set)
				{
					if (item->production->right.size() == item->position)
					{
						continue;
					}
					if (item->production->right[item->position] == nonterminal)
					{
						auto my_next = new LALR1Item(item->production, item->position + 1);
						auto result = item_set.insert(my_next);
						assert(!result.second);
						kernel_set.insert(*result.first);
					}
				}
				if (!kernel_set.empty())
				{
					int order = 0;
					bool need_pushing_back = true;
					for (order = 0; order < kernel_status_vector.size(); order++)
					{
						if (kernel_status_vector[order] == kernel_set)
						{
							need_pushing_back = false;
							break;
						}
					}
					if (need_pushing_back)
					{
						kernel_status_vector.push_back(kernel_set);
					}
					kernel_goto_table[i].insert(std::make_pair(nonterminal, order));
				}
			}
		}
		assert(kernel_action_table.size() == kernel_status_vector.size());
	}

	// Get a closuer of a status.
	void LALR::LR0_closure(unordered_set<LALR1Item*, item_pointer_hash, item_pointer_hash_compare>& closure_set)
	{
		queue<LALR1Item*> q;
		for each(auto item in closure_set)
		{
			q.push(item);
		}
		while (!q.empty())
		{
			auto current_item = q.front();
			q.pop();
			for each(auto nonterminal in nonterminal_set)
			{
				if (current_item->production->right.size() == current_item->position)
				{
					continue;
				}
				if (current_item->production->right[current_item->position] == nonterminal)
				{
					// 把所有nonterminal开头、position=0的项目放进closure_set
					for each(auto item in item_set)
					{
						if (item->production->left == nonterminal && item->position == 0)
						{
							if (closure_set.insert(item).second)
							{
								q.push(item);
							}
						}
					}
					// 对于一个产生式而言, 至多一个nonterminal符合添加条件.
					break;
				}
			}
		}

	}



	LALR::LALR()
	{

	}

	LALR::~LALR()
	{

	}

	std::ostream& operator<<(std::ostream& out, LALR1Item item)
	{
		return out << *(item.production) << '\t' << item.position;
	}

}

