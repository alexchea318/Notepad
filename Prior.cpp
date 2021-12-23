#ifndef _NOTEBOOK_H_
#define _NOTEBOOK_H_
#include "Notebook.h"
#endif

//Container-function
void Notebook::Prior::addtree_pr_container(struct prnode* pr, int number, int* times, int priors) {
	pr_root = addtree_pr(pr_root, number, times, priors);
}

//Add note to priority tree
struct Notebook::Prior::prnode* Notebook::Prior::addtree_pr(struct prnode* pr, int number, int* times, int priors) {
	int cond = 0;

	//Check
	if (pr != NULL) {
		if (priors < pr->priors) {
			cond = -1;
		}
		else {
			cond = 1;
		}
	}

	//Adding
	if (pr == NULL) {
		pr = new prnode;
		pr->number = number;
		pr->priors = priors;
		for (int i = 0; i < 5; i++) {
			pr->times[i] = times[i];
		}
		pr->left = pr->right = NULL;
	}
	else if (cond < 0) {
		pr->left = addtree_pr(pr->left, number, times, priors);
	}
	else {
		pr->right = addtree_pr(pr->right, number, times, priors);
	}
	return pr;
}


//Delete node from priority tree
struct Notebook::Prior::prnode* Notebook::Prior::del_pr(struct prnode* pr, int number, int priors) {
	if (pr == NULL)
		return pr;

	//Check
	int cond = 0;
	if (priors < pr->priors) {
		cond = -1;
	}
	else {
		cond = 1;
	}

	//Deleting
	if (cond == 0 && number == pr->number) {

		prnode* tmp;
		if (pr->right == NULL)
			tmp = pr->left;
		else {

			prnode* ptr = pr->right;
			if (ptr->left == NULL) {
				ptr->left = pr->left;
				tmp = ptr;
			}
			else {

				prnode* pmin = ptr->left;
				while (pmin->left != NULL) {
					ptr = pmin;
					pmin = ptr->left;
				}
				ptr->left = pmin->right;
				pmin->left = pr->left;
				pmin->right = pr->right;
				tmp = pmin;
			}
		}

		delete pr;
		return tmp;
	}
	else if (cond < 0)
		pr->left = del_pr(pr->left, number, priors);
	else
		pr->right = del_pr(pr->right, number, priors);
	return pr;
}

//Free of priority tree
void  Notebook::Prior::freemem_pr(prnode* tree) {
	if (tree != NULL) {
		freemem_pr(tree->left);
		freemem_pr(tree->right);
		delete tree;
	}
}

//Print priority tree
void  Notebook::treeprint_pr(struct Prior::prnode* pr) {
	if (pr != NULL) {
		treeprint_pr(pr->left);
		int times[5];
		for (int i = 0; i < 5; i++) {
			times[i] = pr->times[i];
		}
		int number = pr->number;
		time_tree.search(time_tree.get_root(), times, number);
		treeprint_pr(pr->right);
	}
}

//Search in priority tree by number
void Notebook::search_pr(struct Prior::prnode* pr, int number) {
	if (pr != NULL) {
		search_pr(pr->left, number);
		if (number == pr->number) {
			is_flag=1;
			int priors = pr->priors;
			int times[5];
			for (int i = 0; i < 5; i++) {
				times[i] = pr->times[i];
			}
			//printf("\n” записи важность: %d, врем€: %d:%d", prior_tree, time_tree[3], time_tree[4]);
			time_tree.del_container(time_tree.get_root(), number, times); //удаление из дерева времени 
			prior_tree.del_pr_container(prior_tree.get_pr_root(), number, priors); //удаление из дерева важности
			return;
		}
		search_pr(pr->right, number);
	}
}