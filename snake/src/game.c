#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "lib.h"

int main(void) {
	char (* field)[W][3];
	int (* snake)[2];
	int size = 0;
	int x = W/2;
	int y = H/2;
	char dir;

	field = initField();
	snake = initSnake();
	placeApple(snake, field, size);
	while (true) {
		drawSnake(snake, field, size);
		drawField(field);
		
		dir = getch();

		if (dir == 'a')
			--x;
		else if (dir == 'd')
			++x;
		else if (dir == 'w')
			--y;
		else if (dir == 's')
			++y;
		else if (dir == '0')
			break;
		else {
			system("cls");
			continue;
		}

		if (crush(x, y, size) || eatself(x, y, snake, size))
			break;

		move(field, snake, x, y, &size);
		system("cls");
	}
	
	getch();
	getch();

	return 0;
}

static char (* initField(void))[W][3] {
	static char field[H][W][3];

	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			field[i][j][0] = '[';
			field[i][j][1] = ' ';
			field[i][j][2] = ']';
		}
	}

	return field;
}

static void drawField(char field[][W][3]) {
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			for (int k = 0; k < 3; ++k) {
				printf("%c", field[i][j][k]);
			}
		}
		printf("\n");
	}
}

static int (* initSnake(void))[2] {
	static int snake[SS][2];
	
	// head
	snake[0][0] = W/2;
	snake[0][1] = H/2;

	return snake;
}

static void placeApple(const int snake[][2], char field[][W][3], int size) {
	// changing seed for rand()
	srand(time(NULL)); 

	int rx, ry;
	bool done = false;

	// randoming X and Y for apple
	while (!done) {
		rx = rand() % (W - 1);
		ry = rand() % (H - 1);
		done = true;
		
		for (int i = 0; i <= size; ++i) {
			if (snake[i][0] == rx && snake[i][1] == ry) {
				done = false;
				break;
			}
		}
	}

	field[ry][rx][1] = '@';
}

static void drawSnake(int snake[][2], char field[][W][3], int size) {
	field[snake[0][1]][snake[0][0]][1] = 'O';

	for (int i = 1; i <= size; ++i)
		field[snake[i][1]][snake[i][0]][1] = '#';
}

static void move(char field[][W][3], int snake[][2], int x, int y, int * size) {
	bool grew = false;
	int lastx = snake[*size][0];
	int lasty = snake[*size][1];

	if (field[y][x][1] == '@') {
		++(*size);
		grew = true;
	}

	for (int i = *(size); i > 0; --i) {
		snake[i][0] = snake[i - 1][0];
		snake[i][1] = snake[i - 1][1];
	}

	snake[0][0] = x;
	snake[0][1] = y;

	if (grew)
		placeApple(snake, field, *size);
	else 
		field[lasty][lastx][1] = ' ';
}

static bool crush(int x, int y, int size) {
	if (x >= W || y >= H || x < 0 || y < 0 ) {
		gameOver(size);
		return true;
	}

	return false;
}

static bool eatself(int x, int y, int snake[][2], int size) {
	for (int i = 0; i <= size; ++i)
		if (snake[i][0] == x && snake[i][1] == y) {
			gameOver(size);
			return true;
		}

	return false;
}

static void gameOver(int size) {
	system("cls");
	printf("GAME OVER!\n\n");
	printf("Score: %d\n", size);
}