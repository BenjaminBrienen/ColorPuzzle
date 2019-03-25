// OpenGLSquares.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "Rendering.h"
#include "game.h"

void display();
void displayRandSquares();
void keyboard(unsigned char key, int x, int y);
void click(int button, int state, int x, int y);

float board[size][size][3] = { 0 };
float boardSolved[size][size][3] = { 0 };

int scrambleSteps = size;
float color1[3] = { 1, 0, 0 }; //bottom left
float color2[3] = { 0, 1, 0 }; //botom right
float color3[3] = { 0, 0, 1 }; //top left
float color4[3] = { 1, 1, 1 }; //top right
int selectedX = 1;
int selectedY = 1;
int moves = 0;


int main(int argc, char **argv)
{
	initBoard(board, color1, color2, color3, color4);
	initBoard(boardSolved, color1, color2, color3, color4);
	scrambleBoard(board, scrambleSteps);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(XRES, YRES);
	glutCreateWindow("square");

	glClearColor(0.0, 0.0, 0.0, 0.0);         // black background 
	glMatrixMode(GL_PROJECTION);              // setup viewing projection 
	glLoadIdentity();                           // start with identity matrix 
	gluOrtho2D(0.0, XRES, 0.0, YRES, -1, 1);   // setup a sizexsizex2 viewing world
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMouseFunc(click);
	glutMainLoop();

	return 0;
}

void game()
{
	displayBoard(board);
}

void display()
{
	game();
	//drawCursor(1, 1, 1, 10);

	glFlush();
}

int selectMode = 0; //0 is none, 1 is x mode, 2 is y mode
void keyboard(unsigned char key, int x, int y)
{
	moves++;

	if (selectedX == size - 1)
	{
		selectedX = 1;
	}
	if (selectedX == 0)
	{
		selectedX = size - 2;
	}
	if (selectedY == size - 1)
	{
		selectedY = 1;
	}
	if (selectedY == 0)
	{
		selectedY = size - 2;
	}
	switch (key)
	{
		case 'w':
			makeVerticalMove(selectedY, 1, board);
			selectedX++;
			break;
		case 's':
			makeVerticalMove(selectedY, -1, board);
			selectedX--;
			break;
		case 'a':
			makeHorizontalMove(selectedX, -1, board);
			selectedY--;
			break;
		case 'd':
			makeHorizontalMove(selectedX, 1, board);
			selectedY++;
			break;
		case 'x':
			selectMode = 2;
			break;
		case 'y':
			selectMode = 1;
			break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		//case '9':
		//case '0':
			if (selectMode == 1)
			{
				selectedX = key - '0';
			}
			if (selectMode == 2)
			{
				selectedY = key - '0';
			}
			selectMode = 0;
			break;
		default:
			break;
	}
	if (checkBoard(board, boardSolved))
	{
		printf("You win!\nYour score is: %d (lower is better)", moves);
	}
	glutPostRedisplay(); /* this redraws the scene without
							waiting for the display callback
							so that any changes appear instantly */
	
}

void click(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("x: %d, y: %d\n", x, y);
		selectedX = size - 1 - (y * size / YRES);
		selectedY = x *size / XRES;
	}
}