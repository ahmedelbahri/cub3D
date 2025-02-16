# cub3d

**cub3d** is a project that implements a 3D game engine in C, simulating a raycasting engine. The goal is to create a simple 3D rendering engine using raycasting, allowing the user to navigate a maze-like environment. The project includes the full set of features with a **125% bonus**, adding extra visual and functional elements to the game.

---

## About

**cub3d** is based on the raycasting technique used in early 3D games to simulate a 3D environment from a 2D map. The engine allows for navigation within the environment, simulating a first-person perspective. The project focuses on rendering walls, floors, and ceilings, as well as implementing basic user movement and camera control.

### Core Requirements:
- Implement a raycasting engine to render a 3D environment from a 2D map.
- Handle user input for moving and rotating the camera.
- Draw walls, floors, and ceilings.
- Use a basic map format to define the environment.
- Implement the game loop with real-time rendering.

---

## Installation

To install **cub3d**, follow these steps:

1. Clone this repository:
    ```bash
    git clone https://github.com/ahmedelbahri/cub3d.git
    cd cub3d
    ```

2. Compile the project:
    ```bash
    make
    ```

3. Optionally, to remove all compiled objects:
    ```bash
    make clean
    ```

4. To remove the executable:
    ```bash
    make fclean
    ```

5. To recompile the project after cleaning:
    ```bash
    make re
    ```

---

## Usage

To run **cub3d**, execute the program with the path to a valid `.cub` map file:

```bash
./cub3d map.cub
