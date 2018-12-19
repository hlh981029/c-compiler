#include "LR.hpp"

namespace lr
{

	LALR1Item::LALR1Item() :is_kernel(true)
	{

	}


	LALR1Item::LALR1Item(cfg::Production* production_, int position_, cfg::Terminal* sentence_ending_, int order_)
		:production(production_), position(position_), is_kernel(true),order(order_)
	{
		if (sentence_ending_ != nullptr)
		{
			lookaheads.insert(sentence_ending_);
		}

	}






	LALR::LALR(const cfg::ContextFreeGrammar & context_free_grammar_) :
		terminal_set(context_free_grammar_.terminal_set),
		nonterminal_set(context_free_grammar_.nonterminal_set),
		start_symbol(context_free_grammar_.start_symbol)
	{
		auto result = terminal_set.insert(new cfg::Terminal("$"));
		sentence_ending = *result.first;
		int production_order = 0;
		for each(auto production in context_free_grammar_.production_set)
		{
			for (int i = 0; i < production->right.size() + 1; i++)
			{
				cout << i << endl;
				cout << *production->left << endl;
				lr0_item_set.insert(new LALR1Item(production, i, sentence_ending,production_order));
			}
			production_order++;
		}
		int exchanged_order_number = -1;
		for each(auto item in lr0_item_set)
		{
			if (item->production->left == start_symbol && item->position == 0)
			{
				argumented_grammar_start = item;
				exchanged_order_number = item->order;
				break;
			}
		}
		if (exchanged_order_number)
		{
			for each(auto item in lr0_item_set)
			{
				if (item->order== 0)
				{
					item->order = exchanged_order_number;
					argumented_grammar_start->order = 0;
					break;
				}
			}
		}
	}

