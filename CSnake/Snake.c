#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h> 
#include <time.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define MS_PER_UPDATE 200

void UserInput();
void Update();
void Draw();
void MoveSnake(int direction);
void gotoxy(int x, int y);
long getCurrentTime();

int snakeHeadX = 0;
int snakeHeadY = 0;
int snakeTailX = 0;
int snakeTailY = 0;
int snakeTailBeforeX = 0;
int snakeTailBeforeY = 0;

char userInput;
int keyCode;
bool gameRunning = true;
long lastTime = 0;
long currentTime = 0;

int borders[SCREEN_WIDTH][SCREEN_HEIGHT];
int snakePosition[SCREEN_WIDTH][SCREEN_HEIGHT];
int plumsPositions[SCREEN_WIDTH][SCREEN_HEIGHT];

enum{ KEY_ESC = 27, KEY_LEFT = 75, KEY_RIGHT = 77, KEY_UP = 72, KEY_DOWN = 80 };
enum{LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3};

void main() {

	lastTime = getCurrentTime();

	while (true)
	{
		UserInput();
		Update();
		Draw();
	}

	// removes inside coding when you stop the game
	system("pause>0");
}

long getCurrentTime()
{
	long  currentTime = time(0);
	return currentTime;
}

void UserInput()
{
	if (_kbhit()) {
		keyCode = _getch();
	}

	// decide what to do based on keycode
	switch (keyCode)
	{
	case KEY_ESC:
		gameRunning = false;
		break;
	case KEY_LEFT:
		MoveSnake(LEFT);
		break;
	case KEY_RIGHT:
		MoveSnake(RIGHT);
		break;
	case KEY_UP:
		MoveSnake(UP);
		break;
	case KEY_DOWN:
		MoveSnake(DOWN);
		break;
	}

	// reset keycode
	keyCode = 0;
}

void Update()
{
	// fill screen matrix
	for (size_t y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (size_t x = 0; x < SCREEN_WIDTH; x++)
		{
			// set borders
			if(y == 0 || y == SCREEN_HEIGHT - 1 || x == 0 || x == SCREEN_WIDTH - 1)
			{
				borders[x][y] = 1;
			}


		}
	}
}

void Draw()
{
	//system("cls");

	// print screen matrix
	for (size_t y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (size_t x = 0; x < SCREEN_WIDTH; x++)
		{
			// move cursor to console position
			gotoxy(x, y);

			// print borders
			if (borders[x][y] == 1)
			{
				printf("%c", '*');
			}
			
			// print snake
			if (snakePosition[x][y] == 1) 
			{
				printf("%c", 'X');
			}

			// print plums
			if (plumsPositions[x][y] == 1)
			{
				printf("%c", 'O');
			}

		}
		printf("\n");
	}
}

void MoveSnake(int direction) 
{

	switch (direction)
	{
		case LEFT:
			puts("LEFT");
			break;
		case RIGHT:
			puts("RIGHT");
			break;
		case UP:
			puts("UP");
			break;
		case DOWN:
			puts("DOWN");
			break;
	}

}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

