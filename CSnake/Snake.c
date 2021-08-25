#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h> 
#include <time.h>
#include <stdlib.h>

// constants
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define MS_PER_UPDATE 100
#define FRUIT_AMOUNT 10

// structs
struct Positions;
struct Positions
{
	int x;
	int y;
}position;

// functions
void UserInput();
void Update();
void Draw();
void MoveSnake();
bool CheckWallCollision();
bool CheckSelfCollision();
bool CheckFruitCollision();
void CreateFruit();
void gotoxy(int x, int y);
void PrintSnake();
void PrintFruit();
void CreateBorders();
void PrintBorders();
void GrowSnake();
int random_number(int min_num, int max_num);
int getCurrentTimeInMillis();

// snake parameters
int snakeLength = 1;
bool snakeShouldGrow = false;
int lastSnakeXToRemove = 0;
int lastSnakeYToRemove = 0;
bool removeLastSnakeLink = false;

// fruit parameters
int numberOfFruit = 0;

// user parameters
char userInput;
int keyCode;
int lastDirection = 0;

// game parameters
bool gameRunning = true;

// time management
double lag = MS_PER_UPDATE;
int lastTime;
int currentTime;

// positions
int borders[SCREEN_WIDTH][SCREEN_HEIGHT];
struct Positions snakePosition[(SCREEN_WIDTH)*(SCREEN_HEIGHT)];
struct Positions fruitPositions[FRUIT_AMOUNT];

// keyboard interaction
enum{ KEY_ESC = 27, KEY_LEFT = 75, KEY_RIGHT = 77, KEY_UP = 72, KEY_DOWN = 80 };
enum{NONE = 0, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4};

void main() {

	float elapsed;

	// create borders
	CreateBorders();
	PrintBorders();

	// create first fruit
	CreateFruit();
	
	// set snake entrance point
	int snakeHeadX = (SCREEN_WIDTH - 1) / 2;
	int snakeHeadY = (SCREEN_HEIGHT - 1) / 2;
	snakePosition[0].x = snakeHeadX;
	snakePosition[0].y = snakeHeadY;

	// set last time
	lastTime = getCurrentTimeInMillis();

	while (gameRunning)
	{
		UserInput();

		// get current time
		currentTime = getCurrentTimeInMillis();

		// if the time set in lag has passed since last time was taken then update the game. 
		// this is done so that the game will update at the same time for every computer and not
		// based on processor speed
		elapsed = currentTime - lastTime;
		if (elapsed > lag)
		{
			// update game
			Update();
			Draw();

			// update last time to lag game again
			lastTime = getCurrentTimeInMillis();
		}

	}

	// removes inside coding when you stop the game
	system("pause>0");
}

int getCurrentTimeInMillis()
{
	struct timespec now;
	timespec_get(&now, TIME_UTC);
	return ((int)now.tv_sec) * 1000 + ((int)now.tv_nsec) / 1000000;
}

int random_number(int min_num, int max_num)
{
	int result = 0, low_num = 0, hi_num = 0;

	if (min_num < max_num)
	{
		low_num = min_num;
		hi_num = max_num + 1; // include max_num in output
	}
	else {
		low_num = max_num + 1; // include max_num in output
		hi_num = min_num;
	}

	srand(time(NULL));
	result = (rand() % (hi_num - low_num)) + low_num;
	return result;
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
		lastDirection = LEFT;
		break;
	case KEY_RIGHT:
		lastDirection = RIGHT;
		break;
	case KEY_UP:
		lastDirection = UP;
		break;
	case KEY_DOWN:
		lastDirection = DOWN;
		break;
	}

	// reset keycode
	keyCode = 0;
}

void Update()
{

	MoveSnake();

	CheckWallCollision();

	CheckSelfCollision();

	CheckFruitCollision();

}

void Draw()
{

	// print snake
	PrintSnake();

}

void CreateBorders()
{
	for (size_t y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (size_t x = 0; x < SCREEN_WIDTH; x++)
		{
			// set borders
			if (y == 0 || y == SCREEN_HEIGHT - 1 || x == 0 || x == SCREEN_WIDTH - 1)
			{
				borders[x][y] = 1;
			}
		}
	}
}

