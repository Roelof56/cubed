🎮 cub3D
Description
cub3D is a simple 3D game engine written in C using raycasting to render a first-person view from a 2D map.

Requirements
Linux or macOS
cc
make
MLX42
X11 libraries (Linux) or macOS graphical dependencies
Build
make
Run
./cub3d examplemap.cub
# There are currently 3 map files included here to test: map0.cub, map1.cub, map2.cub
Controls
W, A, S, D — Move player
← / → OR Mouse input — Rotate camera
ESC — Exit the game
Clean
make clean      # removes object files
make fclean     # removes object files and executable
make re         # rebuilds the project
