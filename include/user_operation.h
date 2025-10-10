#ifndef USER_OPERATION_H
#define USER_OPERATION_H

#include "common.h"
#include "func_string.h"
#include "file_operation.h"

bool check_login(string user, string password, bool* admin, string userFilePath);
vector<tuple<string,string,string>> get_user_login(string fileName);
vector<tuple<string,string>> get_user_list(string fileName);
void add_user(string userFilePath);
void erase_user(string userFilePath);

#endif