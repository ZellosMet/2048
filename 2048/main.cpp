#include<iostream>
#include<conio.h>
#include<time.h>

using namespace std;

#define MOVE_LEFT 75  //Задание переменных для отлова с клавиатуры
#define MOVE_RIGHT 77
#define MOVE_UP 72
#define MOVE_DOWN 80
#define ENTER 13
#define ESC 27

const int SIZE = 4;

void Print_Grid(int grid[SIZE][SIZE], int SIZE); // Функция вывода сетки
void Move_Up(int grid[SIZE][SIZE], int SIZE); //Функции смещения
void Move_Down(int grid[SIZE][SIZE], int SIZE);
void Move_Right(int grid[SIZE][SIZE], int SIZE);
void Move_Left(int grid[SIZE][SIZE], int SIZE);
int Сheck_for_Loss(int grid[SIZE][SIZE], int SIZE); //Функция проверки на проигрыш

void test(int grid[SIZE][SIZE], int SIZE)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			grid[i][j] = 0;
		}
	}
}

void Block_Generation(int grid[SIZE][SIZE], int SIZE);

void main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "ru");

	int control;
	int grid[SIZE][SIZE] = {};	

	Block_Generation(grid, SIZE);
	Block_Generation(grid, SIZE);	

	Print_Grid(grid, SIZE);

	do //Цикл отлова событий
	{
		control = _getch();
		switch (control)
		{
		case MOVE_UP: Move_Up(grid, SIZE); Block_Generation(grid, SIZE); Print_Grid(grid, SIZE); control = Сheck_for_Loss(grid, SIZE); break;
		case MOVE_DOWN: Move_Down(grid, SIZE); Block_Generation(grid, SIZE); Print_Grid(grid, SIZE); control = Сheck_for_Loss(grid, SIZE); break;
		case MOVE_RIGHT: Move_Right(grid, SIZE); Block_Generation(grid, SIZE); Print_Grid(grid, SIZE); control = Сheck_for_Loss(grid, SIZE); break;
		case MOVE_LEFT: Move_Left(grid, SIZE); Block_Generation(grid, SIZE); Print_Grid(grid, SIZE); ; control = Сheck_for_Loss(grid, SIZE); break;
		case ENTER: Block_Generation(grid, SIZE); Print_Grid(grid, SIZE); control = Сheck_for_Loss(grid, SIZE); break;
		}
	} while (control != ESC);
}

void Print_Grid(int grid[SIZE][SIZE], int SIZE)
{
	system("cls");
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (grid[i][j] == 0) cout << "[     ] ";
			else if (grid[i][j] < 10) cout << "[    " << grid[i][j] << "] ";
			else if (grid[i][j] >= 10 && grid[i][j] < 100) cout << "[   " << grid[i][j] << "] ";
			else if (grid[i][j] >= 100 && grid[i][j] < 1000) cout << "[  " << grid[i][j] << "] ";
			else if (grid[i][j] >= 1000 && grid[i][j] < 10000) cout << "[ " << grid[i][j] << "] ";
			else cout << "[" << grid[i][j] << "] ";
		}
		cout << endl;
	}
}

void Block_Generation(int grid[SIZE][SIZE], int SIZE)
{	
	bool set = true;
	do
	{
		int position_i = rand() % 4;
		int position_j = rand() % 4;
		int block = (rand() % 10) <= 0 ? 4 : 2;
		if (grid[position_i][position_j] == 0)
		{
			grid[position_i][position_j] = block; 
			set = false;
		}
	} while (set);
}

void Move_Up(int grid[SIZE][SIZE], int SIZE)
{
	for (int k = 0; k < SIZE-1; k++)
	{
		for (int i = 1; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				if (grid[i - 1][j] == grid[i][j])
				{
					grid[i - 1][j] += grid[i][j];
					grid[i][j] = 0;
					continue;
				}
				else if (grid[i - 1][j] == 0)
				{
					grid[i - 1][j] ^= grid[i][j];
					grid[i][j] ^= grid[i - 1][j];
					grid[i - 1][j] ^= grid[i][j];
				}
			}
		}
	}
}
void Move_Down(int grid[SIZE][SIZE], int SIZE)
{
	for (int k = 0; k < SIZE - 1; k++)
	{
		for (int i = SIZE-2; i >= 0; i--)
		{
			for (int j = SIZE-1; j >= 0; j--)
			{
				if (grid[i + 1][j] == grid[i][j])
				{
					grid[i + 1][j] += grid[i][j];
					grid[i][j] = 0;
				}
				else if (grid[i + 1][j] == 0)
				{
					grid[i + 1][j] ^= grid[i][j];
					grid[i][j] ^= grid[i + 1][j];
					grid[i + 1][j] ^= grid[i][j];
				}
			}
		}
	}
}
void Move_Right(int grid[SIZE][SIZE], int SIZE)
{
	for (int k = 0; k < SIZE - 1; k++)
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = SIZE-2; j >=0 ; j--)
			{
				if (grid[i][j+1] == grid[i][j])
				{
					grid[i][j+1] += grid[i][j];
					grid[i][j] = 0;
				}
				else if (grid[i][j+1] == 0)
				{
					grid[i][j+1] ^= grid[i][j];
					grid[i][j] ^= grid[i][j+1];
					grid[i][j+1] ^= grid[i][j];
				}
			}
		}
	}
}
void Move_Left(int grid[SIZE][SIZE], int SIZE)
{
	for (int k = 0; k < SIZE - 1; k++)
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 1; j < SIZE; j++)
			{
				if (grid[i][j - 1] == grid[i][j])
				{
					grid[i][j - 1] += grid[i][j];
					grid[i][j] = 0;
				}
				else if (grid[i][j - 1] == 0)
				{
					grid[i][j - 1] ^= grid[i][j];
					grid[i][j] ^= grid[i][j - 1];
					grid[i][j - 1] ^= grid[i][j];
				}
			}
		}
	}
}
int Сheck_for_Loss(int grid[SIZE][SIZE], int SIZE)
{

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (grid[i][j]==0)
			{
				return 0;
			}
		}
	}
	cout << "Играокончена!";
	return ESC;

}