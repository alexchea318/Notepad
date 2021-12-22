#pragma once
#ifndef _NOTEBOOK_H_
#define _NOTEBOOK_H_
#include "Menu.h"
#endif

class Time {
private:
	//Time tree template
	struct tnode {
		int priors;
		int times[5];
		std::string place;            
		std::string description;               
		int number;
		struct tnode* left;
		struct tnode* right; 
	};

	//Root
	tnode* root = nullptr;

public:

	Time() { tnode* root = nullptr; };

	struct tnode* get_root() { return root; }
	void one_print(struct tnode* p);
	struct tnode* addtree(struct tnode* p, int number, int* times, int priors, std::string description, std::string  place);
	void addtree_container(struct tnode* p, int number, int* times, int priors, std::string description, std::string  place);
	struct tnode* del(struct tnode* p, int number, int* times);
	void del_container(struct tnode* p, int number, int* times) { root = del(root, number, times); };
	void treeprint(struct tnode* p);
	struct tnode* search(struct tnode* p, int* times, int number);
	void treeprint_filter(struct tnode* p, std::string filter);
	void freemem(tnode* tree);

	~Time() { freemem(root); }
};



