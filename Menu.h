#pragma once
#include <iostream>
#include "Notebook.h"

class Menu
{
private:
	int glob_count=0; //global_counter

public:
	void menu();
	void before_delete();
	void before_out();
	void addnote();
	int get_number(std::string input, std::string error, int left, int right);
	std::string get_data(std::string input, std::string error);

	Notebook note;
};
