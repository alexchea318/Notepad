#pragma once
#include <iostream>
#include <fstream>

class Notebook
{
public:
	class Prior {
	public:
		//Priority tree
		struct prnode {
			int priors;
			int number;
			int times[5];
			struct prnode* left;
			struct prnode* right;
		};
	private:
		//Root
		prnode* pr_root = nullptr;
	public:
		Prior() { prnode* root = nullptr; };

		struct prnode* get_pr_root() { return pr_root; }
		struct prnode* addtree_pr(struct prnode* pr, int number, int* times, int priors);
		void addtree_pr_container(struct prnode* pr, int number, int* times, int priors);
		struct prnode* del_pr(struct prnode* pr, int number, int priors);
		void del_pr_container(struct prnode* pr, int number, int priors) { pr_root = del_pr(pr_root, number, priors); };
		void freemem_pr(prnode* tree);

		~Prior() { freemem_pr(pr_root); }
	};

	class Time {
	public:
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
	private:
		//Root
		tnode* root = nullptr;
	public:

		int fil_count = 0; //check of result of filter out

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

	class Files
	{
	public:
		std::string file_name;
		std::fstream file;
		void add_to_file(int glob_count, int* times, int priors, std::string description, std::string place);
		void get_name();
	};

	//Interfaces functions
	int add_to_tree(int glob_count);
	void treeprint_pr(struct Prior::prnode* pr);
	void search_pr(struct Prior::prnode* pr, int number);

	//Exemplares
	int is_flag = -1; //check of exist of node

	Time time_tree;
	Prior prior_tree;
	Files files_func;
};
