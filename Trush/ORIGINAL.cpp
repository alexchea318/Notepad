#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

//Глобальные переменные
int glob_count; //счётчик
int file_out_flag = -1; //был ли создан файл
int is_flag = -1; //сущетсвует ли запись
char* out_name; //имя выходного файла
int fil_count = 0; //Был ли вывод с фильтром

//Дерево хранения по времемени
struct tnode {
	int prior;	//Важность
	int time[5]; //Время
	char* place;   //Место               
	char* description; //Описание                
	int number; //Номер
	struct tnode* left;    // левый потомок
	struct tnode* right;   // правый потомок
};

//Корень
tnode* root = NULL;

//Дерево сортировки по важности
struct prnode {
	int prior;	//Важность             
	int number; //Номер
	int time[5]; //Время
	struct prnode* left;    // левый потомок
	struct prnode* right;   // правый потомок
};

//Корень
prnode* pr_root = NULL;

// Функция добавления узла к дереву времени
struct tnode* addtree(struct tnode* p, int number, int* time, int prior, char* description, char* place) {
	int cond = 0;

	//Сравнение
	if (p != NULL) {
		for (int i = 0; i < 5; i++) {
			if (time[i] < p->time[i]) {
				cond = -1;
				break;
			}
			else if (time[i] > p->time[i]) {
				cond = 1;
				break;
			}
		}
	}

	//Добавление
	if (p == NULL) {
		p = (struct tnode*)malloc(sizeof(struct tnode));
		p->place = _strdup(place);
		p->description = _strdup(description);
		p->number = number;
		p->prior = prior;
		for (int i = 0; i < 5; i++) {
			p->time[i] = time[i];
		}
		p->left = p->right = NULL;
	}
	else if (cond < 0) {
		p->left = addtree(p->left, number, time, prior, description, place);
	}
	else {
		p->right = addtree(p->right, number, time, prior, description, place);
	}
	return p;
}

// Функция добавления узла к дереву важности
struct prnode* addtree_pr(struct prnode* pr, int number, int* time, int prior) {
	int cond = 0;

	//Сравнение
	if (pr != NULL) {
		if (prior < pr->prior) {
			cond = -1;
		}
		else {
			cond = 1;
		}
	}

	//Добавление
	if (pr == NULL) {
		pr = (struct prnode*)malloc(sizeof(struct prnode));
		pr->number = number;
		pr->prior = prior;
		for (int i = 0; i < 5; i++) {
			pr->time[i] = time[i];
		}
		pr->left = pr->right = NULL;
	}
	else if (cond < 0) {
		pr->left = addtree_pr(pr->left, number, time, prior);
	}
	else {
		pr->right = addtree_pr(pr->right, number, time, prior);
	}
	return pr;
}

//Удаление элемента из дерева времени
struct tnode* del(struct tnode* p, int number, int *time) {
	if (p == NULL)
		return p;

	//Сравнение
	int cond = 0;
	for (int i = 0; i < 5; i++) {
		if (time[i] < p->time[i]) {
			cond = -1;
			break;
		}
		else if (time[i] > p->time[i]) {
			cond = 1;
			break;
		}
	}

	//Удаление
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

		free (p);
		return tmp;
	}
	else if (cond < 0)
		p->left = del(p->left, number, time);
	else
		p->right = del(p->right, number, time);
	return p;
}

//Удаление элемента из дерева важности
struct prnode* del_pr(struct prnode* pr, int number, int prior) {
	if (pr == NULL)
		return pr;

	//Сравнение
	int cond = 0;
	if (prior < pr->prior) {
		cond = -1;
	}
	else {
		cond = 1;
	}

	//удаление
	if (cond == 0 && number==pr->number) {

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

		free( pr);
		return tmp;
	}
	else if (cond < 0)
		pr->left = del_pr(pr->left, number, prior);
	else
		pr->right = del_pr(pr->right, number, prior);
	return pr;
}

// Функция очищения памяти дерева времени
void freemem(tnode* tree) {
	if (tree != NULL) {
		freemem(tree->left);
		freemem(tree->right);
		free(tree);
	}
}

// Функция очищения памяти дерева важности
void freemem_pr(prnode* tree) {
	if (tree != NULL) {
		freemem_pr(tree->left);
		freemem_pr(tree->right);
		free(tree);
	}
}

