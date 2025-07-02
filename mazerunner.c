/* mazerunner.c
 * This file contains the main logic of the game
 * 
 * Leo Paquette 
 * CST8234
 * 041147786
 * 2025-06-30
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "maze.h"
#include "mazegen.h"
#include "mazeplay.h"

#define MIN_SIZE 10
#define MAX_SIZE 20

/*
 * Main function:
 * Handles the overall game flow for Maze Runner.
 * - Prompts the player for their name and dynamically allocates memory for it.
 * - Runs a game loop that:
 *   - Randomly generates maze dimensions and allocates the maze.
 *   - Initializes the maze with walls and carves paths.
 *   - Finds random valid openings for the maze entrance (top) and exit (bottom).
 *   - Sets the start and exit points in the maze.
 *   - Starts the player movement gameplay until the maze is solved or player quits.
 *   - Tracks and updates the player’s best 3 scores.
 *   - Frees allocated maze memory after each game.
 *   - Asks the player if they want to play again.
 * - At the end, displays the player's top 3 best runs and thanks them.
 * - Frees dynamically allocated player name memory before exiting.
 */
int main(void)
{
    int rows, cols;
    int startY, exitY;
    char **maze;
    int moves;
    int playAgain = 1;
    char input;
    char nameBuffer[100];
    char *playerName;
    int bestScores[3] = {0};
    int i;
    int j;

    /* Seed random number generator with current time */
    srand((unsigned int)time(NULL));

    printf("Welcome to Maze Runner!\n");

    /* Prompt for player name */
    printf("Enter your name: ");

    /* Read player name with fgets */
    if (fgets(nameBuffer, sizeof(nameBuffer), stdin) == NULL)
    {
        fprintf(stderr, "Failed to read name.\n");
        return 1;
    }

    /* Strip newline character from nameBuffer */
    for (i = 0; nameBuffer[i] != '\0'; i++)
    {
        if (nameBuffer[i] == '\n')
        {
            nameBuffer[i] = '\0';
            break;
        }
    }

    /* Allocate memory dynamically for playerName */
    playerName = (char *)malloc(strlen(nameBuffer) + 1);
    if (playerName == NULL)
    {
        fprintf(stderr, "Memory allocation failed for player name.\n");
        return 1;
    }

    /* Copy input name to allocated memory */
    strcpy(playerName, nameBuffer);

    /* Main game loop */
    while (playAgain)
    {
        /* Get random rows between MIN_SIZE and MAX_SIZE */
        rows = (rand() % (MAX_SIZE - MIN_SIZE + 1)) + MIN_SIZE;

        /* Make rows odd if even */
        if (rows % 2 == 0)
            rows++;

        /* Keep rows within max limit */
        if (rows > MAX_SIZE)
            rows = MAX_SIZE - 1;

        /* Get random cols between MIN_SIZE and MAX_SIZE */
        cols = (rand() % (MAX_SIZE - MIN_SIZE + 1)) + MIN_SIZE;

        /* Make cols odd if even */
        if (cols % 2 == 0)
            cols++;

        /* Keep cols within max limit */
        if (cols > MAX_SIZE)
            cols = MAX_SIZE - 1;

        /* Allocate maze memory */
        maze = allocateMaze(rows, cols);
        if (maze == NULL)
        {
            fprintf(stderr, "Memory allocation failed.\n");
            free(playerName);
            return 1;
        }

        /* Initialize maze with walls */
        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < cols; j++)
            {
                maze[i][j] = '#';
            }
        }

        /* Carve paths in maze starting at (1,1) */
        carve(maze, rows, cols, 1, 1);

        /* Find random openings for start (top row) and exit (bottom row) */
        startY = findRandomOpening(maze, 1, cols);
        exitY = findRandomOpening(maze, rows - 2, cols);

        /* Validate openings */
        if (startY == -1 || exitY == -1)
        {
            fprintf(stderr, "Failed to place start or exit.\n");
            freeMaze(maze, rows);
            free(playerName);
            return 1;
        }

        /* Place start and exit markers */
        maze[0][startY] = '*';       /* Start opening */
        maze[1][startY] = '.';       /* Path below start */
        maze[rows - 1][exitY] = 'E'; /* Exit opening */
        maze[rows - 2][exitY] = '.'; /* Path above exit */

        printf("\nMaze Generated. Reach the exit (E).\n");
        printf("Use W/A/S/D to move. Press Q to quit.\n\n");

        /* Start gameplay and get move count */
        moves = playGame(maze, rows, cols, 0, startY, rows - 1, exitY);

        /* Display results and update best scores */
        if (moves > 0)
        {
            printf("Congratulations, %s! You solved the maze in %d moves.\n", playerName, moves);
            updateBestScores(bestScores, moves);
        }
        else
        {
            printf("Game quit before solving the maze.\n");
        }

        /* Free maze memory */
        freeMaze(maze, rows);

        /* Prompt to play again */
        printf("Play again? (y/n): ");
        fflush(stdout);
        input = getchar();

        /* Clear input buffer */
        while (getchar() != '\n')
            ;

        if (input != 'y' && input != 'Y')
        {
            playAgain = 0;
        }
    }

    /* Display top 3 best scores */
    displayTopScores(playerName, bestScores);

    printf("\nThank you for playing Maze Runner, %s!\n", playerName);

    /* Free allocated memory for player name */
    free(playerName);

    return 0;
}