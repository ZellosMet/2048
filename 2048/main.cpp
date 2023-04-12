#include<iostream>
#include<conio.h>
#include<time.h>
#include<windows.h>

#define MOVE_LEFT 75  //Задание переменных для отлова с клавиатуры
#define MOVE_RIGHT 77
#define MOVE_UP 72
#define MOVE_DOWN 80
#define RESET 114
#define RESET_RU 170
#define ESC 27

const int SIZE_GRID = 4;

void Print_Grid(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, int *pscore); // Функция вывода сетки
void Fusion_Up(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, int *pscore, bool *pcheck_move); //Функции слияния блоков одного номинала
void Fusion_Down(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, int *pscore, bool* pcheck_move);
void Fusion_Right(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, int *pscore, bool* pcheck_move);
void Fusion_Left(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, int *pscore, bool* pcheck_move);
void Shift_Up(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, bool* pcheck_move); //Функция смещения блоков
void Shift_Down(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, bool* pcheck_move);
void Shift_Right(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, bool* pcheck_move);
void Shift_Left(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, bool* pcheck_move);
int Loss_check(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID); //Функция проверки на проигрыш
void Reset(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, int *pscore); //Функция рестарта
void Block_Generation(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, bool *pcheck_move); //Функция генерации новых блоков


void main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "ru");

	int score = 0;
	int *pscore = &score;
	int control;
	bool check_move = true;
	bool *pcheck_move = &check_move;
	int grid[SIZE_GRID][SIZE_GRID] = {};	

	Block_Generation(grid, SIZE_GRID, pcheck_move);
	check_move = true;
	Block_Generation(grid, SIZE_GRID, pcheck_move);
	Print_Grid(grid, SIZE_GRID, pscore);
	std::cout << "\nУправление: стрелочками производится смещение блоков, r - Рестарт, ESC - Выход";
	do //Цикл отлова событий
	{
		control = _getch();
		switch (control)
		{
		case MOVE_UP:	Shift_Up(grid, SIZE_GRID, pcheck_move); Fusion_Up(grid, SIZE_GRID, pscore, pcheck_move); Shift_Up(grid, SIZE_GRID, pcheck_move); 
						Print_Grid(grid, SIZE_GRID, pscore); Block_Generation(grid, SIZE_GRID, pcheck_move); Sleep(150); Print_Grid(grid, SIZE_GRID, pscore); 
						Loss_check(grid, SIZE_GRID); break;
		case MOVE_DOWN: Shift_Down(grid, SIZE_GRID, pcheck_move); Fusion_Down(grid, SIZE_GRID, pscore, pcheck_move); Shift_Down(grid, SIZE_GRID, pcheck_move); 
						Print_Grid(grid, SIZE_GRID, pscore); Block_Generation(grid, SIZE_GRID, pcheck_move); Sleep(150); Print_Grid(grid, SIZE_GRID, pscore);
						Loss_check(grid, SIZE_GRID); break;
		case MOVE_RIGHT:Shift_Right(grid, SIZE_GRID, pcheck_move); Fusion_Right(grid, SIZE_GRID, pscore, pcheck_move); Shift_Right(grid, SIZE_GRID, pcheck_move);
						Print_Grid(grid, SIZE_GRID, pscore); Block_Generation(grid, SIZE_GRID, pcheck_move); Sleep(150); Print_Grid(grid, SIZE_GRID, pscore);
						Loss_check(grid, SIZE_GRID); break;
		case MOVE_LEFT: Shift_Left(grid, SIZE_GRID, pcheck_move); Fusion_Left(grid, SIZE_GRID, pscore, pcheck_move); Shift_Left(grid, SIZE_GRID, pcheck_move); 
						Print_Grid(grid, SIZE_GRID, pscore); Block_Generation(grid, SIZE_GRID, pcheck_move); Sleep(150); Print_Grid(grid, SIZE_GRID, pscore);
						Loss_check(grid, SIZE_GRID); break;
		case RESET:		Reset(grid, SIZE_GRID, pscore); check_move = true; Block_Generation(grid, SIZE_GRID, pcheck_move); check_move = true; 
						Block_Generation(grid, SIZE_GRID, pcheck_move); Print_Grid(grid, SIZE_GRID, pscore); break;
		case RESET_RU:	Reset(grid, SIZE_GRID, pscore); check_move = true; Block_Generation(grid, SIZE_GRID, pcheck_move); check_move = true; 
						Block_Generation(grid, SIZE_GRID, pcheck_move); Print_Grid(grid, SIZE_GRID, pscore); break;
		}
	} while (control != ESC);
}

void Reset(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, int *pscore)
{
	for (int i = 0; i < SIZE_GRID; i++)
	{
		for (int j = 0; j < SIZE_GRID; j++)
		{
			grid[i][j] = 0;
		}
	}
	*pscore = 0;
}