// Функция вывода дерева времени
void treeprint(struct tnode* p) {
	if (p != NULL) {
		treeprint(p->left);
		printf("\nЗапись №%d: ", p->number);
		printf("год: %d, месяц: %d, число: %d, время: %d:%d, ", p->time[0], p->time[1], p->time[2], p->time[3], p->time[4]);
		printf("важность: %d, место: %s, описание: %s", p->prior, p->place, p->description);
		treeprint(p->right);
	}
}

// Поиск времени по приоритету в дереве времени
struct tnode* search(struct tnode* p, int* time, int number) {
	int cond = 0;

	//Сравнение
	if (p != NULL) {
		for (int i = 0; i < 5; i++) {
			if (time[i] < p->time[i]) {
				cond = -1;
				break;
			}
			else if (time[i] > p->time[i]) {
				cond = 1;
				break;
			}
		}
	}

	//Добавление
	if (p == NULL) {
		return p;
	}
	else if (cond == 0 && number==p->number) {
		printf("\nЗапись №%d: ", p->number);
		printf("год: %d, месяц: %d, число: %d, время: %d:%d, ", p->time[0], p->time[1], p->time[2], p->time[3], p->time[4]);
		printf("важность: %d, место: %s, описание: %s", p->prior, p->place, p->description);
		p->right = search(p->right, time, number);
	}
	else if (cond < 0) {
		p->left = search(p->left, time, number);
	}
	else {
		p->right = search(p->right, time, number);
	}
	return p;
}

// Функция вывода дерева важности
void treeprint_pr(struct prnode* pr) {
	if (pr != NULL) {
		treeprint_pr(pr->left);
		int time[5];
		for (int i = 0; i < 5; i++) {
			time[i] = pr->time[i];
		}
		int number = pr->number;
		search(root, time, number);
		treeprint_pr(pr->right);
	}
}

//Поиск приоритета по номеру в дереве важности
void search_pr(struct prnode* pr, int number) {
	if (pr != NULL) {
		search_pr(pr->left, number);
		if (number == pr->number) {
			is_flag = 1;
			int prior = pr->prior;
			int time[5];
			for (int i = 0; i < 5; i++) {
				time[i] = pr->time[i];
			}
			//printf("\nУ записи важность: %d, время: %d:%d", prior, time[3], time[4]);
			root = del(root, number, time); //удаление из дерева времени
			pr_root = del_pr(pr_root, number, prior); //удаление из дерева важности
			return;
		}
		search_pr(pr->right, number);
	}
}

// Функция вывода дерева c фильтром
void treeprint_filter(struct tnode* p, char* filter) {
	if (p != NULL) {
		treeprint_filter(p->left, filter);
		if (strcmp(filter, p->place) == 0) {
			printf("\nЗапись №%d: ", p->number);
			printf("год: %d, месяц: %d, число: %d, время: %d:%d, ", p->time[0], p->time[1], p->time[2], p->time[3], p->time[4]);
			printf("важность: %d, место: %s, описание: %s", p->prior, p->place, p->description);
			fil_count++;
		}
		treeprint_filter(p->right, filter);
	}
}

