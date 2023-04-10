#include<iostream>
#include<conio.h>
#include<time.h>

using namespace std;

#define MOVE_LEFT 75  //Задание переменных для отлова с клавиатуры
#define MOVE_RIGHT 77
#define MOVE_UP 72
#define MOVE_DOWN 80
#define ENTER 13
#define RESET 114
#define ESC 27

const int SIZE = 4;

void Print_Grid(int grid[SIZE][SIZE], int SIZE); // Функция вывода сетки
void Fusion_Up(int grid[SIZE][SIZE], int SIZE); //Функции слияния блоков одного номинала
void Fusion_Down(int grid[SIZE][SIZE], int SIZE);
void Fusion_Right(int grid[SIZE][SIZE], int SIZE);
void Fusion_Left(int grid[SIZE][SIZE], int SIZE);
void Shift_Up(int grid[SIZE][SIZE], int SIZE, bool* pcheck_move); //Функция смещения блоков
void Shift_Down(int grid[SIZE][SIZE], int SIZE, bool* pcheck_move);
void Shift_Right(int grid[SIZE][SIZE], int SIZE, bool* pcheck_move);
void Shift_Left(int grid[SIZE][SIZE], int SIZE, bool* pcheck_move);
int Сheck_for_Loss(int grid[SIZE][SIZE], int SIZE); //Функция проверки на проигрыш
void Reset(int grid[SIZE][SIZE], int SIZE); //Функция рестарта
void Block_Generation(int grid[SIZE][SIZE], int SIZE, bool *pcheck_move); //Функция генерации новых блоков


void main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "ru");

	int control;
	bool check_move = true;
	bool *pcheck_move = &check_move;
	int grid[SIZE][SIZE] = {};	

	Block_Generation(grid, SIZE, pcheck_move);
	check_move = true;
	Block_Generation(grid, SIZE, pcheck_move);

	Print_Grid(grid, SIZE);
	
	do //Цикл отлова событий
	{
		control = _getch();
		switch (control)
		{
		case MOVE_UP: Shift_Up(grid, SIZE, pcheck_move); Fusion_Up(grid, SIZE); Shift_Up(grid, SIZE, pcheck_move); Block_Generation(grid, SIZE, pcheck_move); Print_Grid(grid, SIZE); control = Сheck_for_Loss(grid, SIZE); break;
		case MOVE_DOWN: Shift_Down(grid, SIZE, pcheck_move); Fusion_Down(grid, SIZE); Shift_Down(grid, SIZE, pcheck_move); Block_Generation(grid, SIZE, pcheck_move); Print_Grid(grid, SIZE); control = Сheck_for_Loss(grid, SIZE); break;
		case MOVE_RIGHT:Shift_Right(grid, SIZE, pcheck_move); Fusion_Right(grid, SIZE); Shift_Right(grid, SIZE, pcheck_move); Block_Generation(grid, SIZE, pcheck_move); Print_Grid(grid, SIZE); control = Сheck_for_Loss(grid, SIZE); break;
		case MOVE_LEFT: Shift_Left(grid, SIZE, pcheck_move); Fusion_Left(grid, SIZE); Shift_Left(grid, SIZE, pcheck_move); Block_Generation(grid, SIZE, pcheck_move); Print_Grid(grid, SIZE); control = Сheck_for_Loss(grid, SIZE); break;
		case RESET: Reset(grid, SIZE); Block_Generation(grid, SIZE, pcheck_move); Block_Generation(grid, SIZE, pcheck_move); Print_Grid(grid, SIZE); break;
		}
	} while (control != ESC);
}

void Reset(int grid[SIZE][SIZE], int SIZE)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			grid[i][j] = 0;
		}
	}
}

void Print_Grid(int grid[SIZE][SIZE], int SIZE)
{
	system("cls");
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (grid[i][j] == 0) cout << "[     ] ";
			else if (grid[i][j] < 10) cout << "[  " << grid[i][j] << "  ] ";
			else if (grid[i][j] >= 10 && grid[i][j] < 100) cout << "[  " << grid[i][j] << " ] ";
			else if (grid[i][j] >= 100 && grid[i][j] < 1000) cout << "[ " << grid[i][j] << " ] ";
			else if (grid[i][j] >= 1000 && grid[i][j] < 10000) cout << "[ " << grid[i][j] << "] ";
			else cout << "[" << grid[i][j] << "] ";
		}
		cout << endl;
	}
}

