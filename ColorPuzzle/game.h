#pragma once
void initBoard(int sizeX, int sizeY, float board[16][16][3], float color1[3], float color2[3], float color3[3], float color4[3]);
void scrambleBoard(int sizeX, int sizeY, float board[16][16][3], int steps);
void lerpColorF(float nextColor[3], float color1[3], float color2[3], int currentStep, int totalSteps);
void makeVerticalMove(int x, int dir, int sizeY, float board[16][16][3]);
