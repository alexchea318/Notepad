#pragma once
#ifndef _NOTEBOOK_H_
#define _NOTEBOOK_H_
#include "Menu.h"
#endif
#include <iostream>
#include <fstream>

class Files 
{
private:
	std::string file_name;
	std::fstream file;

public:
	void add_to_file(int glob_count, int* times, int priors, std::string description, std::string place);
	int add_to_tree(int glob_count);
	void get_name();
};
