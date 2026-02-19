#include "bfs.h"
#include <algorithm>

BFSSolver::BFSSolver() : state_(SolverState::IDLE) {}

void BFSSolver::init(Maze& maze) {
    while (!queue_.empty()) queue_.pop();
    parent_.clear();
    visited_.clear();
    path_.clear();

    maze.resetVisited();

    Position start = { maze.startRow, maze.startCol };
    queue_.push(start);
    maze.getCell(start.first, start.second).visited = true;
    parent_[start] = { -1, -1 };

    state_ = SolverState::SEARCHING;
}

SolverState BFSSolver::step(Maze& maze) {
    if (state_ != SolverState::SEARCHING) return state_;

    if (queue_.empty()) {
        state_ = SolverState::NO_PATH;
        return state_;
    }

    Position cur = queue_.front(); queue_.pop();
    int r = cur.first, c = cur.second;
    visited_.push_back(cur);

    Position end = { maze.endRow, maze.endCol };
    if (cur == end) {
        reconstructPath(end);
        state_ = SolverState::DONE;
        return state_;
    }

    Cell& cell = maze.getCell(r, c);

    if (!cell.wallTop    && !maze.getCell(r-1, c).visited) { Position nb={r-1,c}; maze.getCell(r-1,c).visited=true; parent_[nb]=cur; queue_.push(nb); }
    if (!cell.wallBottom && !maze.getCell(r+1, c).visited) { Position nb={r+1,c}; maze.getCell(r+1,c).visited=true; parent_[nb]=cur; queue_.push(nb); }
    if (!cell.wallLeft   && !maze.getCell(r, c-1).visited) { Position nb={r,c-1}; maze.getCell(r,c-1).visited=true; parent_[nb]=cur; queue_.push(nb); }
    if (!cell.wallRight  && !maze.getCell(r, c+1).visited) { Position nb={r,c+1}; maze.getCell(r,c+1).visited=true; parent_[nb]=cur; queue_.push(nb); }

    return state_;
}

void BFSSolver::reconstructPath(const Position& end) {
    Position cur = end;
    while (cur.first != -1 && cur.second != -1) {
        path_.push_back(cur);
        cur = parent_[cur];
    }
    std::reverse(path_.begin(), path_.end());
}