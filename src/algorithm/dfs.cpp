#include "src/algorithm/dfs.h"
#include <algorithm>

DFSSolver::DFSSolver() : state_(SolverState::IDLE) {}

void DFSSolver::init(Maze& maze) {
    while (!stack_.empty()) stack_.pop();
    parent_.clear();
    visited_.clear();
    path_.clear();

    maze.resetVisited();

    Position start = { maze.startRow, maze.startCol };
    stack_.push(start);
    parent_[start] = { -1, -1 };

    state_ = SolverState::SEARCHING;
}

SolverState DFSSolver::step(Maze& maze) {
    if (state_ != SolverState::SEARCHING) return state_;

    if (stack_.empty()) {
        state_ = SolverState::NO_PATH;
        return state_;
    }

    Position cur = stack_.top(); stack_.pop();
    int r = cur.first, c = cur.second;

    if (maze.getCell(r, c).visited) return state_;
    maze.getCell(r, c).visited = true;
    visited_.push_back(cur);

    Position end = { maze.endRow, maze.endCol };
    if (cur == end) {
        reconstructPath(end);
        state_ = SolverState::DONE;
        return state_;
    }

    Cell& cell = maze.getCell(r, c);

    if (!cell.wallTop    && !maze.getCell(r-1, c).visited) { Position nb={r-1,c}; parent_[nb]=cur; stack_.push(nb); }
    if (!cell.wallBottom && !maze.getCell(r+1, c).visited) { Position nb={r+1,c}; parent_[nb]=cur; stack_.push(nb); }
    if (!cell.wallLeft   && !maze.getCell(r, c-1).visited) { Position nb={r,c-1}; parent_[nb]=cur; stack_.push(nb); }
    if (!cell.wallRight  && !maze.getCell(r, c+1).visited) { Position nb={r,c+1}; parent_[nb]=cur; stack_.push(nb); }

    return state_;
}

void DFSSolver::reconstructPath(const Position& end) {
    Position cur = end;
    while (cur.first != -1 && cur.second != -1) {
        path_.push_back(cur);
        cur = parent_[cur];
    }
    std::reverse(path_.begin(), path_.end());
}