#include <stdio.h>
#include <stdbool.h>
#include <conio.h>

#define SCREEN_WIDTH 30
#define SCREEN_HEIGHT 20

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
}

void Update()
{

	
}

void Draw()
{
	system("cls");
	
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