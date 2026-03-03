*This project has been created as part of the 42 curriculum by caide-so, marcudos.*

---

# cub3D — My First RayCaster with miniLibX

---

## Description

**cub3D** is a first-person 3D maze exploration engine written in C, inspired by the legendary **Wolfenstein 3D** (Id Software, 1992) — considered the first true First Person Shooter in the history of video games.

The project is built on **ray-casting**, a rendering technique that simulates a 3D perspective by casting rays from the player's viewpoint into a 2D map and computing the distance to walls. This creates the illusion of 3D space without actually working in three dimensions.

### What the project does

- Renders a navigable 3D maze from a first-person perspective in real time
- Parses a `.cub` scene description file that defines textures, colors, and the map layout
- Applies distinct XPM wall textures depending on which cardinal direction a wall faces (N, S, E, W)
- Supports configurable floor and ceiling colors (RGB)
- Handles smooth window management, keyboard input, and clean exit

### Bonus features implemented

- **Minimap system** — a top-down overlay showing the map, FOV cone, and player position (hold TAB for full-screen view)
- **Animated sprites** — zombie sprites placed on the map cycle through animation frames
- **Doors** — interactive doors (`D` on the map) that open and close with the spacebar
- **Mouse rotation** — rotate the player's view by moving the mouse (bonus binary)
- **Wall collision** — the player cannot walk through walls or closed doors

---

## Project Structure

```
cub3D/
├── include/          # Header files (structs, macros, keys, colors)
├── lib/
│   ├── libft/        # Custom C library
│   └── minilibx-linux/  # MiniLibX graphics library
├── maps/             # .cub map files (good/ and bad/ for testing)
├── src/
│   ├── debug/        # Config printing utilities
│   ├── error/        # Error message handling
│   ├── free/         # Memory cleanup functions
│   ├── init/         # Game and config initialization
│   ├── map/          # Map validation (flood fill, char check)
│   ├── minimap/      # Minimap rendering (grid, player, FOV, Bresenham)
│   ├── move/         # Player movement, rotation, door interaction
│   ├── parse/        # .cub file parsing (textures, colors, map)
│   ├── render/       # Raycasting, wall drawing, texture mapping
│   └── sprite/       # Animated sprite loading and rendering
├── sprites/          # XPM sprite frames (zombie1–4)
├── textures/         # XPM wall and door textures
├── Makefile
└── README.md
```

---

## Instructions

### Requirements

- **OS:** Linux (tested on Ubuntu)
- **Dependencies:** `gcc`, `make`, `libX11`, `libXext`

Install dependencies on Ubuntu/Debian:
```bash
sudo apt-get install gcc make libx11-dev libxext-dev
```

### Compilation

```bash
# Build the mandatory binary
make

# Build the bonus binary (mouse look + bonus features)
make bonus

# Clean object files
make clean

# Full clean (objects + binaries)
make fclean

# Rebuild from scratch
make re
```

### Running

```bash
# Mandatory binary
./cub3D maps/good/.cub

# Bonus binary (adds mouse look)
./cub3D_bonus maps/good/.cub
```

### Map file format (`.cub`)

A valid scene file must contain, in any order before the map:

```
NO ./textures/north_wall.xpm   # North wall texture path
SO ./textures/south_wall.xpm   # South wall texture path
WE ./textures/west_wall.xpm    # West wall texture path
EA ./textures/east_wall.xpm    # East wall texture path
F 220,100,0                    # Floor color (R,G,B)
C 225,30,0                     # Ceiling color (R,G,B)
```

The map must be the last element in the file. Valid map characters:

| Character | Meaning |
|-----------|---------|
| `0` | Empty floor tile |
| `1` | Wall |
| `N` / `S` / `E` / `W` | Player start position and facing direction |
| `D` | Closed door (bonus) |
| `d` | Open door (bonus) |
| `C` | Sprite spawn point (bonus) |

The map must be fully enclosed by walls. Any open edge will cause an error.

### Controls

| Key | Action |
|-----|--------|
| `W` / `A` / `S` / `D` | Move forward / strafe left / move backward / strafe right |
| `←` / `→` | Rotate view left / right |
| `SHIFT` | Sprint (2× speed) |
| `CTRL` | Walk slowly (0.5× speed) |
| `SPACE` | Interact with door (open/close) |
| `TAB` | Toggle fullscreen minimap |
| `ESC` | Quit the program |
| `Mouse` | Rotate view (bonus binary only) |

### Error handling

If the `.cub` file is misconfigured, the program exits with:
```
Error
<explicit error message>
```

---

## Technical Highlights

### Ray-Casting

Each frame, a ray is cast for every screen column using the **DDA (Digital Differential Analyzer)** algorithm. The perpendicular wall distance determines the height of the wall slice drawn on screen, producing a correct perspective projection without fisheye distortion.

### Texture Mapping

Wall textures are sampled column-by-column. The horizontal hit position on the wall tile determines the X coordinate in the texture. A vertical step is calculated based on the projected wall height, allowing the texture to be scaled proportionally.

### Sprite Rendering

Sprites are transformed into camera space using an inverse determinant calculation. They are depth-sorted against the Z-buffer populated during wall rendering, so walls correctly occlude sprites that are behind them.

### Minimap

The minimap blends semi-transparent colored tiles over the rendered scene. The FOV cone is drawn using NUM_RAYS mini-raycasts with Bresenham line drawing. In TAB mode, the map is centered and scaled to fill the screen.

---

## Resources

### Ray-casting fundamentals
- [Lode's Computer Graphics Tutorial — Raycasting](https://lodev.org/cgtutor/raycasting.html) — The primary reference for DDA, texture mapping, and sprite rendering
- [Permadi's Ray-Casting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/) — Classic in-depth ray-casting walkthrough
- [Game Engine Black Book: Wolfenstein 3D by Fabien Sanglard](https://fabiensanglard.net/gebbwolf3d/) — Deep technical dive into the original game

### miniLibX
- [miniLibX documentation (42 campus)](https://harm-smits.github.io/42docs/libs/minilibx) — MiniLibX functions and event handling reference

### Mathematics
- [Bresenham's line algorithm — Wikipedia](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
- [Digital differential analyzer — Wikipedia](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))

---

### AI usage

AI tools (Claude) were used in the following ways during this project:

- **Struct and header design** — Getting suggestions on how to organize data structures (`t_ray`, `t_sprite_calc`, etc.) before implementation, then reviewing and adapting the proposals to fit the project's specific needs
- **Debugging** — Describing unexpected rendering artifacts (e.g., fisheye distortion, texture misalignment) and using AI explanations to understand the underlying mathematical cause
- **Documentation** — Generating inline comment drafts for complex functions (DDA loop, sprite transform), which were then reviewed, corrected, and rewritten to reflect actual behavior
- **README drafting** — Initial structure and wording for this README was AI-assisted, then manually reviewed and adapted to match the actual codebase

In all cases, AI-generated content was critically reviewed, tested, and understood before being used. No code was copied without full comprehension of its logic.
