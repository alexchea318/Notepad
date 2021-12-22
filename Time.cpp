#ifndef _TIME_H_
#define _TIME_H_
#include "Time.h"
#endif

//Printing of one node
void Time::one_print(struct tnode* p) {
	std::cout << "\nЗапись № " << p->number << ": ";
	std::cout << "год: "<< p->times[0]<<", месяц: "<< p->times[1] <<", число: "<< p->times[2] <<", время: "<< p->times[3]<<":"<< p->times[4] << ", ";
	std::cout << "важность: " << p->priors << ", место: " << p->place << ", описание: " << p->description;
}

//Function-container
void Time::addtree_container(struct tnode* p, int number, int* times, int priors, std::string description, std::string  place) {
	root = addtree(root, number, times, priors, description, place);
}

//Adding node to time tree
struct Time::tnode* Time::addtree(struct tnode* p, int number, int* times, int priors, std::string description, std::string place) {
	int cond = 0;

	//Check
	if (p != NULL) {
		for (int i = 0; i < 5; i++) {
			if (times[i] < p->times[i]) {
				cond = -1;
				break;
			}
			else if (times[i] > p->times[i]) {
				cond = 1;
				break;
			}
		}
	}

	//Adding
	if (p == NULL) {
		p = new tnode;
		p->place = place;
		p->description = description;
		p->number = number;
		p->priors = priors;
		for (int i = 0; i < 5; i++) {
			p->times[i] = times[i];
		}
		p->left = p->right = NULL;
	}
	else if (cond < 0) {
		p->left = addtree(p->left, number, times, priors, description, place);
	}
	else {
		p->right = addtree(p->right, number, times, priors, description, place);
	}
	return p;
}

//Delete node from time tree
struct Time::tnode* Time::del(struct tnode* p, int number, int* times) {
	if (p == NULL)
		return p;

	//Check
	int cond = 0;
	for (int i = 0; i < 5; i++) {
		if (times[i] < p->times[i]) {
			cond = -1;
			break;
		}
		else if (times[i] > p->times[i]) {
			cond = 1;
			break;
		}
	}

	//Deleting
	if (cond == 0 && number == p->number) {

		tnode* tmp;
		if (p->right == NULL)
			tmp = p->left;
		else {

			tnode* ptr = p->right;
			if (ptr->left == NULL) {
				ptr->left = p->left;
				tmp = ptr;
			}
			else {

				tnode* pmin = ptr->left;
				while (pmin->left != NULL) {
					ptr = pmin;
					pmin = ptr->left;
				}
				ptr->left = pmin->right;
				pmin->left = p->left;
				pmin->right = p->right;
				tmp = pmin;
			}
		}

		delete p;
		return tmp;
	}
	else if (cond < 0)
		p->left = del(p->left, number, times);
	else
		p->right = del(p->right, number, times);
	return p;
}

//Delete all time tree
void Time::freemem(tnode* tree) {
	if (tree != NULL) {
		freemem(tree->left);
		freemem(tree->right);
		delete tree;
	}
}

//Print time tree
void Time::treeprint(struct tnode* p) {
	if (p != NULL) {
		treeprint(p->left);
		one_print(p);
		treeprint(p->right);
	}
}

//Search in time tree by priopity
struct Time::tnode* Time::search(struct tnode* p, int* times, int number) {
	int cond = 0;

	//Check
	if (p != NULL) {
		for (int i = 0; i < 5; i++) {
			if (times[i] < p->times[i]) {
				cond = -1;
				break;
			}
			else if (times[i] > p->times[i]) {
				cond = 1;
				break;
			}
		}
	}

	//Adding
	if (p == NULL) {
		return p;
	}
	else if (cond == 0 && number == p->number) {
		one_print(p);
		p->right = search(p->right, times, number);
	}
	else if (cond < 0) {
		p->left = search(p->left, times, number);
	}
	else {
		p->right = search(p->right, times, number);
	}
	return p;
}

// Print time tree with filter
void Time::treeprint_filter(struct tnode* p, std::string filter) {
	if (p != NULL) {
		treeprint_filter(p->left, filter);
		if (strcmp(filter.c_str(), (p->place).c_str()) == 0) {
			one_print(p);
			Note.add_fil_count();
		}
		treeprint_filter(p->right, filter);
	}
}
