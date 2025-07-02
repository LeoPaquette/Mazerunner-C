/* maze.h
 * This file contains the prototypes for maze.c
 * 
 * Leo Paquette 
 * CST8234
 * 041147786
 * 2025-06-30
 */

#ifndef MAZE_H
#define MAZE_H


/* Allocate rows × cols characters; return NULL if malloc fails. */
char **allocateMaze(int rows, int cols);

/* Free every row plus the pointer returned by allocateMaze(). */
void freeMaze(char **maze, int rows);

/* Print the maze grid to stdout. */
void printMaze(char **maze, int rows, int cols);

/* Return 1 if (x,y) lies inside the grid, 0 otherwise. */
int inBounds(int x, int y, int rows, int cols);

#endif