//Добавление записи
void addnote() {
	int prior = 0;
	char* place;
	char* description;
	int time[5];

	int type_input = 0;
	printf("\nВведите:\n1 - добавить с помощью клавиатуры\n2 - добавить из файла\nОперация: ");
	scanf("%d", &type_input);

	//Ввод с клаиватуры
	if (type_input == 1) {
		glob_count++;
		//Важность
		while (1) {
			printf("\nВведите важность события (0-10): ");
			scanf("%d", &prior);
			if (prior > 10 || prior < 0) {
				printf("\nВажность должна быть в диапазоне 1-10, повторите ввод");
			}
			else {
				break;
			}
		}

		//Время
		//Год
		while (1) {
			printf("\nВведите год события (например, 2020): ");
			scanf("%d", &time[0]);
			if (time[0] < 2020) {
				printf("\nНельзя добавить дело на прошлый год, повторите ввод");
			}
			else {
				break;
			}
		}
		//Месяц
		while (1) {
			printf("\nВведите месяц события (например, 11): ");
			scanf("%d", &time[1]);
			if (time[1] > 12 || time[1] < 1) {
				printf("\nМесяц должен быть в дипазаоне 1-12, повторите ввод");
			}
			else {
				break;
			}
		}
		//Число
		while (1) {
			printf("\nВведите число события (например, 15): ");
			scanf("%d", &time[2]);
			if (time[2] > 31 || time[2] < 1) {
				printf("\nЧисло должно быть в дипазаоне 1-31, повторите ввод");
			}
			else {
				break;
			}
		}
		//Час
		while (1) {
			printf("\nВведите час события (например, 22): ");
			scanf("%d", &time[3]);
			if (time[3] > 23 || time[3] < 0) {
				printf("\nЧас события должен быть в дипазаоне 0-23, повторите ввод");
			}
			else {
				break;
			}
		}
		//Минута
		while (1) {
			printf("\nВведите минуту события (например, 45): ");
			scanf("%d", &time[4]);
			if (time[4] > 59 || time[4] < 0) {
				printf("\nЧас события должен быть в дипазаоне 0-59, повторите ввод");
			}
			else {
				break;
			}
		}

		//Описание события
		getchar();
		while (1) {
			printf("\nВведите описание события (например, поход в музей): ");
			int i = 0;
			description = (char*)malloc(2);
			while (1) {
				//description[i] = fgetc(stdin);
				scanf("%c", &description[i]);
				i++;
				if (description[i - 1] == '\n') {
					description[i - 1] = '\0';
					break;
				}
				description = (char*)realloc(description, i + 2);
			}
			if (i < 2) {
				printf("\nНельзя создать пустое описание, повторите ввод");
				free(description);
			}
			else {
				break;
			}
		}

		//Место события
		while (1) {
			printf("\nВведите место события (например, дом): ");
			int i = 0;
			place = (char*)malloc(2);
			while (1) {
				scanf("%c", &place[i]);
				i++;
				if (place[i - 1] == '\n') {
					place[i - 1] = '\0';
					break;
				}
				place = (char*)realloc(place, i + 2);
			}
			if (i < 2) {
				printf("\nНельзя добавить пустое место, повторите ввод");
				free(place);
			}
			else {
				break;
			}
		}

		//Добавление в файл
		printf("\nВведите:\n1 - не добавлять событие в файл\n2 - добавить событие в файл\nОперация: ");
		int file;
		scanf("%d", &file);
		getchar();
		//Открытие файла
		if (file == 2) {
			FILE* out;
			int i = 0;
			if (file_out_flag == -1) {
				while (1) {
					printf("\nВведите имя файла: ");
					out_name = (char*)malloc(2);
					while (1) {
						scanf("%c", &out_name[i]);
						i++;
						if (out_name[i - 1] == '\n') {
							out_name[i - 1] = '\0';
							break;
						}
						out_name = (char*)realloc(out_name, i + 2);
					}
					if (i > 4) {
						out = fopen(out_name, "wt");
						if (out == NULL) {
							printf("\nОшибка открытия файла, повторите ввод");
							free(out_name);
						}
						else {
							file_out_flag = 1;
							break;
						}
					}
					else {
						printf("\nИмя файла слишклм короткое, повторите ввод");
						free(out_name);
					}
				}
			}
			else {
				out = fopen(out_name, "at");
			}

			//Печать в файл
			for (i = 0; i < 5; i++) {
				fprintf(out, "%d ", time[i]);
			}
			fprintf(out, "%d %s~%s\n", prior, place, description);

			fclose(out);
		}

		//Добавление в дерево
		printf("\nЗапись №%d: ", glob_count);
		for (int i = 0; i < 5; i++) {
			printf("%d ", time[i]);
		}
		printf("%d %s %s добавлена!\n", prior, place, description);

		int number = glob_count;
		root = addtree(root, number, time, prior, description, place); //Добавление в дерево времени
		pr_root = addtree_pr(pr_root, number, time, prior); //Добавление в дерево поиска по важности
		free(place);
		free(description);
	}

	//Ввод из файла
	else {
		getchar();
		char* in_name;
		FILE* in;
		while (1) {
			printf("\nВведите имя файла: ");
			int i = 0;
			in_name = (char*)malloc(2);
			while (1) {
				scanf("%c", &in_name[i]);
				i++;
				if (in_name[i - 1] == '\n') {
					in_name[i - 1] = '\0';
					break;
				}
				in_name = (char*)realloc(in_name, i + 2);
			}
			if (i < 5 || (in = fopen(in_name, "rt")) == NULL) {
				printf("\nОшибка открытия файла, повторите ввод");
				free(in_name);
			}
			else {
				break;
			}
		}

		//Сканирование

		//Цифры
		while (1) {

			fscanf(in, "%d %d %d %d %d %d", &time[0], &time[1], &time[2], &time[3], &time[4], &prior);
			fgetc(in);

			//Место
			int i = 0;
			char c;
			place = (char*)malloc(2);
			while ((c = fgetc(in)) != '~') {
				place[i] = c;
				i++;
				place = (char*)realloc(place, i + 2);
			}
			place[i] = '\0';
			//Описание
			i = 0;
			description = (char*)malloc(2);
			while ((c = fgetc(in)) != '\n') {
				description[i] = c;
				i++;
				description = (char*)realloc(description, i + 2);
			}
			description[i] = '\0';
			glob_count++;
			root = addtree(root, glob_count, time, prior, description, place); //Добавление в дерево времени
			pr_root = addtree_pr(pr_root, glob_count, time, prior); //Добавление в дерево поиска по важности
			free(place);
			free(description);
			if (fgetc(in) == EOF) {
				break;
			}
			else {
				fseek(in, -1, SEEK_CUR);
			}
		}
		//
		free(in_name);
		fclose(in);
	}

}

