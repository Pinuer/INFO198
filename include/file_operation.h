#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

#include <filesystem>

#include "common.h"

namespace fs = std::filesystem;


vector<string> get_files(string folderPath);
vector<string> read_file(string fileName);
vector<string> read_file_up_to(string fileName, int numLines);
int check_number_of_lines(string fileName);
void cut_lines_up_to(string fileName, int numLines);
void add_line_to_file(string fileName, string line);
void add_user_to_file(string fileName, string line);
void erase_lines(string fileName, vector<string> newLines);
void erase_file_contents(string fileName);
bool input_output_file_check(string input, string output);

#endif