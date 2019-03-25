
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


void initBoard(int sizeX, int sizeY, float board[16][16][3], float color1[3], float color2[3], float color3[3], float color4[3])
{
	for (int y = 0; y < sizeY; y++)
	{
		float nextColorLeft[3] = { 0 };
		lerpColorF(nextColorLeft, color1, color3, y, sizeY - 1);
		board[y][0][0] = nextColorLeft[0];
		board[y][0][1] = nextColorLeft[1];
		board[y][0][2] = nextColorLeft[2];

		float nextColorRight[3] = { 0 };
		lerpColorF(nextColorRight, color2, color4, y, sizeY - 1);
		board[y][sizeX - 1][0] = nextColorRight[0];
		board[y][sizeX - 1][1] = nextColorRight[1];
		board[y][sizeX - 1][2] = nextColorRight[2];

		for (int x = 1; x < sizeX - 1; x++)
		{
			float nextColorX[3] = { 0 };
			lerpColorF(nextColorX, nextColorLeft, nextColorRight, x, sizeX - 1);
			board[y][x][0] = nextColorX[0];
			board[y][x][1] = nextColorX[1];
			board[y][x][2] = nextColorX[2];
		}
	}

}

void scrambleBoard(int sizeX, int sizeY, float board[16][16][3], int steps)
{

}

void lerpColorF(float nextColor[3], float color1[3], float color2[3], int currentStep, int totalSteps)
{
	nextColor[0] = (1 - (float)currentStep / totalSteps)*color1[0] + ((float)currentStep / totalSteps)*color2[0];
	nextColor[1] = (1 - (float)currentStep / totalSteps)*color1[1] + ((float)currentStep / totalSteps)*color2[1];
	nextColor[2] = (1 - (float)currentStep / totalSteps)*color1[2] + ((float)currentStep / totalSteps)*color2[2];
}

void makeVerticalMove(int x, int dir, int sizeY, float board[16][16][3])
{
	float temp[3];
	dir *= -1;
	if (dir == -1)
	{
		temp[0] = board[sizeY-1][x][0];
		temp[1] = board[sizeY-1][x][1];
		temp[2] = board[sizeY-1][x][2];
	}
	else if (dir == 1)
	{
		temp[0] = board[0][x][0];
		temp[1] = board[0][x][1];
		temp[2] = board[0][x][2];
	}
	else
	{
		printf("\n\nFAIL dir=%d\n\n", dir);
	}

	for (int i = 0; i < sizeY - 1; i++)
	{
		int index = (dir * i) - ((sizeY - 1)*(dir - 1) / 2);
		board[index][x][0] = board[index+dir][x][0];
		board[index][x][1] = board[index+dir][x][1];
		board[index][x][2] = board[index+dir][x][2];
	}

	if (dir == -1)
	{
		board[0][x][0] = temp[0];
		board[0][x][1] = temp[1];
		board[0][x][2] = temp[2];
	}

	if (dir == 1)
	{
		board[sizeY-1][x][0] = temp[0];
		board[sizeY-1][x][1] = temp[1];
		board[sizeY-1][x][2] = temp[2];
	}

}

void makeHorizontalMove(int y, int dir, int sizeX, float board[16][16][3])
{
	float temp[3];
	dir *= -1;
	if (dir == -1)
	{
		temp[0] = board[y][sizeX - 1][0];
		temp[1] = board[y][sizeX - 1][1];
		temp[2] = board[y][sizeX - 1][2];
	}
	else if (dir == 1)
	{
		temp[0] = board[y][0][0];
		temp[1] = board[y][0][1];
		temp[2] = board[y][0][2];
	}
	else
	{
		printf("\n\nFAIL dir=%d\n\n", dir);
	}

	for (int i = 0; i < sizeX - 1; i++)
	{
		int index = (dir * i) - ((sizeX - 1)*(dir - 1) / 2);
		board[y][index][0] = board[y][index + dir][0];
		board[y][index][1] = board[y][index + dir][1];
		board[y][index][2] = board[y][index + dir][2];
	}

	if (dir == -1)
	{
		board[y][0][0] = temp[0];
		board[y][0][1] = temp[1];
		board[y][0][2] = temp[2];
	}

	if (dir == 1)
	{
		board[y][sizeX-1][0] = temp[0];
		board[y][sizeX - 1][1] = temp[1];
		board[y][sizeX - 1][2] = temp[2];
	}

}