//Main
int main() {
	//setlocale(LC_ALL, "Russian");
	int type_operation = 0;
	system("chcp 1251");
	system("cls");
	while (1) {
		printf("Введите:\n1 - добавить событие (в т.ч. работа с файлами)\n2 - удалить событие\n3 - вывести все события\n4 - выход\nОперация: ");
		scanf("%d", &type_operation);
		if (type_operation == 1) {
			addnote(); //Добаление записи, в том числе работа с файлами
		}
		else if (type_operation == 2) {
			if (root == NULL) {
				printf("\nДерево пустое");
			}
			else {
				int number = 0;
				while (1) {
					printf("\nВведите номер записи, которую необходимо удалить (например, 2): ");
					scanf("%d", &number);
					if (number<0 || number>glob_count) {
						printf("\nЗаписи с таким номером не может существовать, повторитее ввод");
					}
					else {
						search_pr(pr_root, number); //Поиск номера приоритета по номеру
						if (is_flag == 1) {
							is_flag = -1;
							break;
						}
						else {
							printf("\nЗаписи с таким номером не сущетсвует, повторитее ввод");
						}
					}
				}
			}
			getchar();
		}
		else if (type_operation == 3) {
			if (root == NULL) {
				printf("\nДерево пустое");
			}
			else {
				int type_out = 1;
				getchar();
				printf("\nВведите:\n1 - вывести с сортировкой по дате\n2 - вывести с сортировкой по важности\n3 - вывести с фильтром по месту\nОперация: ");
				scanf("%d", &type_out);
				if (type_out == 1) {
					treeprint(root); //Вывод дерева по дате
				}
				else if (type_out == 2) {
					treeprint_pr(pr_root); //Вывод дерева по важности
				}
				else if (type_out == 3) {
					getchar();
					char* filter;
					while (1) {
						printf("\nВведите фильтр места (например, дом): ");
						int i = 0;
						filter = (char*)malloc(2);
						while (1) {
							filter[i] = getchar();
							i++;
							if (filter[i - 1] == '\n') {
								filter[i - 1] = '\0';
								break;
							}
							filter = (char*)realloc(filter, i + 2);
						}
						if (i < 2) {
							printf("\nНельзя использовать пустой фильтр, повторите ввод");
							free(filter);
						}
						else {
							break;
						}
					}
					fil_count = 0;
					treeprint_filter(root, filter); //Вывод дерева с фильтром по месту
					if (fil_count == 0) {
						printf("\nЗаписей не найдено");
					}
					free(filter);
				}
			}
		}
		else if (type_operation == 4) {
			break;
		}
		printf("\n\n");

	}
	freemem(root); //Очищаем память
	freemem_pr(pr_root);
	free(out_name);
	return 0;
}