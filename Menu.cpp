#ifndef _MENU_H_
#define _MENU_H_
#include "Menu.h"
#endif

//Add numbers with checks
int Menu::get_number(std::string input, std::string error, int left, int right) {
	while (1) {
		int temp;
		std::cout << input << ": ";
		std::cin >> temp;
		if (temp > right || temp < left) {
			std::cout << error;
		}
		else return temp;
	}
}

//Add texts with checks
std::string Menu::get_data(std::string input, std::string error) {
	while (1) {
		std::string temp;
		std::cout << input << ": ";
		std::cin >> temp;

		if (temp.length() < 2) {
			std::cout << error;
		}
		else return temp;
	}
}

//Adding node prepares
void Menu::addnote() {
	int times[5];
	int type_input = 0;
	std::cout << "Введите:\n1 - добавить с помощью клавиатуры\n2 - добавить из файла\nОперация: ";
	std::cin >> type_input;

	if (type_input == 1)
	{
		glob_count++;

		//Node details
		int priors = get_number("\nВведите важность события (1-10, 1 - наибольшая)", "Важность должна быть в диапазоне 1-10, повторите ввод", 1, 10);
		times[0] = get_number("Введите год события (например, 2021)", "Нельзя добавить дело на прошлый год, повторите ввод", 2021, 2099);
		times[1] = get_number("Введите месяц события (например, 11)", "Месяц должен быть в дипазаоне 1-12, повторите ввод", 1, 12);
		times[2] = get_number("Введите число события (например, 15)", "Число должно быть в дипазаоне 1-31, повторите ввод", 1, 31);
		times[3] = get_number("Введите час события (например, 22)", "Час события должен быть в дипазаоне 0-23, повторите ввод", 0, 23);
		times[4] = get_number("Введите минуту события (например, 45)", "Минута события должна быть в дипазаоне 0-59, повторите ввод", 0, 59);
		std::string description = get_data("Введите описание события (например, поход в музей)", "Нельзя создать пустое описание, повторите ввод");
		std::string place = get_data("Введите место события (например, дом)", "Нельзя добавить пустое место, повторите ввод");

		//Adding
		std::cout << "\nВведите:\n1 - не добавлять событие в файл\n2 - добавить событие в файл\nОперация: ";
		int add_node_to_file;
		std::cin >> add_node_to_file;
		if (add_node_to_file == 2) {
			note.files_func.add_to_file(glob_count, times, priors, description, place);
		}

		std::cout << "\nЗапись №" << glob_count;
		std::cout << " \"" << description << "\" добавлена!\n";

		note.time_tree.addtree_container(note.time_tree.get_root(), glob_count, times, priors, description, place); //Add node in time tree
		note.prior_tree.addtree_pr_container(note.prior_tree.get_pr_root(), glob_count, times, priors); //Add node in priority tree
	}
	else {
		glob_count= note.add_to_tree(glob_count);
	}
}

//Prepares before delete
void Menu::before_delete() {
	if (note.time_tree.get_root() == NULL) {
		std::cout << "\nДерево пустое";
	}
	else {
		int number = 0;
		while (1) {
			std::cout << "Введите номер записи, которую необходимо удалить (например, 2): ";
			std::cin >> number;
			if (number<0 || number>glob_count) {
				std::cout << "\nЗаписи с таким номером не может существовать, повторитее ввод";
			}
			else {
				note.search_pr(note.prior_tree.get_pr_root(), number); //Search note with number in priority tree
				if (note.is_flag == 1) {
					note.is_flag = -1;
					break;
				}
				else {
					std::cout << "\nЗаписи с таким номером не сущетсвует, повторитее ввод";
				}
			}
		}
	}
}

//Prepares before out
void Menu::before_out() {
	int type_out = 1;
	std::cout << "Введите:\n1 - вывести с сортировкой по дате\n2 - вывести с сортировкой по важности\n3 - вывести с фильтром по месту\nОперация: ";
	std::cin >> type_out;
	if (type_out == 1) {
		note.time_tree.treeprint(note.time_tree.get_root()); //Print time tree with date sort
	}
	else if (type_out == 2) {
		note.treeprint_pr(note.prior_tree.get_pr_root()); //Print priority tree with prior sort
	}
	else if (type_out == 3) {
		std::string filter = get_data("Введите фильтр места (например, дом)", "Нельзя использовать пустой фильтр, повторите ввод");
		note.time_tree.fil_count = 0;
		note.time_tree.treeprint_filter(note.time_tree.get_root(), filter); //Print time tree with place filter
		if (note.time_tree.fil_count == 0) {
			std::cout << "\nЗаписей не найдено";
		}
	}
	std::cout << std::endl;
}

//Main menu
void Menu::menu() {
	while (1) {
		int type_operation = 0;
		std::cout << "Введите:\n1 - добавить событие (в т.ч. работа с файлами)\n2 - удалить событие\n3 - вывести все события\n4 - выход\nОперация: ";
		std::cin >> type_operation;
		std::cout << std::endl;
		if (type_operation == 1) {
			addnote(); //Prepares before add in tree
		}
		else if (type_operation == 2) {
			before_delete();
		}
		else if (type_operation == 3) {
			if (note.time_tree.get_root() == NULL) {
				std::cout << "\nДерево пустое" ;
			}
			else {
				before_out();
			}
		}

		else break;
		std::cout << std::endl;
	}
}