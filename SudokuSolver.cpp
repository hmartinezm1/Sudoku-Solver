/*

Application: Sudoku Solver
Subject: ICOM 6025
Name: Howard Andrés Martínez Meza
Student Number: 502-15-2951

*/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <omp.h>

using namespace std;

int number_threads = 8;

bool solveSudoku(int sudoku[][9], int row, int col);
bool isEmpty(int sudoku[][9], int row, int col, int num);

bool solveSudoku(int sudoku[][9], int row, int col)
{
	int i;
	if (row<9 && col<9)
	{
		if (sudoku[row][col])
		{
			if ((col + 1)<9)
				return solveSudoku(sudoku, row, col + 1);
			else if ((row + 1)<9)
				return solveSudoku(sudoku, row + 1, 0);
			else
				return true;
		}
		else
		{
#pragma omp parallel for private(i) num_threads(number_threads)
			for (i = 0; i<9; ++i)
			{
				if (isEmpty(sudoku, row, col, i + 1))
				{
					sudoku[row][col] = i + 1;
					if ((col + 1)<9)
					{
						if (solveSudoku(sudoku, row, col))
							return true;
						else sudoku[row][col] = 0;
					}
					else if ((row + 1)<9)
					{
						if (solveSudoku(sudoku, row + 1, 0))
							return true;
						else sudoku[row][col] = 0;
					}
					else
						return true;
				}
			}
		}
		return false;
	}
	else
		return true;
}

bool isEmpty(int sudoku[][9], int row, int col, int num)
{
	int rowStart = (row / 3) * 3;
	int colStart = (col / 3) * 3;
	int i;

	for (i = 0; i<9; ++i)
	{
		if (sudoku[row][i] == num) return 0;
		if (sudoku[i][col] == num) return 0;
		if (sudoku[rowStart + (i % 3)][colStart + (i / 3)] == num)
			return false;
	}
	return true;
}

void main()
{
	clock_t startTime, endTime;
	int i, j;
	int sudoku[9][9] = { { 1, 0, 5, 0, 2, 0, 0, 4, 0 }, //Easy
	{ 0, 8, 2, 0, 0, 0, 0, 0, 0 },
	{ 7, 6, 0, 5, 0, 0, 2, 0, 0 },
	{ 0, 3, 0, 0, 5, 0, 0, 0, 9 },
	{ 5, 0, 0, 7, 8, 2, 0, 0, 6 },
	{ 0, 1, 6, 4, 0, 9, 0, 8, 0 },
	{ 0, 5, 3, 2, 0, 0, 0, 1, 4 },
	{ 4, 0, 0, 0, 0, 6, 8, 5, 7 },
	{ 0, 0, 8, 0, 0, 5, 3, 0, 0 } };
	//int sudoku[9][9] = { { 0, 0, 0, 9, 8, 0, 1, 0, 0 }, //Medium
	//{ 0, 8, 2, 0, 0, 0, 0, 3, 0 },
	//{ 0, 3, 5, 7, 1, 0, 0, 0, 0 },
	//{ 0, 0, 0, 0, 7, 0, 0, 5, 0 },
	//{ 8, 5, 0, 6, 0, 0, 0, 0, 0 },
	//{ 0, 9, 0, 0, 0, 0, 0, 0, 6 },
	//{ 0, 0, 1, 0, 0, 0, 9, 0, 0 },
	//{ 0, 4, 0, 8, 0, 1, 0, 0, 0 },
	//{ 0, 0, 0, 5, 0, 0, 0, 0, 2 } };
	//int sudoku[9][9] = { { 1, 0, 0, 4, 0, 0, 0, 0, 0 }, //Hard
	//{ 9, 3, 0, 0, 0, 0, 6, 0, 1 },
	//{ 0, 0, 0, 0, 5, 0, 7, 0, 0 },
	//{ 0, 0, 8, 6, 0, 0, 0, 0, 0 },
	//{ 0, 9, 0, 7, 0, 2, 0, 4, 0 },
	//{ 0, 0, 5, 0, 0, 0, 9, 0, 0 },
	//{ 0, 0, 0, 0, 3, 0, 0, 6, 0 },
	//{ 8, 0, 0, 0, 0, 0, 0, 1, 0 },
	//{ 0, 0, 3, 0, 7, 4, 0, 0, 8 } };

	cout << "\t\t\tICOM 6025 - Sudoku Solver \n\n";
	cout << "This application reads an incomplete Sudoku \nand show its solution in case there was one. \n\n\tThe next is the Matrix given: \n\n";
	printf("\n+-----+-----+-----+\n");
	for (i = 1; i<10; ++i)
	{
		for (i = 1; i<10; ++i)
		{
			for (j = 1; j<10; ++j) printf("|%d", sudoku[i - 1][j - 1]);
			printf("|\n");
			if (i % 3 == 0) printf("+-----+-----+-----+\n");
		}
	}
	cout << "\n\n Results:\n\n";
	startTime = clock();
	if (solveSudoku(sudoku, 0, 0))
	{
		printf("\n+-----+-----+-----+\n");
		for (i = 1; i<10; ++i)
		{
			for (j = 1; j<10; ++j) printf("|%d", sudoku[i - 1][j - 1]);
			printf("|\n");
			if (i % 3 == 0) printf("+-----+-----+-----+\n");
		}
	}
	else printf("There is no solution! \n\n");
	endTime = clock();
	cout << "\n\n";
	cout << "Time spent: " << (endTime - startTime) << " ms\n\n\n";
	system("PAUSE");
}
