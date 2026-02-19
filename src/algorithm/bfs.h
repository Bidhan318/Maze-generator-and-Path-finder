#pragma once
#include "src/maze/maze.h"
#include <vector>
#include <queue>
#include <map>
#include <utility>

using Position = std::pair<int,int>;

enum class SolverState {
    IDLE,        
    SEARCHING,   
    DONE,        
    NO_PATH    
};

class BFSSolver {
public:
    BFSSolver();

    void init(Maze& maze);

    SolverState step(Maze& maze);

    SolverState getState() const { return state_; }

    const std::vector<Position>& getVisited() const { return visited_; }

    // Final shortest path (only valid when state == DONE)
    const std::vector<Position>& getPath() const { return path_; }

private:
    SolverState state_;
    std::queue<Position>         queue_;
    std::map<Position, Position> parent_;  
    std::vector<Position>        visited_;  
    std::vector<Position>        path_;     

    void reconstructPath(const Position& end);
};