void PrintBorders()
{
	// print screen matrix
	for (size_t y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (size_t x = 0; x < SCREEN_WIDTH; x++)
		{
			
			// print borders
			if (borders[x][y] == 1)
			{
				// move cursor to console position
				gotoxy(x, y);

				// print border
				printf("%c", '*');
			}

		}
		printf("\n");
	}
}

void PrintSnake()
{
	for (size_t i = 0; i < snakeLength; i++)
	{
		gotoxy(snakePosition[i].x, snakePosition[i].y);
		printf("%c", 'O');
	}

	if (removeLastSnakeLink)
	{
		removeLastSnakeLink = false;

		// remove last snake link
		gotoxy(lastSnakeXToRemove, lastSnakeYToRemove);
		printf("%c", ' ');
	}
}

void CreateFruit()
{
	// remove last fruit
	gotoxy(fruitPositions[0].x, fruitPositions[0].y);
	printf("%c", ' ');

	// create new fruit
	int randomX = random_number(1, SCREEN_WIDTH - 1);
	int randomY = random_number(1, SCREEN_HEIGHT - 1);

	fruitPositions[0].x = randomX;
	fruitPositions[0].y = randomY;

	PrintFruit();
}

void PrintFruit()
{
	gotoxy(fruitPositions[0].x, fruitPositions[0].y);
	printf("%c", 'X');
}

void MoveSnake() 
{

	// if snake has started moving remove the last link
	if (lastDirection != 0 && !snakeShouldGrow)
	{
		removeLastSnakeLink = true;

		// remove last snake link at position
		lastSnakeXToRemove = snakePosition[0].x;
		lastSnakeYToRemove = snakePosition[0].y;
	}

	if (!snakeShouldGrow) {
		if (snakeLength > 1) {
			for (size_t i = 0; i < snakeLength - 1; i++)
			{
				snakePosition[i].x = snakePosition[i + 1].x;
				snakePosition[i].y = snakePosition[i + 1].y;
			}
		}
	}
	else
	{
		// just let the snake lengthen
	}

	// reset snake growth
	if (snakeShouldGrow) {
		snakeLength = snakeLength + 1;
		switch (lastDirection)
		{
		case LEFT:
			snakePosition[snakeLength - 1].x = snakePosition[snakeLength - 2].x - 1;
			snakePosition[snakeLength - 1].y = snakePosition[snakeLength - 2].y;
			break;
		case RIGHT:
			snakePosition[snakeLength - 1].x = snakePosition[snakeLength - 2].x + 1;
			snakePosition[snakeLength - 1].y = snakePosition[snakeLength - 2].y;
			break;
		case UP:
			snakePosition[snakeLength - 1].x = snakePosition[snakeLength - 2].x;
			snakePosition[snakeLength - 1].y = snakePosition[snakeLength - 2].y - 1;
			break;
		case DOWN:
			snakePosition[snakeLength - 1].x = snakePosition[snakeLength - 2].x;
			snakePosition[snakeLength - 1].y = snakePosition[snakeLength - 2].y + 1;
			break;
		}
		snakeShouldGrow = false;
	}
	else 
	{
		switch (lastDirection)
		{
		case LEFT:
			snakePosition[snakeLength - 1].x = snakePosition[snakeLength - 1].x - 1;
			break;
		case RIGHT:
			snakePosition[snakeLength - 1].x = snakePosition[snakeLength - 1].x + 1;
			break;
		case UP:
			snakePosition[snakeLength - 1].y = snakePosition[snakeLength - 1].y - 1;
			break;
		case DOWN:
			snakePosition[snakeLength - 1].y = snakePosition[snakeLength - 1].y + 1;
			break;
		}
	}

	

}

bool CheckWallCollision()
{
	// on wall collision do end sequence and stop game
	
	// get user input if he/she wants to play a new game

	// restart game
}

bool CheckSelfCollision()
{

}

bool CheckFruitCollision()
{
	// check if head is colliding with fruit in fruit array
	// if it is grow snake and make a new fruit
	if (snakePosition[snakeLength - 1].x == fruitPositions[0].x && snakePosition[snakeLength - 1].y == fruitPositions[0].y)
	{
		// grow snake by one
		GrowSnake();

		// create a new fruit
		CreateFruit();
	}
}

void GrowSnake() 
{
	snakeShouldGrow = true;
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

