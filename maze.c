/* maze.c
 * This file contains the utility functions that assist in creating and displaying the maze
 * 
 * Leo Paquette 
 * CST8234
 * 041147786
 * 2025-06-30
 */

#include <stdlib.h>
#include <stdio.h>
#include "maze.h"
/*
 * Allocate memory for the maze:
 * Creates a 2D array of characters with specified rows and columns.
 * Returns pointer to the array or NULL on failure.
 */
char **allocateMaze(int rows, int cols)
{
    int i;
    /* Allocate array of pointers for rows */
    char **maze = (char **)malloc(rows * sizeof(*maze));
    if (maze == NULL)
        return NULL;

    for (i = 0; i < rows; i++)
    {
        /* Allocate each row */
        maze[i] = (char *)malloc(cols * sizeof(char));
        if (maze[i] == NULL)
        {
            int j;
            /* Free all previously allocated rows on failure */
            for (j = 0; j < i; j++)
                free(maze[j]);
            free(maze);
            return NULL;
        }
    }
    return maze;
}

/*
 * Free memory allocated for the maze:
 * Frees each row and then the pointer array itself.
 */
void freeMaze(char **maze, int rows)
{
    int i;
    /* Free each row */
    for (i = 0; i < rows; i++)
        free(maze[i]);
    /* Free the row pointers */
    free(maze);
}

/*
 * Print the maze to the console:
 * Prints each character in the maze row by row.
 */
void printMaze(char **maze, int rows, int cols)
{
    int i;
    int j;

    /* Print each row */
    for (i = 0; i < rows; i++)
    {
        /* Print each column */
        for (j = 0; j < cols; j++)
            putchar(maze[i][j]);
        putchar('\n'); /* Newline after each row */
    }
}

/*
 * Check if coordinates (x,y) are within maze bounds:
 * Returns 1 (true) if in bounds, 0 otherwise.
 */
int inBounds(int x, int y, int rows, int cols)
{
    /* Return 1 if x,y are inside maze boundaries */
    return (x >= 0 && y >= 0 && x < rows && y < cols);
}
