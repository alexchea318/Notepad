#ifndef _NOTEBOOK_H_
#define _NOTEBOOK_H_
#include "Notebook.h"
#endif

//Get file name
void Notebook::Files::get_name() {
	if (file_name.length()) {
		return;
	}
	std::cout << "\nВведите имя файла: ";
	std::cin >> file_name;
}

//Add node from tree to file
void Notebook::Files::add_to_file(int glob_count, int* times, int priors, std::string description, std::string place) {
	get_name();
	file.open(file_name, std::ios_base::app);
	if (!file.is_open()) {
		file_name.empty();
		std::cout << "\nОшибка открытия файла";
		get_name();
	}

	file << priors << "\t";
	for (int i = 0; i < 5; ++i)
		file << times[i] << "\t";
	file << description << "\t" << place << "\n";
	file.close();
}

//Add nodes from file to tree
int Notebook::add_to_tree(int glob_count) {
	int start = glob_count;
	files_func.get_name();
	files_func.file.open(files_func.file_name, std::ios_base::in);

	if (!files_func.file.is_open()) {
		files_func.file_name.empty();
		std::cout << "\nОшибка открытия файла";
		files_func.get_name();
	}

	while (1) {
		int priors;
		int times[5];
		std::string description;
		std::string place;

		files_func.file >> priors;
		for (int i = 0; i < 5; ++i)
			files_func.file >> times[i];
		files_func.file >> description;
		files_func.file >> place;

		if (description.length()) {
			start++;
			time_tree.addtree_container(time_tree.get_root(), start, times, priors, description, place); //Add node in time tree
			prior_tree.addtree_pr_container(prior_tree.get_pr_root(), start, times, priors); //Add node in priority tree
			//std::cout << priors<<" "+description+" "+place+"\n";
		}
		else break;
	}
	files_func.file.close();
	std::cout << "\nУспешно добавлено событий: " << start - glob_count << "\n";
	return start;
}