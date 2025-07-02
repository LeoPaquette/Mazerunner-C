/* mazeplay.h
 * This file contains the prototypes for mazeplay.h
 * 
 * Leo Paquette 
 * CST8234
 * 041147786
 * 2025-06-30
 */

#ifndef MAZEPLAY_H
#define MAZEPLAY_H

/* WASD game loop; returns moves taken (0 if player quits). */
int playGame(char **maze, int rows, int cols, int startX, int startY, int exitX, int exitY);

/* Insert newScore into bestScores[3] if it beats an existing entry. */
void updateBestScores(int bestScores[], int newScore);

/* Print the three best scores for a player. */
void displayTopScores(const char *playerName, int bestScores[]);

#endif
