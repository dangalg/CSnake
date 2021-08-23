#include <stdio.h>
#include <stdbool.h>
#include <conio.h>

#define SCREEN_WIDTH 60
#define SCREEN_HEIGHT 25

void UserInput();
void Update();
void Draw();
void MoveSnake(int direction);

char userInput;
char screen[SCREEN_WIDTH][SCREEN_HEIGHT];
int keyCode;
bool gameRunning = true;


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
			// convert index to char
			itoa(y, index, 10);

			// print index
			printf("%s", index);

		}
		printf("\n");
	}
	
}

void Draw()
{
	system("cls");

	char index[3] = { "0" };

	// print screen matrix
	for (size_t x = 0; x < SCREEN_HEIGHT; x++)
	{
		for (size_t y = 0; y < SCREEN_WIDTH; y++)
		{
			// convert index to char
			itoa(y, index, 10);

			// print index
			printf("%s", index);
			printf("%s", screen[x][y]);

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