#include "raylib.h"
#include "maze/maze.h"
#include "renderer/render.h"

int main() {
    const int SCREEN_W  = 900;
    const int SCREEN_H  = 700;
    const int CELL_SIZE = 20;   // pixels per cell
    const int ROWS = 25;   // number of rows
    const int COLS = 35;   // number of cols

    InitWindow(SCREEN_W, SCREEN_H, "Maze Generator");
    SetTargetFPS(60);

    Maze maze(ROWS, COLS);
    Renderer renderer(CELL_SIZE);

    maze.generate();   // generate on startup

    while (!WindowShouldClose()) {

        // R to regenearte maze
        if (IsKeyPressed(KEY_R))
            maze.generate();

        BeginDrawing();
            ClearBackground(BLACK);

            renderer.drawMaze(maze);
            renderer.drawStartEnd(maze);

            DrawText("Press R to regenerate maze", 10, 10, 18, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}