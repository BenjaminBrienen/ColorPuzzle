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

int sizeX = 16;
int sizeY = 16;
float board[16][16][3] = { 0 };

int scrambleSteps = 100;
float color1[3] = { 1, 0, 0 }; //bottom left
float color2[3] = { 0, 1, 0 }; //botom right
float color3[3] = { 0, 0, 1 }; //top left
float color4[3] = { 1, 1, 1 }; //top right

int main(int argc, char **argv)
{

	printf("Initializing board with colors...\n");
	fflush(stdout);
	initBoard(sizeX, sizeY, board, color1, color2, color3, color4);
	printf("Scrambling board...\n");
	fflush(stdout);
	scrambleBoard(sizeX, sizeY, board, scrambleSteps);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("square");

	glClearColor(0.0, 0.0, 0.0, 0.0);         // black background 
	glMatrixMode(GL_PROJECTION);              // setup viewing projection 
	glLoadIdentity();                           // start with identity matrix 
	gluOrtho2D(0.0, 10.0, 0.0, 10.0, -1, 1);   // setup a 10x10x2 viewing world
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}

void game()
{
	displayBoard(sizeX, sizeY, board);
	printf("Done\n");
	fflush(stdout);
}

void display()
{
	game();
	glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
	printf("%c", key);
	switch (key)
	{
	case 'w':
		makeVerticalMove(2, 1, sizeY, board);
		break;
	case 's':
		makeVerticalMove(2, -1, sizeY, board);
		break;
	case 'a':
		makeHorizontalMove(2, -1, sizeX, board);
		break;
	case 'd':
		makeHorizontalMove(2, 1, sizeX, board);
		break;

	default:
		break;
	}
	glutPostRedisplay(); /* this redraws the scene without
							waiting for the display callback
							so that any changes appear instantly */
}