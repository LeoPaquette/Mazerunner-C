/* mazegen.h
 * This file contains the prototypes for mazegen.c
 * 
 * Leo Paquette 
 * CST8234
 * 041147786
 * 2025-06-30
 */

#ifndef MAZEGEN_H
#define MAZEGEN_H

/* Shuffle of length n. */
void shuffle(int *array, int n);

/* Recursive back‑tracking carve starting at (x,y). */
void carve(char **maze, int rows, int cols, int x, int y);

/* Return random odd column on row that already contains a '.'; −1 if none. */
int findRandomOpening(char **maze, int row, int cols);

#endif