void Block_Generation(int grid[SIZE][SIZE], int SIZE, bool *pcheck_move)
{	
	if (*pcheck_move) //Проверка на смещение блоков
	{
		bool set = true; // Проверка на фактическую установку блока
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
	*pcheck_move = false;
}

void Fusion_Up(int grid[SIZE][SIZE], int SIZE)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (grid[i + 1][j] == grid[i][j])
			{
				grid[i][j] += grid[i+1][j];
				grid[i+1][j] = 0;
			}
		}
	}
}
void Fusion_Down(int grid[SIZE][SIZE], int SIZE)
{
	for (int i = SIZE - 1; i > 0; i--)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (grid[i - 1][j] == grid[i][j])
			{
				grid[i][j] += grid[i - 1][j];
				grid[i - 1][j] = 0;
			}
		}
	}
}
void Fusion_Right(int grid[SIZE][SIZE], int SIZE)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = SIZE - 1; j > 0; j--)
		{
			if (grid[i][j - 1] == grid[i][j])
			{
				grid[i][j] += grid[i][j - 1];
				grid[i][j - 1] = 0;
			}
		}
	}
}
void Fusion_Left(int grid[SIZE][SIZE], int SIZE)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (grid[i][j + 1] == grid[i][j])
			{
				grid[i][j] += grid[i][j + 1];
				grid[i][j + 1] = 0;
			}
		}
	}
}

void Shift_Up(int grid[SIZE][SIZE], int SIZE, bool* pcheck_move)
{
	for (int k = 0; k < SIZE - 1; k++)
	{
		for (int n = SIZE - 1; n > 0; n--)
		{
			for (int m = 0; m < SIZE; m++)
			{
				if (grid[n - 1][m] == 0 && grid[n][m] != 0)
				{
					grid[n - 1][m] = grid[n][m];
					grid[n][m] = 0;
					*pcheck_move = true;
				}
			}
		}
	}
}
void Shift_Down(int grid[SIZE][SIZE], int SIZE, bool* pcheck_move)
{
	for (int k = 0; k < SIZE - 1; k++)
	{
		for (int n = 0; n < SIZE; n++)
		{
			for (int m = 0; m < SIZE; m++)
			{
				if (grid[n + 1][m] == 0 && grid[n][m] != 0)
				{
					grid[n + 1][m] = grid[n][m];
					grid[n][m] = 0;
					*pcheck_move = true;
				}
			}
		}
	}
}
void Shift_Right(int grid[SIZE][SIZE], int SIZE, bool* pcheck_move)
{
	for (int k = 0; k < SIZE - 1; k++)
	{
		for (int n = 0; n < SIZE; n++)
		{
			for (int m = 0; m < SIZE - 1; m++)
			{
				if (grid[n][m + 1] == 0 && grid[n][m] != 0)
				{
					grid[n][m + 1] = grid[n][m];
					grid[n][m] = 0;
					*pcheck_move = true;
				}
			}
		}
	}
}
void Shift_Left(int grid[SIZE][SIZE], int SIZE, bool* pcheck_move)
{
	for (int k = 0; k < SIZE - 1; k++)
	{
		for (int n = 0; n < SIZE; n++)
		{
			for (int m = SIZE - 1; m > 0; m--)
			{
				if (grid[n][m - 1] == 0 && grid[n][m] != 0)
				{
					grid[n][m - 1] = grid[n][m];
					grid[n][m] = 0;
					*pcheck_move = true;
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
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (grid[i + 1][j] == grid[i][j])
			{
				return 0;
			}
		}
	}
	for (int i = SIZE - 1; i > 0; i--)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (grid[i - 1][j] == grid[i][j])
			{
				return 0;
			}
		}
	}
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = SIZE - 1; j > 0; j--)
		{
			if (grid[i][j - 1] == grid[i][j])
			{
				return 0;
			}
		}
	}
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (grid[i][j + 1] == grid[i][j])
			{
				return 0;
			}
		}
	}
	cout << "Играокончена!";
	return ESC;
}