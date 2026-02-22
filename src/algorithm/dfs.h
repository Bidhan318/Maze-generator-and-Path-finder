#pragma once
#include "src/maze/maze.h"
#include "src/algorithm/bfs.h"  // reuse Position and SolverState
#include <vector>
#include <stack>
#include <map>

class DFSSolver {
public:
    DFSSolver();

    void        init(Maze& maze);
    SolverState step(Maze& maze);
    SolverState getState() const { return state_; }

    const std::vector<Position>& getVisited() const { return visited_; }
    const std::vector<Position>& getPath()    const { return path_;    }

private:
    SolverState              state_;
    std::stack<Position>     stack_;
    std::map<Position,Position> parent_;
    std::vector<Position>    visited_;
    std::vector<Position>    path_;

    void reconstructPath(const Position& end);
};