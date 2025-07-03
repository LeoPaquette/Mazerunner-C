# Mazerunner

A console-based maze navigation game written in C.  
This project demonstrates dynamic memory management, recursive maze generation, user input handling, and simple game state tracking.

---

## Game Features

- Randomly generated mazes with variable odd dimensions (10–20 rows and columns)  
- Maze generation using recursive backtracking algorithm  
- Player navigation with WASD controls and quit option (Q)  
- Visual maze display in the console with start, path, walls, player, and exit indicators  
- Tracks and displays the player’s top 3 best completion scores based on moves taken  
- Option to replay with new randomly generated mazes  

---

## Technologies Used

- C programming language (C99 standard)  
- Dynamic memory allocation (`malloc` / `free`)  
- Console I/O (`printf`, `getchar`)  
- Recursive algorithms for maze carving  
- Basic array and pointer manipulation  

---

## File Overview

| File                        | Description                                                   |
|-----------------------------|---------------------------------------------------------------|   
| `mazerunner.c`              | Main program: game flow, user input, replay logic             |
| `maze.c` / `maze.h`         | Maze memory management and display utilities                  |
| `mazegen.c` / `mazegen.h`   | Maze generation via recursive carving and randomization       |
| `mazeplay.c` / `mazeplay.h` | Player movement, input handling, and top scores tracking      |

---

## Compilation

Make sure you have a C compiler (like `gcc`) installed.  
Compile the program using:

```bash
gcc -ansi -pedantic -Wall -Wextra mazerunner.c maze.c mazeplay.c mazegen.c -o mazerunner
```

This command produces an executable named `mazerunner`.

---

## Running the Game

Run the executable from your terminal or command prompt:

```bash
./mazerunner
```

Follow the on-screen prompts to enter your name and play the game. Use the controls below to navigate the maze.

---

## Controls

| Key | Action          |
|------|-----------------|
| W    | Move Up         |
| A    | Move Left       |
| S    | Move Down       |
| D    | Move Right      |
| Q    | Quit the game   |

---

## Example Gameplay

```
Welcome to Maze Runner!
Enter your name: Leo

Maze Generated. Reach the exit (E).
Use W/A/S/D to move. Press Q to quit.

#S#########
#.....#...#
#####.#.#.#
#...#.#.#.#
#.#.#.#.#.#
#.#.#...#.#
#.#######.#
#.....#...#
###.###.###
#...#...#.#
#.###.###.#
#...#.#...#
#.#.#.###.#
#.#...#...#
#.#####.#.#
#.......#.#
###E#######

Move (W/A/S/D): d
...
Congratulations, Leo! You solved the maze in 64 moves.
Play again? (y/n): n

Leo's Top 3 Maze Runs:
  1. 64 moves
  2. ---
  3. ---

Thank you for playing Maze Runner, Leo!
```

---

## How It Works

- The program prompts the player to enter their name.  
- It generates a maze with random odd dimensions between 10 and 20.  
- The maze is initialized with walls (`#`) and paths carved recursively (`.`).  
- Random openings on the top and bottom rows serve as the start (`S`) and exit (`E`) points.  
- The player moves through the maze using WASD keys; invalid moves into walls or outside bounds are blocked.  
- The path traveled is marked (`X` for current position, `*` for previously visited path).  
- The game ends when the player reaches the exit or quits by pressing Q.  
- The player's moves count is recorded, and top 3 scores are tracked and displayed.  
- Players may replay to try to improve their scores.  

---

## Notes

- Maze dimensions are always odd to ensure proper maze structure and carving.  
- The maze uses dynamic memory allocation; all allocated memory is freed after each game.  
- The maze is displayed in the console using ASCII characters:  
  - `#` = wall  
  - `.` = path  
  - `S` = start position  
  - `E` = exit position  
  - `X` = current player position  
  - `*` = player’s previous positions  
- The game only supports console input and output.  

---

## About Me

*Leo Paquette*  
*Computer Engineering Technology – Computing Science*  
*041147786*  
*paqu0450@algonquinlive.com*
