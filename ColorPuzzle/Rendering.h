#pragma once

#define XRES 1000
#define YRES 1000
#include "game.h"

void displayRect(float x, float y, float w, float h, float red, float green, float blue);
void displayBoard(float *** board, int sizeX, int sizeY);