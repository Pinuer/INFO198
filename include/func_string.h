#ifndef FUNC_STRING_H
#define FUNC_STRING_H

#include "common.h"

using namespace std;

bool check_num(string num);
string opt_menu(string user, bool admin, bool checkIndex);
bool check_empty(string s);
vector<int> split_num(string s, string separate);
vector<string> split(string s, string separate);
string text_normalization(string s);
int count_symbols(string s, string filter);
bool check_pali(string s);
void print_user_list(vector<tuple<string,string>> userVector);
string remove_character(string input, char c);
string filter_string(string input , string filter);

//char accent_upper_to_lower(char c); Dice overflow

void print_separation();


#endif