_This project has been created as part of the 42 curriculum by knomura, habe._

## Description

cub3D is a 3D raycasting engine built from scratch in C using the Minilibx library.

This project reads a custom .cub file which defines wall textures per direction (N,S,E,W) and floor/ceiling colors and the map.
then renders the scene in real time using the DDA (Digital Differential Analysis) raycasting algorithm. The player can move and rotate freely within the walled maze.

## Instructions

### Compilation

To compile and run this project, you need:

- A Unix-based operating system (Linux or macOS)
- GCC or Clang compiler
- GNU Make
- GNU Readline library

Compile the project using:

- make

### Execution

./cub3D `PATH_TO_CUBFILE`

## Resources

### References


### AI Usage

AI tools (ChatGPT, Gemini, Claude Code) were used to:

- clarify Bash behavior and edge cases
- understand Unix system calls such as `fork`, `execve`, `pipe`, `dup2` and related functions.
- review logic and suggest improvements in parsing strategies

All final implementation choices and code were written and validated by the authors.
