#ifndef ENV_SETTER_H
#define ENV_SETTER_H


#include "common.h"
#include "file_operation.h"
#include "func_string.h"

#include <algorithm>

void set_env_from_file();
string get_enviroment_variable(const char* var);

using namespace std;



#endif