#ifndef _FILES_H_
#define _FILES_H_
#include "Files.h"
#endif

//Get file name
void Files::get_name() {
	if (file_name.length()) {
		return;
	}
	std::cout << "\nВведите имя файла: ";
	std::cin >> file_name;
}

//Add node from tree to file
void Files::add_to_file(int glob_count, int* times, int priors, std::string description, std::string place) {
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
int Files::add_to_tree(int glob_count) {
	int start = glob_count;
	get_name();
	file.open(file_name, std::ios_base::in);

	if (!file.is_open()) {
		file_name.empty();
		std::cout << "\nОшибка открытия файла";
		get_name();
	}

	while (1) {
		int priors;
		int times[5];
		std::string description;
		std::string place;

		file >> priors;
		for (int i = 0; i < 5; ++i)
			file >> times[i];
		file >> description;
		file >> place;

		if (description.length()) {
			start++;
			time_tree.addtree_container(time_tree.get_root(), start, times, priors, description, place); //Add node in time tree
			prior_tree.addtree_pr_container(prior_tree.get_pr_root(), start, times, priors); //Add node in priority tree
			//std::cout << priors<<" "+description+" "+place+"\n";
		}
		else break;
	}
	file.close();
	std::cout << "\nУспешно добавлено событий: " << start - glob_count << "\n";
	return start;
}