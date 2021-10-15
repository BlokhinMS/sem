#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>

int main(void) {
	system("chcp 1251");

	char c;													//переменная для заполнение массива
	int str = 1, col = 0;									//для посчёта столбцов и строк
	int between;											//для записывание количества столбоц в цикле подсчёта
	int** arr;												//двухмерный массив
	int rows = 0, colum = 0;								//столбцы и строки для запонения двухмерного массива без пробелов
	int chack = 0;											//переменная для доп проверки при заполнении файла .gv
	int mult;												//промежуточная переменная для случая если ребро является петлёй
	int* con;												//массив для проверки на связанность графа
	int com = 0;											//переменная для проверки связанных вершин

	FILE* fin = NULL;

	fin = fopen("2dz.txt", "r");							//открывание файла в режиме ride
	if (!fin) {												//проверка: открыляс ли файл
		printf("Error!\n");
		return 0;
	}
	else {
		while ((c = fgetc(fin)) != EOF) {					//подсчёт строк и столбцов
			if (c != ' ' && c != '\n') {
				col++;
			}
			if (c == '\n') {
				str++;
				between = col - 1;
				col = 0;
			}
		}

		rewind(fin);										//чтения файла сначала

		arr = (int**)calloc(str, sizeof(int*));				//выделение динамической памяти с иницилизацией массива

		if (arr == NULL) {									//проверка: выделилось достаточно памяти
			exit(1);
		}

		for (int i = 0; i < str; i++) {
			arr[i] = (int*)calloc(between, sizeof(int));	//выделение динамической памяти с иницилизацией массива
			if (arr[i] == NULL) {
				exit(1);
			}
		}

		while ((c = fgetc(fin)) != EOF) {					//заполнение двухмерного массива исключая пробелы
			if (!isspace(c)) {
				arr[rows][colum] = c - '0';
				colum++;
			}
			if (c == '\n') {
				rows++;
				colum = 0;
			}
		}

		for (int i = 0; i < str; i++) {						//выведение двухмерного массива для пользователя
			for (int j = 0; j < between; j++) {
				printf("%d\t", arr[i][j]);
			}
			printf("\n");
		}
	}

	fclose(fin);											//закрывание файла

	fin = fopen("2dz_answer.gv", "w");						//открывание файла в режиме write

	if (!fin) {
		printf("Error!\n");
		return 0;
	}

	fprintf(fin, "%s", "graph gr {\n");						//заполнение файла

	for (int j = 0; j < between; j++) {
		for (int i = 0; i < str; i++) {
			if (i == 0) {
				chack = 0;
			}
			if (arr[i][j] == 1 && chack == 1) {
				fprintf(fin, "%d\n", i + 1);
				chack = 2;
				printf("pin 1 & %d\n", i + 1);
			}
			if (arr[i][j] == 1 && chack == 0) {
				fprintf(fin, "%d--", i + 1);
				mult = i + 1;
				chack = 1;
				printf("pin 0 & %d\n", i + 1);
			}
			if (i == (str - 1) && chack == 1) {
				fprintf(fin, "%d\n", mult);
			}
		}
	}

	fprintf(fin, "%s", "}");

	fclose(fin);

	fin = fopen("2dz_answer.gv", "r");						//открывание файла в режиме ride

	if (!fin) {
		printf("Error!\n");
		return 0;
	}

	con = (int*)calloc(str, sizeof(int));					//выделение динамической памяти с инициализацией массива
	if (con == NULL) {
		exit(1);
	}

	con[0] = 1;												//проверка графа на связанность

	for (int i = 0; i < str; i++) {
		if (con[i] == 1) {
			for (int j = 0; j < str; j++) {
				if (con[j] != 1) {
					for (int m = 0; m < between; m++) {
						if ((arr[i][m] == 1) && (arr[j][m] == 1)) {
							con[j] = 1;
							com++;
							break;
						}
					}
				}
			}
		}
	}
	if ((com + 1) == str) {
		printf("\ngraph converges!\n");
	}
	else {
		printf("\ngraph not converges!\n");
	}

	fclose(fin);

	system("dot -Tpng 2dz_answer.gv -o 'answer.png'");		//передача команды командной строке для визуализации графа в среде grathviz
	system("wslview answer.png");

	for (int i = 0; i < str; i++) {							//освобожнение ранее выделенной памяти
		free(arr[i]);
	}
	free(arr);
	free(con);

	return 0;
}
