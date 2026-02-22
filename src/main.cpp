#include "raylib.h"
#include "src/maze/maze.h"
#include "src/renderer/render.h"
#include "src/algorithm/bfs.h"

int main() {
    const int SCREEN_W = 900;
    const int SCREEN_H = 700;
    const int CELL_SIZE = 20;
    const int ROWS = 25;
    const int COLS = 35;
    const int STEPS_PER_FRAME = 3;

    InitWindow(SCREEN_W, SCREEN_H, "Maze Pathfinder - BFS");
    SetTargetFPS(60);

    Maze maze(ROWS, COLS);
    Renderer  renderer(CELL_SIZE);
    BFSSolver bfs;
    DFSSolver dfs;

    // Which solver is active: 0 = none, 1 = BFS, 2 = DFS
    int active = 0;

    maze.generate();

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_R)) {
            maze.generate();
            bfs = BFSSolver();
            dfs = DFSSolver();
            active = 0;
        }

        if (IsKeyPressed(KEY_ONE))  { bfs.init(maze); dfs = DFSSolver(); active = 1; }
        if (IsKeyPressed(KEY_TWO))  { dfs.init(maze); bfs = BFSSolver(); active = 2; }

        // Step the active solver
        SolverState state = SolverState::IDLE;
        if (active == 1 && bfs.getState() == SolverState::SEARCHING)
            for (int i = 0; i < STEPS_PER_FRAME; ++i) { bfs.step(maze); if (bfs.getState() != SolverState::SEARCHING) break; }
        if (active == 2 && dfs.getState() == SolverState::SEARCHING)
            for (int i = 0; i < STEPS_PER_FRAME; ++i) { dfs.step(maze); if (dfs.getState() != SolverState::SEARCHING) break; }

        if      (active == 1) state = bfs.getState();
        else if (active == 2) state = dfs.getState();

        // BFS = blue, DFS = orange
        Color visitColor = (active == 2) ? Color{220, 120, 30, 160} : Color{50, 130, 200, 160};

        BeginDrawing();
            ClearBackground(BLACK);

            if (active == 1) renderer.drawVisited(bfs.getVisited(), visitColor);
            if (active == 2) renderer.drawVisited(dfs.getVisited(), visitColor);

            if (state == SolverState::DONE) {
                if (active == 1) renderer.drawPath(bfs.getPath());
                if (active == 2) renderer.drawPath(dfs.getPath());
            }

            renderer.drawMaze(maze);
            renderer.drawStartEnd(maze);
            renderer.drawUI(state, active == 2 ? "DFS" : "BFS");
        EndDrawing();
    }

    CloseWindow();
    return 0;
}