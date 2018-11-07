#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<set>
#include<map>

using namespace std;

class Min_DFA {
public:
	vector<set<int>> vec;
	int dfa_s;
	int n_dfa_states;
	int n_chars;
	int** matrix;

	set<int> start_set;
	set<int> final_set;

	vector<vector<int>>ans;
	map<int, string>map_ans;
	int start_state_ans;

	Min_DFA(map<int, string> dfa_end, int** dfa_map, int dfa_s, int n_dfa_states, int n_chars) {
		this->matrix = dfa_map;
		this->dfa_s = dfa_s;
		this->n_dfa_states = n_dfa_states;
		this->n_chars = n_chars;
		int final_state_num = dfa_end.size();
		set<int>* final_set_list = new set<int>[final_state_num];
		int final_count = 0;
		for (map<int, string>::iterator it = dfa_end.begin(); it != dfa_end.end(); it++) {
			final_set.insert((*it).first);
			bool flag = false;
			for (int t = 0; t < final_count; t++) {
				if (dfa_end.find(*(final_set_list[t].begin()))->second == it->second) {
					flag = true;
					final_set_list[t].insert(it->first);
					break;
				}
			}
			if (flag == false) {
				final_set_list[final_count].insert(it->first);
				final_count++;
			}
		}
		for (int i = 0; i < final_count; i++) {
			vec.push_back(final_set_list[i]);
		}
		for (int i = 1; i < n_dfa_states; i++) {
			if (final_set.find(i) == final_set.end()) {
				start_set.insert(i);
			}
		}
		vec.push_back(start_set);
		int count_flag = size(vec);
		while (count_flag != 0) {
			vector<set<int>>::iterator it = vec.begin();
			set<int> temp = *it;
			if (size(temp) == 1) {
				vec.erase(vec.begin());
				vec.push_back(temp);
				count_flag--;
				continue;
			}
			else {
				if (break_up(temp)) {
					count_flag = size(vec) - 1;
				}
				else {
					count_flag--;
				}
			}
			vec.erase(vec.begin());
		}
		map<int, int> final_select;
		int* remain_select = new int[vec.size() + 1];
		final_select.insert(pair<int, int>(0, 0));
		int i = 1;
		for (vector<set<int>>::iterator it = vec.begin(); it != vec.end(); it++, i++) {
			final_select.insert(pair<int, int>(*((*it).begin()), i));
			remain_select[i] = *((*it).begin());
		}
		vector<vector<int>> ans;
		vector<int>vec0;
		for (int i = 0; i < this->n_chars; i++) {
			vec0.push_back(0);
		}
		ans.push_back(vec0);
		for (unsigned int i = 1; i <= vec.size(); i++) {
			int line_number = remain_select[i];
			vector<int> vec_temp;
			for (int j = 0; j < this->n_chars; j++) {
				int alter = get_begin(matrix[j][line_number]);
				vec_temp.push_back((final_select.find(alter))->second);
			}
			ans.push_back(vec_temp);
		}
		start_state_ans = final_select.find(get_begin(this->dfa_s))->second;
		bool* has_appended = new bool[vec.size() + 1];
		for (unsigned int i = 0; i < vec.size() + 1; i++) {
			has_appended[i] = false;
		}
		for (map<int, string>::iterator it = dfa_end.begin(); it != dfa_end.end(); it++) {
			int temp = it->first;
			int dest = final_select.find(get_begin(temp))->second;
			if (has_appended[dest] == false) {
				this->map_ans.insert(pair<int, string>(dest, it->second));
				has_appended[dest] = true;
			}
		}
		ofstream outfile("ans.txt");
		outfile << "n_chars:" << this->n_chars << endl;
		outfile << "n_dfa_states:" << vec.size() + 1 << endl;
		outfile << "start_state_ans:" << this->start_state_ans << endl;
		outfile << "matrix:" << endl;
		for (vector<vector<int>>::iterator it1 = ans.begin(); it1 != ans.end(); it1++) {
			vector<int> temp_vec = *it1;
			for (vector<int>::iterator it2 = temp_vec.begin(); it2 != temp_vec.end(); it2++) {
				outfile << *it2 << ' ';
			}
			outfile << endl;
		}
		outfile << "map:" << endl;
		for (map<int, string>::iterator it = map_ans.begin(); it != map_ans.end(); it++) {
			outfile << (*it).first << " " << (*it).second << endl;
		}
	}

	int get_begin(int destination) {
		for (vector<set<int>>::iterator it = vec.begin(); it != vec.end(); it++) {
			if ((*it).find(destination) != (*it).end()) {
				return *((*it).begin());
			}
		}
		return -10000;
	}

	int get_position(int destination) {
		int i = 1;
		for (vector<set<int>>::iterator it = vec.begin(); it != vec.end(); it++, i++) {
			if ((*it).find(destination) != (*it).end()) {
				return i;
			}
		}
		return 0;
	}

	bool break_up(set<int> origin_set) {
		int large = vec.size()+1;
		set<int>* set_pointer = new set<int>[large];
		for (int i = 0; i < this->n_chars; i++) {
			for (set<int>::iterator it = origin_set.begin(); it != origin_set.end(); it++) {
				int temp = matrix[i][*it];
				int result = get_position(temp);
				set_pointer[result].insert(*it);
			}
			bool flag = false;
			for (int i = 0; i < large; i++) {
				if (size(set_pointer[i]) == size(origin_set)) {
					set_pointer[i].clear();
					flag = true;
					break;
				}
			}
			if (flag == false) {
				for (int i = 0; i < large; i++) {
					if (set_pointer[i].size() > 0 && set_pointer[i].size() < origin_set.size()) {
						vec.push_back(set_pointer[i]);
					}
					else {
						continue;
					}
				}
				delete[] set_pointer;
				return true;
			}
		}
		vec.push_back(origin_set);
		delete[] set_pointer;
		return false;
	}
};