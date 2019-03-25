
/*
 * File:   main.c
 * Author: Ben Brienen
 *
 * Created on March 20, 2019, 1:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "Rendering.h"
#include <time.h>


void initBoard(float board[size][size][3], float color1[3], float color2[3], float color3[3], float color4[3])
{
	for (int y = 0; y < size; y++)
	{
		float nextColorLeft[3] = { 0 };
		lerpColorF(nextColorLeft, color1, color3, y, size - 1);
		board[y][0][0] = nextColorLeft[0];
		board[y][0][1] = nextColorLeft[1];
		board[y][0][2] = nextColorLeft[2];

		float nextColorRight[3] = { 0 };
		lerpColorF(nextColorRight, color2, color4, y, size - 1);
		board[y][size - 1][0] = nextColorRight[0];
		board[y][size - 1][1] = nextColorRight[1];
		board[y][size - 1][2] = nextColorRight[2];

		for (int x = 1; x < size - 1; x++)
		{
			float nextColorX[3] = { 0 };
			lerpColorF(nextColorX, nextColorLeft, nextColorRight, x, size - 1);
			board[y][x][0] = nextColorX[0];
			board[y][x][1] = nextColorX[1];
			board[y][x][2] = nextColorX[2];
		}
	}

}

void scrambleBoard(float board[size][size][3], int steps)
{
	srand(time(0));
	for (int i = 1; i < 100; i++)
	{
		int randX = rand() % size;
		int randY = rand() % size;

		if (randX == 0 || randY == 0)
		{
			continue;
		}

		if (randX == size-1 || randY == size-1)
		{
			continue;
		}

		makeHorizontalMove(randX, 1, board);
		makeVerticalMove(randY, 1, board);
	}
}

void lerpColorF(float nextColor[3], float color1[3], float color2[3], int currentStep, int totalSteps)
{
	nextColor[0] = (1 - (float)currentStep / totalSteps)*color1[0] + ((float)currentStep / totalSteps)*color2[0];
	nextColor[1] = (1 - (float)currentStep / totalSteps)*color1[1] + ((float)currentStep / totalSteps)*color2[1];
	nextColor[2] = (1 - (float)currentStep / totalSteps)*color1[2] + ((float)currentStep / totalSteps)*color2[2];
}

void makeVerticalMove(int x, int dir, float board[size][size][3])
{
	float temp[3];
	dir *= -1;
	if (dir == -1)
	{
		temp[0] = board[size - 2][x][0];
		temp[1] = board[size - 2][x][1];
		temp[2] = board[size - 2][x][2];
	}
	else if (dir == 1)
	{
		temp[0] = board[1][x][0];
		temp[1] = board[1][x][1];
		temp[2] = board[1][x][2];
	}
	else
	{
		printf("\n\nFAIL dir=%d\n\n", dir);
	}

	for (int i = 1; i < size - 2; i++)
	{
		int index = (dir * i) - ((size - 1)*(dir - 1) / 2);
		board[index][x][0] = board[index + dir][x][0];
		board[index][x][1] = board[index + dir][x][1];
		board[index][x][2] = board[index + dir][x][2];
	}

	if (dir == -1)
	{
		board[1][x][0] = temp[0];
		board[1][x][1] = temp[1];
		board[1][x][2] = temp[2];
	}

	if (dir == 1)
	{
		board[size - 2][x][0] = temp[0];
		board[size - 2][x][1] = temp[1];
		board[size - 2][x][2] = temp[2];
	}

}

void makeHorizontalMove(int y, int dir, float board[size][size][3])
{
	float temp[3];
	dir *= -1;
	if (dir == -1)
	{
		temp[0] = board[y][size - 2][0];
		temp[1] = board[y][size - 2][1];
		temp[2] = board[y][size - 2][2];
	}
	else if (dir == 1)
	{
		temp[0] = board[y][1][0];
		temp[1] = board[y][1][1];
		temp[2] = board[y][1][2];
	}
	else
	{
		printf("\n\nFAIL dir=%d\n\n", dir);
	}

	for (int i = 1; i < size - 2; i++)
	{
		int index = (dir * i) - ((size - 1)*(dir - 1) / 2);
		board[y][index][0] = board[y][index + dir][0];
		board[y][index][1] = board[y][index + dir][1];
		board[y][index][2] = board[y][index + dir][2];
	}

	if (dir == -1)
	{
		board[y][1][0] = temp[0];
		board[y][1][1] = temp[1];
		board[y][1][2] = temp[2];
	}

	if (dir == 1)
	{
		board[y][size - 2][0] = temp[0];
		board[y][size - 2][1] = temp[1];
		board[y][size - 2][2] = temp[2];
	}

}

int checkBoard(float board[size][size][3], float boardSolved[size][size][3])
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (board[i][j][k] - boardSolved[i][j][k] > 0.01f)
					return 0;
			}
		}
	}
	return 1;
}