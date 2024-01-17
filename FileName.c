#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

#define SIZE 5

struct input {
	int x;
	int y;
	char s;
	int n;
};
typedef struct input Input;

void draw(char arr[SIZE][SIZE], int arr2[SIZE][SIZE]);
Input input();
int loss(char arr[SIZE][SIZE], int arr2[SIZE][SIZE]);
int check_input(Input a);
int check_progress(Input a, char arr[SIZE][SIZE], int arr2[SIZE][SIZE]);
char cfile_input();
int ifile_input();
int play(char symb[SIZE][SIZE], int num[SIZE][SIZE]);
int output_file(char arr[SIZE][SIZE], int arr2[SIZE][SIZE]);

int main() {
	setlocale(LC_ALL, "RUS");
	int cases;
	int condition = 0;
	char symb[SIZE][SIZE] =
	{
		{' ',' ','E',' ',' '},
		{'A',' ','D',' ',' '},
		{' ','D','B',' ',' '},
		{' ',' ',' ',' ','D'},
		{' ',' ','A',' ',' '}
	};
	int num[SIZE][SIZE] =
	{
		{0,0,0,0,0},
		{0,0,3,0,4},
		{0,2,0,0,0},
		{0,0,0,0,0},
		{0,0,1,0,3}
	};
	
	int h = 5, v = 2;
	FILE* f;
	FILE* m;
	int cond;
	puts("КВАДРАТ ЭЙЛЕРА");
	puts("Выберите действие: 1 - Правила игры, 2 - Играть, 3 - Загрузить поле из нового файла\n4 - Загрузить поле из сохранённого файла 5 - Загрузить поле в файл, 6 - Выход");
	scanf("%d", &cond);
	switch (cond) {
	case 1: 
		puts("В каждой ячейке находятся одна буква и одна цифра\nВ каждой строке и каждом столбце каждая буква и каждая цифра встречаются только однажды\nКаждое сочетание буквы и цифры в головоломке встречается только один раз\n");
		break;
	case 2:
		play(symb, num);
		break;
	case 3:
		play(cfile_input, ifile_input);
		break;
		
	case 4:
		f = fopen("output.txt", "r");
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++) {
				symb[i][j] = fgets(symb, 1, f);
				fseek(f, h, SEEK_SET);
				h += 5;
			}
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++) {
				num[i][j] = fgets(num, 1, f);
				fseek(f, v, SEEK_SET);
				v += 2;
			}
		break;
	case 5:
		puts("Для сохранения поля в файл введите 0 вместо ячейки и значений");
		break;
	case 6:
		return 0;
	default: puts("Неверно выбранное действие");
	}
	draw(symb, num);
	return 1;

}

int play(char symb[SIZE][SIZE], int num[SIZE][SIZE]) {
	int condition = 0;
	while (condition != 1) {
		puts("\n");
		draw(symb, num);
		Input a = input();
		if (check_input(a) == 2) {
			puts("Игровое поле сохранено");
			output_file(symb, num);
			break;
		}
		if (check_input(a) == 1) {
			if (check_progress(a, symb, num))
			{
				if (symb[a.x - 1][a.y - 1] == 32)
					symb[a.x - 1][a.y - 1] = a.s;
				if (num[a.x - 1][a.y - 1] == 0)
					num[a.x - 1][a.y - 1] = a.n;
			}
			else {
				puts("Неверно введены данные");
				continue;
			}

		}
		else {
			puts("Неверно введены данные");
			continue;
		}
		
		if (loss(symb, num) == 0) {
			puts("Победа!");
			condition = 1;
			return 1;
		}

	}
}


