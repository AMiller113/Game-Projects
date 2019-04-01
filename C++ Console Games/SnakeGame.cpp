#include<ctime>
#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

/*

Global Variables

*/

bool game_over;
const int width = 20;
const int height = 20;
int x, y, fruit_x, fruit_y, score;
int tail_x[100], tail_y[100];
int n_tail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection current_direction;

void SetFruitLocation();

/*

Core gameplay functions

*/

void Setup() {

	game_over = false;
	current_direction = STOP;
	x = width / 2;
	y = height / 2;
	SetFruitLocation();
}

void Draw() {

	system("cls");

	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height - 1; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				cout << "#";
				continue;
			}
		   
			if (j == width- 1)
			{
				cout << "#";
				continue;
			}

		    if (i == y && j == x) {
				cout << "O";
			}
			else if(i == fruit_y && j == fruit_x)
			{
				cout << "@";
			}
			else
			{
				bool print = false;

				for (int k = 0; k < n_tail; k++)
				{
					if (tail_x[k] == j && tail_y[k] == i)
					{
						cout << "o";
						print = true;
					}
				}

				if (!print)
				{
					cout << " ";
				}
					
			}

		}
		cout << endl;
	}

	for (int i = 0; i < width; i++)
		cout << "#";

	cout << endl;

	cout << "Score: " << score << endl;
}

void Input() {
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			current_direction = LEFT;
			break;
		case 'd':
			current_direction = RIGHT;
			break;
		case 'w':
			current_direction = UP;
			break;
		case 's':
			current_direction = DOWN;
			break;
		case 'x':
			game_over = true;
			break;

		default:
			break;
		}
	}
}

void Logic() {

	int prev_X = tail_x[0];
	int prev_Y = tail_y[0];
	int prev2x, prev2y;

	tail_x[0] = x;
	tail_y[0] = y;

	for (int i = 1; i < n_tail; i++)
	{
		prev2x = tail_x[i];
		prev2y = tail_y[i];

		tail_x[i] = prev_X;
		tail_y[i] = prev_Y;

		prev_X = prev2x;
		prev_Y = prev2y;
	}

	switch (current_direction) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (x >= width || x <= 0|| y >= height || y <= 0)
	{
		game_over = true;
	}
	
	for (int i = 0; i < n_tail; i++)
	{
		if (tail_x[i] == x && tail_y[i] == y)
			game_over = true;
	}

	if (x == fruit_x && y == fruit_y)
	{
		score+=10;
		n_tail++;
		SetFruitLocation();
	}
}

void SetFruitLocation() {

	srand(time(NULL));
	fruit_x = rand() % width;
	fruit_y = rand() % height;

	//check for valid fruit location (one that isn't on the map edges)

	while (fruit_x == 19|| fruit_x == 0)
	{
		fruit_x = rand() % width;
	}

	while (fruit_y == 19||fruit_y == 0)
	{
		fruit_y = rand() % height;
	}

}

int main() {

	Setup();

	while (!game_over)
	{
		Input();
		Logic();
		Draw();
		Sleep(85);
	}

	return 0;
}