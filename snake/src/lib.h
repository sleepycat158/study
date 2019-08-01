#ifndef _LIB_H_
	#define _LIB_H_ 1
	#define H 11
	#define W 11
	#define SS H*W

	static char (* initField(void))[W][3];
	static void drawField(char field[][W][3]);
	static int (* initSnake(void))[2];
	static void placeApple(const int snake[][2], char field[][W][3], int size);
	static void drawSnake(int snake[][2], char field[][W][3], int size);
	static void move(char field[][W][3], int snake[][2], int x, int y, int * size);
	static bool crush(int x, int y, int size);
	static bool eatself(int x, int y, int snake[][2], int size);
	static void gameOver(int size);
#endif