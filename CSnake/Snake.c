#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h> 


#define SCREEN_WIDTH 30
#define SCREEN_HEIGHT 25

void UserInput();
void Update();
void Draw();
void MoveSnake(int direction);
void gotoxy(int x, int y);

char userInput;
int keyCode;
bool gameRunning = true;

int borders[SCREEN_WIDTH][SCREEN_HEIGHT];
int snakePosition[SCREEN_WIDTH][SCREEN_HEIGHT];
int plumsPositions[SCREEN_WIDTH][SCREEN_HEIGHT];

enum{ KEY_ESC = 27, KEY_LEFT = 75, KEY_RIGHT = 77, KEY_UP = 72, KEY_DOWN = 80 };
enum{LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3};

void main() {

	while (gameRunning)
	{
		
		UserInput();
		Update();
		Draw();
		
	}
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
	for (size_t x = 0; x < SCREEN_HEIGHT; x++)
	{
		for (size_t y = 0; y < SCREEN_WIDTH; y++)
		{
			// set borders
			if(x == 0 || x == SCREEN_HEIGHT - 1)
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
	for (size_t x = 0; x < SCREEN_HEIGHT; x++)
	{
		for (size_t y = 0; y < SCREEN_WIDTH; y++)
		{
			// move cursor to console position
			gotoxy(y, x);

			// print borders
			if (borders[x][y] == 1)
			{
				printf("%c", '*');
			}
			
			//printf("%c", borders[x][y]);

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