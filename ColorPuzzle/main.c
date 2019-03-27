// OpenGLSquares.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <GL/glut.h>
#include "Rendering.h"
#include "game.h"
#include <GL/freeglut.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void display();
void keyboard(unsigned char key, int x, int y);
void click(int button, int state, int x, int y);
void assignColors(float color1[3], float color2[3], float color3[3], float color4[3]);
void createGame(float *** board, int sizeX, int sizeY, float *** boardSolved, float color1[3], float color2[3], float color3[3], float color4[3]);
void createGLUTWindow(int argc, char **argv);
void displayInstructions();
int compareColors(float color1[3], float color2[3]);

int scrambleSteps = 0;
float color1[3] = { 0 }; //bottom left
float color2[3] = { 0 }; //botom right
float color3[3] = { 0 }; //top left
float color4[3] = { 0 }; //top right
int selectedX = 1;
int selectedY = 1;
int moves = 0;

int quit = 0;

int sizeX = 10;
int sizeY = 10;

float *** board;
float *** boardSolved;

int main(int argc, char **argv)
{
	scrambleSteps = 25 * (sizeX*sizeY);
	board = malloc(sizeX * sizeY * 3 * sizeof(float**));
	boardSolved = malloc(sizeX * sizeY * 3 * sizeof(float));
	displayInstructions();
	srand((unsigned int)time(0));
	createGLUTWindow(argc, argv);
	createGame(board, sizeX, sizeY, boardSolved, color1, color2, color3, color4);
	display();
	glutMainLoop();

	return 1;
}

void createGLUTWindow(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(XRES, YRES);
	glutCreateWindow("Color Puzzle");

	glClearColor(0.0, 0.0, 0.0, 0.0);         // black background 
	glMatrixMode(GL_PROJECTION);              // setup viewing projection 
	glLoadIdentity();                           // start with identity matrix 
	gluOrtho2D(0.0, XRES, 0.0, YRES);   // setup a sizexsizex2 viewing world
	glutKeyboardFunc(keyboard, sizeX, sizeY);
	glutDisplayFunc(display);
	glutMouseFunc(click);
}

void game()
{
	displayBoard(board, sizeX, sizeY);
}

void display()
{
	if (quit)
	{
		glutLeaveMainLoop();
	}
	game();
	//drawCursor(1, 1, 1, 10);

	glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
	moves++;

	if (selectedY == sizeY - 1)
	{
		selectedY = 1;
	}
	if (selectedY == 0)
	{
		selectedY = sizeY - 2;
	}
	if (selectedX == sizeX - 1)
	{
		selectedX = 1;
	}
	if (selectedX == 0)
	{
		selectedX = sizeX - 2;
	}
	switch (key)
	{
		case 'w':
			makeVerticalMove(selectedX, 1, board, sizeX, sizeY);
			selectedY++;
			break;
		case 's':
			makeVerticalMove(selectedX, -1, board, sizeX, sizeY);
			selectedY--;
			break;
		case 'a':
			makeHorizontalMove(selectedY, -1, board, sizeX, sizeY);
			selectedX--;
			break;
		case 'd':
			makeHorizontalMove(selectedY, 1, board, sizeX, sizeY);
			selectedX++;
			break;
		case 'r':
			moves = 0;
			createGame(board, sizeX, sizeY, boardSolved, color1, color2, color3, color4);
			printf("Press enter to scramble board...\n");
			break;
		case 'e':
			free(board, sizeX, sizeY);
			free(boardSolved);
			quit = 1;
			break;
		case 13:
			moves = 0;
			scrambleBoard(board, sizeX, sizeY, scrambleSteps);
			break;
		default:
			break;
	}
	if (checkBoard(board, sizeX, sizeY, boardSolved) && key != 'r')
	{
		printf("You win!\nYou took %d moves.", moves);
	}
	glutPostRedisplay(); /* this redraws the scene without
							waiting for the display callback
							so that any changes appear instantly */

}

void click(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		selectedY = sizeY - 1 - (y * sizeY / glutGet(GLUT_WINDOW_HEIGHT));
		selectedX = x * sizeX / glutGet(GLUT_WINDOW_WIDTH);
	}
}

void assignColors(float color1[3], float color2[3], float color3[3], float color4[3])
{
	/*color1[0] = 1;
	color1[1] = 1;
	color1[2] = 1;
	color2[0] = 1;
	color2[1] = 1;
	color2[2] = 1;
	color3[0] = 1;
	color3[1] = 1;
	color3[2] = 1;
	color4[0] = 0;
	color4[1] = 0;
	color4[2] = 0;
*/
	color1[0] = (float)(rand() % 2);
	color1[1] = (float)(rand() % 2);
	color1[2] = (float)(rand() % 2);
	color2[0] = (float)(rand() % 2);
	color2[1] = (float)(rand() % 2);
	color2[2] = (float)(rand() % 2);
	color3[0] = (float)(rand() % 2);
	color3[1] = (float)(rand() % 2);
	color3[2] = (float)(rand() % 2);
	color4[0] = (float)(rand() % 2);
	color4[1] = (float)(rand() % 2);
	color4[2] = (float)(rand() % 2);

	if (compareColors(color1, color2) || compareColors(color1, color3) || compareColors(color1, color4))
	{
		assignColors(color1, color2, color3, color4);
	}
	if (compareColors(color2, color3) || compareColors(color2, color4))
	{
		assignColors(color1, color2, color3, color4);
	}
	if (compareColors(color3, color4))
	{
		assignColors(color1, color2, color3, color4);
	}

}

void createGame(float *** board, int sizeX, int sizeY, float *** boardSolved, float color1[3], float color2[3], float color3[3], float color4[3])
{
	assignColors(color1, color2, color3, color4);

	initBoard(board, sizeX, sizeY, color1, color2, color3, color4);
	initBoard(boardSolved, sizeX, sizeY, color1, color2, color3, color4);
}

int compareColors(float color1[3], float color2[3])
{
	if (color1[0] == color2[0] && color1[1] == color2[1] && color1[2] == color2[2])
		return 1;
	return 0;
}

void displayInstructions()
{
	printf("Hello, welcome to Color Puzzle. This is a 2D rubik's cube-esque puzzle game based on organizing colors.\n");
	printf("The goal of the game is to unscramble the colors by organizing them into the correct location.\n");
	printf("The controls are:\n");
	printf("Click a colored tile to control it.\n");
	printf("Use WASD to make it move up, left, down, and right\n");
	printf("Press 'r' to restart with a new board.\n");
	printf("The colors will wrap around to the other side of the board. However, the edge colors stay in place for reference.\n");
	printf("The game will end when you completely organize all the colors.");
	printf("The console will say when you have won.\n");
	printf("Press 'e' to exit.\n");
	printf("Press enter to scramble board at any time.");
}