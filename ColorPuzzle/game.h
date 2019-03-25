#pragma once

#define size 5
void initBoard(float board[size][size][3], float color1[3], float color2[3], float color3[3], float color4[3]);
void scrambleBoard(float board[size][size][3], int steps);
void lerpColorF(float nextColor[3], float color1[3], float color2[3], int currentStep, int totalSteps);
void makeVerticalMove(int x, int dir, float board[size][size][3]);
void makeHorizontalMove(int y, int dir, float board[size][size][3]);
int checkBoard(float board[size][size][3], float boardSolved[size][size][3]);
