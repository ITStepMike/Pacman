#include "pch.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <dos.h>
#include <iomanip>

using namespace std;

const int H = 50, W = 100;
bool map[H][W];

void setXY(short x, short y)
{
	COORD coord = { y, x };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void showXY(short x, short y)
{
	setXY(H+2, W+2);
	cout << "X:" << setw(3) << x << " Y:" << setw(3) << y;
	setXY(x, y);
}

//checking place for setting vertical body
bool checkVerticalWall(short x, short y) {
	
	for (int i = x - 2; i <= x + 2; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (map[i][j] == 1) {
				return 0;
			}
		}
	}

	return 1;
}

bool checkCastle(short x, short y) {
	for (int i = x - 6; i <= x + 7; i++) {
		for (int j = y - 6; j <= y + 7; j++) {
			if (map[i][j] == 1) {
				return 0;
			}
		}
	}

	return 1;
}

bool checkHorizontalWall(short x, short y) {

	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 2; j <= y + 2; j++) {
			if (map[i][j] == 1) {
				return 0;
			}
		}
	}

	return 1;
}

//Build walls (0 - vertical, 1 - horizontal)
void buildWalls(int count) {
	int chose, x, y, i;
	i = 0;
	for (;i < count;) {
		chose = rand() % 3;
		switch (chose) {
		case 24:
			x = 3 + rand() % H-4;
			y = 3 + rand() % W-4;
			if (checkVerticalWall(x, y)) {
				for (int j = x - 1; j <= x + 1; j++) {
					map[j][y] = 1;
				}
				i++;
			}
			break;
		case 25:
			x = 3 + rand() % H - 4;
			y = 3 + rand() % W - 4;
			if (checkHorizontalWall(x, y)) {
				for (int j = y - 1; j <= y + 1; j++) {
					map[x][j] = 1;
				}
				i++;
			}
			break;
		case 2:
			x = 6 + rand() % H - 8;
			y = 6 + rand() % W - 8;
			if (checkCastle(x, y)) {
				for (int l = x - 5; l <= x + 6; l++) {
					for (int j = y - 5; j <= y + 6; j++) {
						if (l == x - 5 || j == y - 5 || l == x + 6 || j == y + 6) {
							map[l][j] = 1;
						}
					}
				}

				for (int l = x - 3; l <= x + 4; l++) {
					for (int j = y - 3; j <= y + 4; j++) {
						if (l == x - 3 || j == y - 3 || l == x + 4 || j == y + 4) {
							map[l][j] = 1;
						}
					}
				}

				map[x + 4][y] = 0;
				map[x - 5][y] = 0;


				i++;
			}
			break;
		}
		setXY(H + 5, W + 5);
		cout << "wallsCount:" << setw(3) << i;
	}
}

bool check(int x, int y)
{
	return !(map[x][y]);
}

int main()
{
	srand(time(NULL));

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (i == 0 || j == 0 || i == H - 1 || j == W - 1) {
				map[i][j] = 1;
			}
			else {
				map[i][j] = 0;
			}
		}
	}

	buildWalls(50);

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			setXY(i, j);
			if (map[i][j] == 1) {
				cout << "#";
			}
		}
	}

	//Set start x, y
	int x, y;
	for (;;) {
		x = 2 + rand() % H-2;
		y = 2 + rand() % W-2;
		if (map[x][y] == 0) {
			break;
		}
	}

	bool flag = true;
	int t = 100;
	enum Moves { UP = 72, RIGHT = 77, DOWN = 80, LEFT = 75, Enter = 13 };
	while(flag) {
		switch (_getch()) {
		case RIGHT:
			if (check(x, y + 1)) {
				setXY(x, y);
				cout << " ";
				++y;
				setXY(x, y);
				cout << "O";
				showXY(x, y);
			}
			break;
		case LEFT:
			if (check(x, y - 1)) {
				setXY(x, y);
				cout << " ";
				--y;
				setXY(x, y);
				cout << "O";
				showXY(x, y);
			}
			break;
		case UP:
			if (check(x - 1, y)) {
				setXY(x, y);
				cout << " ";
				--x;
				setXY(x, y);
				cout << "O";
				showXY(x, y);
			}
			break;
		case DOWN:
			if (check(x + 1, y)) {
				setXY(x, y);
				cout << " ";
				++x;
				setXY(x, y);
				cout << "O";
				showXY(x, y);
			}
			break;
		case Enter:
			flag = false;
			break;
		}
	}
}