void draw(char arr[SIZE][SIZE], int arr2[SIZE][SIZE]) {
	printf("    1    2    3    4    5\n");
	printf("  --------------------------\n");
	printf("1 | %c%i | %c%i | %c%i | %c%i | %c%i |\n", arr[0][0], arr2[0][0], arr[0][1], arr2[0][1], arr[0][2], arr2[0][2], arr[0][3], arr2[0][3], arr[0][4], arr2[0][4]);
	printf("  --------------------------\n");
	printf("2 | %c%i | %c%i | %c%i | %c%i | %c%i |\n", arr[1][0], arr2[1][0], arr[1][1], arr2[1][1], arr[1][2], arr2[1][2], arr[1][3], arr2[1][3], arr[1][4], arr2[1][4]);
	printf("  --------------------------\n");
	printf("3 | %c%i | %c%i | %c%i | %c%i | %c%i |\n", arr[2][0], arr2[2][0], arr[2][1], arr2[2][1], arr[2][2], arr2[2][2], arr[2][3], arr2[2][3], arr[2][4], arr2[2][4]);
	printf("  --------------------------\n");
	printf("4 | %c%i | %c%i | %c%i | %c%i | %c%i |\n", arr[3][0], arr2[3][0], arr[3][1], arr2[3][1], arr[3][2], arr2[3][2], arr[3][3], arr2[3][3], arr[3][4], arr2[3][4]);
	printf("  --------------------------\n");
	printf("5 | %c%i | %c%i | %c%i | %c%i | %c%i |\n", arr[4][0], arr2[4][0], arr[4][1], arr2[4][1], arr[4][2], arr2[4][2], arr[4][3], arr2[4][3], arr[4][4], arr2[4][4]);
	printf("  --------------------------\n");
}


Input input() {
	Input a;
	puts("Выберите ячейку для ввода значения(сначала горизонталь, потом вертикаль)");
	scanf("%d %d", &a.x, &a.y);
	puts("Введите значение ячейки(сначала буква, потом число)");
	getchar();
	scanf("%c %d", &a.s, &a.n);
	return a;
}


int check_input(Input a) {
	
	if (a.x >= 1 && a.x <= 5 && a.y >= 1 && a.y <= 5 && a.n > 0 && a.n <= 5 && a.s >= 65 && a.s <= 71)
			return 1;
	if (a.x == 0 && a.y == 0 && a.n == 0 && a.s == '0')
		return 2;
	return 0;
}


int loss(char arr[SIZE][SIZE], int arr2[SIZE][SIZE]) {
	for (int i = 0; i < 5; i++)
		for (int f = 0; f < 5; f++)
			if (arr[i][f] == 32 || arr2[i][f] == 0)
				return 1;
	return 0;
}

int check_progress(Input a, char arr[SIZE][SIZE], int arr2[SIZE][SIZE]) {
	for (int i = 0; i <= SIZE; i++) {
		if ((arr[a.x - 1][i] == a.s) || (arr2[a.x - 1][i] == a.n))
			return 0;
		if ((arr[i][a.x - 1] == a.s) || (arr2[i][a.x - 1] == a.n))
			return 0;
	}
	for (int i = 0; i <= SIZE; i++)
		for (int y = 0; y <= SIZE; y++) {
			if (arr[i][y] == a.s && arr2[i][y] == a.n)
				return 0;
		}
	return 1;
}

char cfile_input() {
	int h = 5;
	char g[SIZE][SIZE];
	FILE* f = fopen("input.txt", "r");

	if (f == NULL) {
		puts("Ошибка чтения");
		return 0;
	}

	
	
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			g[i][j] = fgets(g, 1, f);
			fseek(f, h, SEEK_SET);
			h += 5;
		}
	fclose(f);
	return g;
}

int ifile_input() {
	int j = 2;
	char g[SIZE][SIZE];
	FILE* f = fopen("input.txt", "r");

	if (f == NULL) {
		puts("Ошибка чтения");
		return 0;
	}

	

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			g[i][j] = fgets(g, 1, f);
			fseek(f, j, SEEK_SET);
			j += 2;
		}
	fclose(f);
	return g;

}



 int output_file(char arr[SIZE][SIZE], int arr2[SIZE][SIZE]) {
	FILE* m;
	m = fopen("output.txt", "w");
	if (m == NULL)
	{
		printf("Ошибка");
		return 0;
	}

	for (int i = 0; i<SIZE; i++)
		for (int g = 0; g < SIZE; g++) {
			fputs(arr[i][g],arr2[i][g], m);
		}
	fclose(m);
	return 1;
}