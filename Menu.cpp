#ifndef _NOTEBOOK_H_
#define _NOTEBOOK_H_
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
	std::cout << "�������:\n1 - �������� � ������� ����������\n2 - �������� �� �����\n��������: ";
	std::cin >> type_input;

	if (type_input == 1)
	{
		glob_count++;

		//Node details
		int priors = get_number("\n������� �������� ������� (1-10, 1 - ����������)", "�������� ������ ���� � ��������� 1-10, ��������� ����", 1, 10);
		times[0] = get_number("������� ��� ������� (��������, 2021)", "������ �������� ���� �� ������� ���, ��������� ����", 2021, 2099);
		times[1] = get_number("������� ����� ������� (��������, 11)", "����� ������ ���� � ��������� 1-12, ��������� ����", 1, 12);
		times[2] = get_number("������� ����� ������� (��������, 15)", "����� ������ ���� � ��������� 1-31, ��������� ����", 1, 31);
		times[3] = get_number("������� ��� ������� (��������, 22)", "��� ������� ������ ���� � ��������� 0-23, ��������� ����", 0, 23);
		times[4] = get_number("������� ������ ������� (��������, 45)", "������ ������� ������ ���� � ��������� 0-59, ��������� ����", 0, 59);
		std::string description = get_data("������� �������� ������� (��������, ����� � �����)", "������ ������� ������ ��������, ��������� ����");
		std::string place = get_data("������� ����� ������� (��������, ���)", "������ �������� ������ �����, ��������� ����");

		//Adding
		std::cout << "\n�������:\n1 - �� ��������� ������� � ����\n2 - �������� ������� � ����\n��������: ";
		int add_node_to_file;
		std::cin >> add_node_to_file;
		if (add_node_to_file == 2) {
			files_func.add_to_file(glob_count, times, priors, description, place);
		}

		std::cout << "\n������ �" << glob_count;
		std::cout << " \"" << description << "\" ���������!\n";

		time_tree.addtree_container(time_tree.get_root(), glob_count, times, priors, description, place); //Add node in time tree
		prior_tree.addtree_pr_container(prior_tree.get_pr_root(), glob_count, times, priors); //Add node in priority tree
	}
	else {
		glob_count=files_func.add_to_tree(glob_count);
	}
}

//Prepares before delete
void Menu::before_delete() {
	if (time_tree.get_root() == NULL) {
		std::cout << "\n������ ������";
	}
	else {
		int number = 0;
		while (1) {
			std::cout << "������� ����� ������, ������� ���������� ������� (��������, 2): ";
			std::cin >> number;
			if (number<0 || number>glob_count) {
				std::cout << "\n������ � ����� ������� �� ����� ������������, ���������� ����";
			}
			else {
				prior_tree.search_pr(prior_tree.get_pr_root(), number); //Search note with number in priority tree
				if (is_flag == 1) {
					is_flag = -1;
					break;
				}
				else {
					std::cout << "\n������ � ����� ������� �� ����������, ���������� ����";
				}
			}
		}
	}
}

//Prepares before out
void Menu::before_out() {
	int type_out = 1;
	std::cout << "�������:\n1 - ������� � ����������� �� ����\n2 - ������� � ����������� �� ��������\n3 - ������� � �������� �� �����\n��������: ";
	std::cin >> type_out;
	if (type_out == 1) {
		time_tree.treeprint(time_tree.get_root()); //Print time tree with date sort
	}
	else if (type_out == 2) {
		prior_tree.treeprint_pr(prior_tree.get_pr_root()); //Print priority tree with prior sort
	}
	else if (type_out == 3) {
		std::string filter = get_data("������� ������ ����� (��������, ���)", "������ ������������ ������ ������, ��������� ����");
		fil_count = 0;
		time_tree.treeprint_filter(time_tree.get_root(), filter); //Print time tree with place filter
		if (fil_count == 0) {
			std::cout << "\n������� �� �������";
		}
	}
	std::cout << std::endl;
}

//Main menu
void Menu::menu() {
	while (1) {
		int type_operation = 0;
		std::cout << "�������:\n1 - �������� ������� (� �.�. ������ � �������)\n2 - ������� �������\n3 - ������� ��� �������\n4 - �����\n��������: ";
		std::cin >> type_operation;
		std::cout << std::endl;
		if (type_operation == 1) {
			addnote(); //Prepares before add in tree
		}
		else if (type_operation == 2) {
			before_delete();
		}
		else if (type_operation == 3) {
			if (time_tree.get_root() == NULL) {
				std::cout << "\n������ ������" ;
			}
			else {
				before_out();
			}
		}

		else break;
		std::cout << std::endl;
	}
}