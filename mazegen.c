/* mazegen.c
 * This file contains the functions that generate the maze itself
 * 
 * Leo Paquette 
 * CST8234
 * 041147786
 * 2025-06-30
 */

#include <stdlib.h>
#include "mazegen.h"
/*
 * Shuffle an integer array randomly using Fisher-Yates algorithm.
 */
void shuffle(int *array, int n)
{
    int i, j, temp;
    for (i = n - 1; i > 0; i--)
    {
        j = rand() % (i + 1);  /* Pick random index */
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

/*
 * Recursively carve out paths in the maze starting at (x,y).
 */
void carve(char **maze, int rows, int cols, int x, int y)
{
    int dirs[4] = {0, 1, 2, 3};  /* Directions */
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    int i;

    maze[x][y] = '.';  /* Mark current cell as path */

    shuffle(dirs, 4);  /* Randomize directions */

    for (i = 0; i < 4; i++)
    {
        int dir = dirs[i];
        int nx = x + 2 * dx[dir];
        int ny = y + 2 * dy[dir];

        /* Check boundaries and if cell is wall */
        if (nx > 0 && ny > 0 && nx < rows - 1 && ny < cols - 1 &&
            maze[nx][ny] == '#')
        {
            maze[x + dx[dir]][y + dy[dir]] = '.';  /* Carve intermediate */
            maze[nx][ny] = '.';                     /* Carve next cell */
            carve(maze, rows, cols, nx, ny);       /* Recurse */
        }
    }
}

/*
 * Find a random opening (path cell) in a given row.
 * Returns column index or -1 if none found.
 */
int findRandomOpening(char **maze, int row, int cols)
{
    int y;
    int attempts = 100;

    while (attempts--)
    {
        y = 1 + 2 * (rand() % ((cols - 2) / 2));  /* Pick random odd col */
        if (maze[row][y] == '.')                   /* Is it path? */
        {
            return y;
        }
    }
    return -1;  /* No opening found */
}