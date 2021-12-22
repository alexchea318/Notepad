#pragma once
#ifndef _NOTEBOOK_H_
#define _NOTEBOOK_H_
#include "Menu.h"
#endif

class Prior {
private:
	//Priority tree
	struct prnode {
		int priors;	           
		int number; 
		int times[5]; 
		struct prnode* left;   
		struct prnode* right;  
	};

	//Root
	prnode* pr_root = nullptr;

public:
	Prior() { prnode* root = nullptr; };

	struct prnode* get_pr_root() { return pr_root; }
	struct prnode* addtree_pr(struct prnode* pr, int number, int* times, int priors);
	void addtree_pr_container(struct prnode* pr, int number, int* times, int priors);
	struct prnode* del_pr(struct prnode* pr, int number, int priors);
	void treeprint_pr(struct prnode* pr);
	void search_pr(struct prnode* pr, int number);
	void freemem_pr(prnode* tree);

	~Prior() { freemem_pr(pr_root); }
};