void Print_Grid(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, int *pscore)
{
	system("cls");
	for (int i = 0; i < SIZE_GRID; i++)
	{
		for (int j = 0; j < SIZE_GRID; j++)
		{
			if (grid[i][j] == 0) std::cout << "[     ] ";
			else if (grid[i][j] < 10) std::cout << "[  " << grid[i][j] << "  ] ";
			else if (grid[i][j] >= 10 && grid[i][j] < 100) std::cout << "[  " << grid[i][j] << " ] ";
			else if (grid[i][j] >= 100 && grid[i][j] < 1000) std::cout << "[ " << grid[i][j] << " ] ";
			else if (grid[i][j] >= 1000 && grid[i][j] < 10000) std::cout << "[ " << grid[i][j] << "] ";
			else std::cout << "[" << grid[i][j] << "] ";
		}
		std::cout << std::endl;
	}
	std::cout << "\t    Счёт: " << *pscore << std::endl;
}

void Block_Generation(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, bool *pcheck_move)
{	
	if (*pcheck_move) //Проверка на смещение блоков
	{
		bool set = true; // Проверка на установку блока в свободную ячейку
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

void Fusion_Up(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, int *pscore, bool* pcheck_move)
{
	for (int i = 0; i < SIZE_GRID; i++)
	{
		for (int j = 0; j < SIZE_GRID; j++)
		{
			if (grid[i + 1][j] == grid[i][j] && grid[i][j] != 0)
			{
				grid[i][j] += grid[i+1][j];
				grid[i+1][j] = 0;
				*pscore += grid[i][j];
				*pcheck_move = true;
			}
		}
	}
}
void Fusion_Down(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, int *pscore, bool* pcheck_move)
{
	for (int i = SIZE_GRID - 1; i > 0; i--)
	{
		for (int j = 0; j < SIZE_GRID; j++)
		{
			if (grid[i - 1][j] == grid[i][j] && grid[i][j] != 0)
			{
				grid[i][j] += grid[i-1][j];
				grid[i-1][j] = 0;
				*pscore += grid[i][j];
				*pcheck_move = true;
			}
		}
	}
}
void Fusion_Right(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, int *pscore, bool* pcheck_move)
{
	for (int i = 0; i < SIZE_GRID; i++)
	{
		for (int j = SIZE_GRID - 1; j > 0; j--)
		{
			if (grid[i][j-1] == grid[i][j] && grid[i][j] != 0)
			{
				grid[i][j] += grid[i][j-1];
				grid[i][j-1] = 0;
				*pscore += grid[i][j];
				*pcheck_move = true;
			}
		}
	}
}
void Fusion_Left(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, int *pscore, bool* pcheck_move)
{
	for (int i = 0; i < SIZE_GRID; i++)
	{
		for (int j = 0; j < SIZE_GRID; j++)
		{
			if (grid[i][j+1] == grid[i][j] && grid[i][j] != 0)
			{
				grid[i][j] += grid[i][j+1];
				grid[i][j+1] = 0;
				*pscore += grid[i][j];
				*pcheck_move = true;
			}
		}
	}
}

void Shift_Up(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, bool* pcheck_move)
{
	for (int k = 0; k < SIZE_GRID-1; k++)
	{
		for (int i = SIZE_GRID-1; i > 0; i--)
		{
			for (int j = 0; j < SIZE_GRID; j++)
			{
				if (grid[i-1][j] == 0 && grid[i][j] != 0)
				{
					grid[i-1][j] = grid[i][j];
					grid[i][j] = 0;
					*pcheck_move = true;
				}
			}
		}
	}
}
void Shift_Down(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, bool* pcheck_move)
{
	for (int k = 0; k < SIZE_GRID-1; k++)
	{
		for (int i = 0; i < SIZE_GRID; i++)
		{
			for (int j = 0; j < SIZE_GRID; j++)
			{
				if (grid[i+1][j] == 0 && grid[i][j] != 0)
				{
					grid[i+1][j] = grid[i][j];
					grid[i][j] = 0;
					*pcheck_move = true;
				}
			}
		}
	}
}
void Shift_Right(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, bool* pcheck_move)
{
	for (int k = 0; k < SIZE_GRID-1; k++)
	{
		for (int i = 0; i < SIZE_GRID; i++)
		{
			for (int j = 0; j < SIZE_GRID-1; j++)
			{
				if (grid[i][j+1] == 0 && grid[i][j] != 0)
				{
					grid[i][j+1] = grid[i][j];
					grid[i][j] = 0;
					*pcheck_move = true;
				}
			}
		}
	}
}
void Shift_Left(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID, bool* pcheck_move)
{
	for (int k = 0; k < SIZE_GRID-1; k++)
	{
		for (int i = 0; i < SIZE_GRID; i++)
		{
			for (int j = SIZE_GRID-1; j > 0; j--)
			{
				if (grid[i][j-1] == 0 && grid[i][j] != 0)
				{
					grid[i][j-1] = grid[i][j];
					grid[i][j] = 0;
					*pcheck_move = true;
				}
			}
		}
	}
}

int Loss_check(int grid[SIZE_GRID][SIZE_GRID], int SIZE_GRID)
{
	for (int i = 0; i < SIZE_GRID; i++)
	{
		for (int j = 0; j < SIZE_GRID; j++)
		{
			if (grid[i][j]==0 || grid[i + 1][j] == grid[i][j] ||  grid[i - 1][j] == grid[i][j] || grid[i][j + 1] == grid[i][j] || grid[i][j - 1] == grid[i][j])
			{
				return 0;
			}
		}
	}
	std::cout << "\t Игра окончена!\n   r - Рестарт, ESC - Выход\n";
	return 0;
}