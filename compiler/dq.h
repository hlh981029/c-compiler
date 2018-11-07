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
		for (map<int, string>::iterator it = dfa_end.begin(); it != dfa_end.end(); it++) {
			final_set.insert((*it).first);
		}
		for (int i = 0; i < n_dfa_states; i++) {
			if (final_set.find(i) == final_set.end()) {
				start_set.insert(i);
			}
		}
		vec.push_back(start_set);
		vec.push_back(final_set);
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
		int* final_select = new int[vec.size()];
		int i = 0;
		for (vector<set<int>>::iterator it = vec.begin(); it != vec.end(); it++, i++) {
			final_select[i] = *((*it).begin());
		}
		int adjust_start_state = adjust_num(this->dfa_s);
		for (int j = 0; j < vec.size(); j++) {
			if (final_select[j] == adjust_start_state) {
				this->start_state_ans = j + 1;
				break;
			}
		}
		for (map<int, string>::iterator it = dfa_end.begin(); it != dfa_end.end(); it++) {
			int dest = (*it).first;
			int _dest = final_select[get_position(dest)];
			int k = 0;
			for (; k < vec.size(); k++) {
				if (final_select[k] == _dest) {
					break;
				}
			}
			map_ans.insert(pair<int, string>(k + 1, (*it).second));
		}
		vector<int> temp_vec;
		for (int i = 0; i < this->n_chars; i++) {
			temp_vec.push_back(0);
		}
		ans.push_back(temp_vec);
		for (int j = 0; j < vec.size(); j++) {
			vector<int> temp;
			int dest = final_select[j];
			if (dest == 0) {
				continue;
			}
			for (int i = 0; i < this->n_chars; i++) {
				int _dest = adjust_num(matrix[i][dest]);
				int k = 0;
				for (; k < vec.size(); k++) {
					if (final_select[k] == _dest) {
						break;
					}
				}
				temp.push_back(k + 1);
			}
			ans.push_back(temp);
		}
		ofstream outfile("ans.txt");
		outfile << "n_dfa_states:" << vec.size() << " n_chars" << this->n_chars << endl;
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

	int get_position(int destination) {
		int i = 0;
		for (vector<set<int>>::iterator it = vec.begin(); it != vec.end(); it++, i++) {
			if ((*it).find(destination) != (*it).end()) {
				return i;
			}
		}
		return -1;
	}

	int adjust_num(int dest) {
		return *(vec[get_position(dest)].begin());
	}

	bool break_up(set<int> origin_set) {
		set<int>* set_pointer = new set<int>[vec.size()];
		for (int i = 0; i < this->n_chars; i++) {
			for (set<int>::iterator it = origin_set.begin(); it != origin_set.end(); it++) {
				int temp = matrix[i][(*it)];
				int result = get_position(temp);
				set_pointer[result].insert(*it);
			}
			bool flag = false;
			for (unsigned int i = 0; i < vec.size(); i++) {
				if (size(set_pointer[i]) == size(origin_set)) {
					set_pointer[i].clear();
					flag = true;
					break;
				}
			}
			if (flag == false) {
				for (unsigned int i = 0; i < vec.size(); i++) {
					if (size(set_pointer[i]) > 0 && size(set_pointer[i]) < size(origin_set)) {
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
