#pragma once


void initBoard(float *** board, int sizeX, int sizeY, float color1[3], float color2[3], float color3[3], float color4[3]);
void scrambleBoard(float *** board, int sizeX, int sizeY, int steps);
void lerpColor(float nextColor[3], float color1[3], float color2[3], int currentStep, int totalSteps);
void makeVerticalMove(int x, int dir, float *** board, int sizeX, int sizeY);
void makeHorizontalMove(int y, int dir, float *** board, int sizeX, int sizeY);
int checkBoard(float *** board, int sizeX, int sizeY, float *** boardSolved);
