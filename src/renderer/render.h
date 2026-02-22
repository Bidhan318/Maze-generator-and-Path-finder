#pragma once
#include "raylib.h"
#include "src/maze/maze.h"
#include "src/algorithm/bfs.h"
#include "src/algorithm/dfs.h"
#include <vector>

class Renderer {
public:
    Renderer(int cellSize);

    void drawMaze(const Maze& maze);
    void drawStartEnd(const Maze& maze);
    void drawVisited(const std::vector<Position>& visited, Color color);
    void drawPath(const std::vector<Position>& path);
    void drawUI(SolverState state, const char* algo);

private:
    int cellSize_, offsetX_, offsetY_;

    void computeOffset(const Maze& maze);
    int px(int col) const { return offsetX_ + col * cellSize_; }
    int py(int row) const { return offsetY_ + row * cellSize_; }
};