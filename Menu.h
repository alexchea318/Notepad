#pragma once
#include <iostream>
#include "Time.h"
#include "Prior.h"
#include "Files.h"
#include <Windows.h>

class Menu
{
private:
	int glob_count=0; //global_counter
	int is_flag = -1; //check of exist of node
	int fil_count = 0; //check of result of filter out

public:
	void menu();
	void before_delete();
	void before_out();
	void addnote();
	int get_number(std::string input, std::string error, int left, int right);
	std::string get_data(std::string input, std::string error);
	void add_fil_count() { fil_count++; };
	void set_is_flag(int k) { is_flag = k; };
};

extern class Menu Note;
extern class Prior prior_tree;
extern class Time time_tree;
extern class Files files_func;