	void LALR::get_kernel()
	{
		unordered_set<LALR1Item*, item_pointer_hash, item_pointer_hash_compare> first_set;
		LALR1Item* start = new LALR1Item(argumented_grammar_start->production, argumented_grammar_start->position, sentence_ending, argumented_grammar_start->order);
		start->is_kernel = true;
		first_set.insert(start);
		kernel_status_vector.push_back(first_set);
		// 查重集
		// 查重相同的核
		// unordered_map<unordered_set<LALR1Item*, item_pointer_hash, item_pointer_hash_compare>,int ,unordered_set_lalr_item_hash> distincted_map;
		//对于每一个项目集核
		//先求闭包, 然后找GO函数
		for (int i = 0; i < kernel_status_vector.size(); i++)
		{
			cout << i << endl;
			auto closure_set = kernel_status_vector[i];
			LR0_closure(closure_set);

			//kernel_action_vector.push_back(map<cfg::Terminal*, string>());
			//kernel_go_vector.push_back(map < cfg::Nonterminal*, int>());
			kernel_goto_vector.push_back(map<cfg::Symbol*, int>());
			// 输入一个终结符, 状态转换
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
						LALR1Item* insert_item = new LALR1Item(item->production, item->position + 1, sentence_ending,item->order);
						insert_item->is_kernel = true;
						kernel_set.insert(insert_item);
					}
				}
				if (!kernel_set.empty())
				{
					int order = 0;
					bool need_pushing_back = true;
					// 去重操作 vector遍历 慢
					// 外加一个map<unordered_set,int>辅助查询？
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
					//kernel_action_vector[i].insert(std::make_pair(terminal, "s" + ss.str()));
					kernel_goto_vector[i].insert(std::make_pair(terminal, order));
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
						LALR1Item* insert_item = new LALR1Item(item->production, item->position + 1, sentence_ending,item->order);
						insert_item->is_kernel = true;
						kernel_set.insert(insert_item);
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
					//kernel_go_vector[i].insert(std::make_pair(nonterminal, order));
					kernel_goto_vector[i].insert(std::make_pair(nonterminal, order));
				}
			}
			int delete_count = 0;
			for each(auto item in closure_set)
			{
				if (item->is_kernel == false)
				{
					delete item;
					delete_count++;
				}
			}
			cout << "delete count: " << delete_count << endl;
		}
		assert(kernel_goto_vector.size() == kernel_status_vector.size());
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
			if (current_item->production->right.size() == current_item->position)
			{
				continue;
			}
			for each(auto nonterminal in nonterminal_set)
			{

				if (current_item->production->right[current_item->position] == nonterminal)
				{
					// 把所有nonterminal开头、position=0的项目放进closure_set
					for each(auto item in lr0_item_set)
					{
						if (item->production->left == nonterminal && item->position == 0)
						{
							LALR1Item* insert_item = new LALR1Item(item->production, item->position, nullptr,item->order);
							insert_item->is_kernel = false;
							if (closure_set.insert(insert_item).second)
							{
								q.push(insert_item);
							}
							else
							{
								delete insert_item;
							}
						}
					}
					// 对于一个产生式而言, 至多一个nonterminal符合添加条件.
					break;
				}
			}
		}
	}

	void LALR::LALR_closuer(unordered_set<LALR1Item*, item_pointer_hash, item_pointer_hash_compare>& closure_set)
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
			if (current_item->production->right.size() == current_item->position)
			{
				continue;
			}
			for each(auto nonterminal in nonterminal_set)
			{
				if (current_item->production->right[current_item->position] == nonterminal)
				{
					// 把所有nonterminal开头、position=0的项目放进closure_set
					for each(auto item in lr0_item_set)
					{
						if (item->production->left == nonterminal && item->position == 0)
						{
							LALR1Item* insert_item = new LALR1Item(item->production, item->position, nullptr,item->order);
							auto result = closure_set.insert(insert_item);
							// 无论是否之前有同心项 都需要更新先前看符号
							if (current_item->position + 1 >= current_item->production->right.size())
							{
								for each (auto terminal in current_item->lookaheads)
								{
									(*result.first)->lookaheads.insert(terminal);
								}
							}
							else
							{
								for each(auto terminal in current_item->production->right[current_item->position + 1]->first_set)
								{
									(*result.first)->lookaheads.insert(terminal);
								}
							}
							insert_item->is_kernel = false;
							// 插入成功 之前没有重复
							if (result.second)
							{
								q.push(insert_item);
							}
							else
							{
								delete insert_item;
							}
						}
					}
					// 对于一个产生式而言, 至多一个nonterminal符合添加条件.
					break;
				}
			}
		}
	}

	// Can be optimized
	void LALR::get_spontaneous_lookaheads_and_spreading_lookaheads()
	{
		for (int i = 0; i < kernel_status_vector.size(); i++)
		{
			for each (auto kernel_item in kernel_status_vector[i])
			{
				unordered_set<LALR1Item*, item_pointer_hash, item_pointer_hash_compare> closure_set;
				closure_set.insert(kernel_item);
				LALR_closuer(closure_set);
				for each (auto item in closure_set)
				{
					if (item->production->right.size() == item->position)
					{
						continue;
					}
					for each (auto terminal in item->lookaheads)// 对于每一个先前看符号
					{
						if (terminal == sentence_ending)// 传播
						{
							for each(auto next_item in kernel_status_vector[kernel_goto_vector[i][item->production->right[item->position]]])
							{
								if (next_item->production == item->production && next_item->position == item->position + 1)
								{
									spreading_lookaheads_vector.push_back(std::make_pair(kernel_item, next_item));
									break;
								}
							}
						}
						else//自产生
						{
							for each (auto next_item in kernel_status_vector[kernel_goto_vector[i][item->production->right[item->position]]])
							{
								if (next_item->production == item->production && next_item->position == item->position + 1)
								{
									spontaneous_lookaheads_vector.push_back(std::make_pair(next_item, terminal));
									break;
								}
							}
						}
					}
				}
				for each (auto item in closure_set)
				{
					if (item != kernel_item)
					{
						delete item;
					}
				}
			}
		}
	}

	void LALR::set_spontaneous_lookaheads()
	{
		for each (auto status_set in kernel_status_vector)
		{
			for each (auto item in status_set)
			{
				item->lookaheads.empty();
			}
		}
		assert(kernel_status_vector[0].size() == 1);

		(*kernel_status_vector[0].begin())->lookaheads.insert(sentence_ending);

		for each (auto spontaneous_pair in spontaneous_lookaheads_vector)
		{
			spontaneous_pair.first->lookaheads.insert(spontaneous_pair.second);
		}

	}
	void LALR::spread_lookaheads()
	{
		bool need_spread = true;
		int count = 0;
		while (need_spread)
		{
			cout << ++count << endl;
			need_spread = false;
			for each (auto spreading_pair in spreading_lookaheads_vector)
			{
				for each (auto fommer_lookaheads in spreading_pair.first->lookaheads)
				{
					need_spread = spreading_pair.second->lookaheads.insert(fommer_lookaheads).second ? true : need_spread;
				}
			}
		}
	}

	void LALR::get_full_status_vector()
	{
		for (int i = 0; i < kernel_status_vector.size(); i++)
		{
			unordered_set<LALR1Item*, item_pointer_hash, item_pointer_hash_compare> closure_set = kernel_status_vector[i];
			LALR_closuer(closure_set);
			status_vector.push_back(closure_set);
			assert(status_vector.size() == i + 1);
		}
	}

	void LALR::serialize_symbol()
	{
		assert(terminal_vector.empty() && nonterminal_vector.empty());
		for each (auto terminal in terminal_set)
		{
			terminal_vector.push_back(terminal);
			terminal_to_int_map.insert(std::make_pair(terminal, terminal_vector.size() - 1));
		}
		for each (auto nonterminal in nonterminal_set)
		{
			nonterminal_vector.push_back(nonterminal);
			nonterminal_to_int_map.insert(std::make_pair(nonterminal, nonterminal_vector.size() - 1));
		}
		int start_symbol_position = -1;
		for (int i = 0; i < nonterminal_vector.size(); i++)
		{
			if (nonterminal_vector[i] == start_symbol)
			{
				start_symbol_position = i;
				break;
			}
		}
		if(start_symbol_position)
		{
			auto temp = nonterminal_vector[0];
			nonterminal_vector[0] = start_symbol;
			nonterminal_vector[start_symbol_position] = temp;
			nonterminal_to_int_map[temp] = start_symbol_position;
			nonterminal_to_int_map[start_symbol] = 0;
		}

		assert(terminal_set.size() == terminal_vector.size() && terminal_vector.size() == terminal_to_int_map.size());
		assert(nonterminal_set.size() == nonterminal_vector.size() && nonterminal_vector.size() == nonterminal_to_int_map.size());

	}

	void LALR::make_action_and_go()
	{
		for (int i = 0; i < kernel_goto_vector.size(); i++)
		{
			action_vector.push_back(vector<string>(terminal_set.size(), "e"));
			go_vector.push_back(vector<int>(nonterminal_set.size(), -1));
			for each (auto trans_pair in kernel_goto_vector[i])
			{
				if (trans_pair.first->get_id() == cfg::Identify::Terminal)
				{
					std::stringstream ss;
					ss.clear();
					ss<<trans_pair.second;
					action_vector[i][terminal_to_int_map[dynamic_cast<cfg::Terminal*> (trans_pair.first)]] = "s" + ss.str();
					ss.clear();
				}
				if (trans_pair.first->get_id() == cfg::Identify::Nonterminal)
				{
					go_vector[i][nonterminal_to_int_map[dynamic_cast<cfg::Nonterminal*> (trans_pair.first)]] = trans_pair.second;
				}
			}
			for each (auto item in status_vector[i])
			{
				if (item->production->right.size() == item->position)
				{
					for each (auto terminal in item->lookaheads)
					{
						std::stringstream ss;
						ss.clear();
						ss << item->order;
						if(action_vector[i][terminal_to_int_map[terminal]][0] == 'e')
						{
							action_vector[i][terminal_to_int_map[terminal]] = "r" + ss.str();
						}
						else
						{
							action_vector[i][terminal_to_int_map[terminal]] += "r" + ss.str();
						}
					}
				}
			}
		}
	}

	void LALR::output()
	{
		std::ofstream txt("lalr.txt");
		txt << terminal_vector.size() << endl;
		for each (auto terminal in terminal_vector)
		{
			txt << *terminal << endl;
		}
		txt << nonterminal_vector.size();
		for each (auto nonterminal in nonterminal_vector)
		{
			txt << *nonterminal << endl;
		}
		txt << status_vector.size() << endl;
		for each (auto vec in action_vector)
		{
			for each (auto str in vec)
			{
				txt << str << ' ';
			}
			txt << endl;
		}
		for each (auto vec in go_vector)
		{
			for each (auto status in vec)
			{
				txt << status << ' ';
			}
			txt << endl;
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

