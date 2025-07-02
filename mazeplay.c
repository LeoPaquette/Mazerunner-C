/* mazeplay.c
 * This file contains the functions that allow the user to interact with the maze
 * 
 * Leo Paquette 
 * CST8234
 * 041147786
 * 2025-06-30
 */

#include <stdio.h>
#include <ctype.h>
#include "mazeplay.h"
#include "maze.h" 
/*
 * Main gameplay loop: lets player move through the maze until exit or quit.
 */
int playGame(char **maze, int rows, int cols, int startX, int startY, int exitX, int exitY)
{
    int playerX = startX;
    int playerY = startY;
    int moves = 0;
    char input;
    int newX, newY;

    maze[playerX][playerY] = 'S';  /* Mark start position */

    while (1)
    {
        printMaze(maze, rows, cols);  /* Show current maze */
        printf("\nMove (W/A/S/D): ");
        fflush(stdout);

        input = getchar();
        while (getchar() != '\n');  /* Clear input buffer */

        input = (char)tolower(input);  /* Normalize input */

        if (input == 'q')  /* Quit command */
            return 0;

        newX = playerX;
        newY = playerY;

        /* Determine new position based on input */
        switch (input)
        {
        case 'w':
            newX = playerX - 1;
            break;
        case 'a':
            newY = playerY - 1;
            break;
        case 's':
            newX = playerX + 1;
            break;
        case 'd':
            newY = playerY + 1;
            break;
        default:
            printf("\nInvalid input! Use W/A/S/D or Q to quit.\n");
            continue;
        }

        /* Check for walls or out-of-bounds */
        if (!inBounds(newX, newY, rows, cols) || maze[newX][newY] == '#')
        {
            printf("\nYou walked into a wall!\n\n");
            continue;
        }

        /* Mark previous position as path (unless start) */
        if (!(playerX == startX && playerY == startY))
            maze[playerX][playerY] = '*';

        playerX = newX;
        playerY = newY;
        moves++;

        /* Check if reached exit */
        if (playerX == exitX && playerY == exitY)
        {
            maze[playerX][playerY] = 'E';  /* Mark exit */
            printMaze(maze, rows, cols);
            break;
        }

        /* Mark current player position (unless start) */
        if (!(playerX == startX && playerY == startY))
            maze[playerX][playerY] = 'X';
    }

    return moves;
}

/*
 * Update the bestScores array with newScore if it is a top 3 score.
 */
void updateBestScores(int bestScores[], int newScore)
{
    int i, j;

    if (newScore == 0)
        return;

    for (i = 0; i < 3; i++)
    {
        if (bestScores[i] == 0 || newScore < bestScores[i])
        {
            /* Shift lower scores down */
            for (j = 2; j > i; j--)
                bestScores[j] = bestScores[j - 1];
            bestScores[i] = newScore;  /* Insert new top score */
            break;
        }
    }
}

/*
 * Display the top 3 scores for the player.
 */
void displayTopScores(const char *playerName, int bestScores[])
{
    int i;
    printf("\n%s's Top 3 Maze Runs:\n", playerName);
    for (i = 0; i < 3; i++)
    {
        if (bestScores[i] > 0)
            printf("  %d. %d moves\n", i + 1, bestScores[i]);
        else
            printf("  %d. ---\n", i + 1);
    }
}