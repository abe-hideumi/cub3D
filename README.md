_This project has been created as part of the 42 curriculum by knomura, habe._

## Description

cub3D is a 3D raycasting engine built from scratch in C using the Minilibx library.

This project reads a custom .cub file which defines wall textures per direction (N,S,E,W) and floor/ceiling colors and the map.
then renders the scene in real time using the DDA (Digital Differential Analysis) raycasting algorithm. The player can move and rotate freely within the walled maze.

## Instructions

### Requirements

- GCC or Clang compiler
- GNU Make
- MinilibX (must be downloaded separately and placed in the project root)

### Compilation

```bash
make
```

### Execution

```bash
./cub3D map/valid.cub
```

Pass any `.cub` file as the argument. The file must define wall textures (NO/SO/WE/EA), floor and ceiling colors (F/C), and a valid map.

### Controls

| Key | Action |
|-----|--------|
| W / A / S / D | Move forward / left / backward / right |
| ← / → | Rotate camera left / right |
| ESC | Quit |

## Resources

### References

Lode's Computer Graphics Tutorial - Raycasting: https://lodev.org/cgtutor/raycasting.html
cub3D解説スライド: https://docs.google.com/presentation/d/1dQrnEUmDkodlIC366O_YdLbO2-MBsuzEkgC8F2xjxOY/edit?slide=id.p#slide=id.p
fabs(3) - Linux man page: https://ja.manpages.org/fabs/3
複素数の概念と三角関数 - 金沢工業大学: https://w3e.kanazawa-it.ac.jp/math/category/kika/heimenkika/henkan-tex.cgi?target=/math/category/kika/heimenkika/souzi.html



### AI Usage

AI tools (ChatGPT, Gemini, Claude Code) were used to:

- understand the DDA raycasting algorithm and how to apply it to 2D map grids
- clarify MinilibX library functions (image creation, pixel writing, event hooks)
- understand trigonometric calculations for player movement and camera rotation
- review `.cub` file parsing logic and edge case handling
- debug rendering artifacts and texture mapping issues

All final implementation choices and code were written and validated by the authors.
