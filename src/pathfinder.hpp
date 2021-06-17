#ifndef PATHFINDER
#define PATHFINDER

#include <iostream>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

namespace Pathfinder {

  class Position {
  public:
    int x;
    int y;
    Position () {
      x = 0;
      y = 0;
    }
    Position (int a, int b)  {
      x = a;
      y = b;
    }
    std::string toString () {
      return "[" + std::to_string(x) + ", " + std::to_string(y) + "]";
    }
    bool equals (int a, int b) {
      if (x == a && y == b) return true;
      return false;
    }
  };

  class Path {
  public:
    Position start;
    Position goal;
    std::vector<Position> moves;
    std::vector<std::vector<int>> levels;
    bool possible;
    int distance;
    Path (Position s, Position g, std::vector<Position> m, std::vector<std::vector<int>> l, bool p, int d): start {s}, goal {g}, moves{m}, levels{l} {
      start = s;
      goal = g;
      possible = p;
      distance = d;
      levels = l;
      moves = m;
    }
    Path (Position s, Position g, std::vector<std::vector<int>> l, bool p, int d): start {s}, goal {g}, levels{l} {
      start = s;
      goal = g;
      possible = p;
      distance = d;
      levels = l;
      moves = std::vector<Position>(0);
    }
    void print () {
      for (int i = 0; i < levels.size(); i++) {
        for (int j = 0; j < levels[i].size(); j++) {
          if (levels[i][j] == -1) std::cout << "# ";
          else if (start.equals(j,i)) std::cout << "$ ";
          else if (goal.equals(j,i)) std::cout << "X ";
          else {
            bool isPath = false;
            if (possible) {
              for (int k = 0; k < moves.size(); k++) {
                if (moves[k].x == j && moves[k].y == i) {
                  isPath = true;
                  std::cout << (k+1)%10 << " ";
                  break;
                }
              }
            }
            if (!isPath) std::cout << ". ";
          }
        }
        std::cout << std::endl;
      }
      std::cout << std::endl;

      std::cout << "Starting Position: " << start.toString() << std::endl;
      std::cout << "Goal: " << goal.toString() << std::endl;

      if (!possible) std::cout << "Goal is unreachable!" << std::endl;
      else {
        std::cout << "Distance: " << distance << std::endl;
        std::cout << "Suggested Move: ";
        if (moves[0].x > start.x) std::cout << "Right";
        else if (moves[0].x < start.x) std::cout << "Left";
        else if (moves[0].y > start.y) std::cout << "Down";
        else std::cout << "Up";
        std::cout << std::endl;
      }
    }
  };

  void pathfind (std::vector<std::vector<int>> &levels, int x, int y, int value) {
    levels[y][x] = value;

    if (y < levels.size() - 1 && levels[y+1][x] > value + 1) pathfind(levels, x, y+1, value+1);
    if (y > 0 && levels[y-1][x] > value + 1) pathfind(levels, x, y-1, value+1);
    if (x < levels[y].size() - 1 && levels[y][x+1] > value + 1) pathfind(levels, x+1, y, value+1);
    if (x > 0 && levels[y][x-1] > value + 1) pathfind(levels, x-1, y, value+1);

  }

  Path* pathfinder (std::vector<std::vector<char>> map, Position start, Position goal) {

    std::vector<std::vector<int>> levels(map.size());

    for (int i = 0; i < map.size(); i++) {

      levels[i] = std::vector<int>(map[i].size());

      for (int j = 0; j < map[i].size(); j++) {
        if (map[i][j] == '#') levels[i][j] = -1;
        else levels[i][j] = INT_MAX;
      }
    }

    if (map[goal.y][goal.x] != '#') pathfind(levels, start.x, start.y, 0);

    int x = goal.x;
    int y = goal.y;

    int distance = levels[y][x];
    bool possible = true;

    if (distance == -1 || distance == INT_MAX) {
      possible = false;
      distance = 0;
    }


    if (possible) {
      int temp = distance;

      std::vector<Position> moves(distance-1);

      while (distance > 1) {
        if (x < levels[y].size() - 1 && levels[y][x+1] == distance-1) x++;
        else if (x > 0 && levels[y][x-1] == distance-1) x--;
        else if (y < levels.size() - 1 && levels[y+1][x] == distance-1) y++;
        else if (y > 0 && levels[y-1][x] == distance-1) y--;
        else break;
        distance--;
        moves[distance-1] = Position(x,y);
      }

      distance = temp;

      return new Path(start, goal, moves, levels, possible, distance);
    }

    else return new Path(start, goal, levels, possible, distance);
  }

  std::vector<std::vector<char>> generateMap (int height, int width, Position start, Position goal) {
    srand(time(NULL));

    int p = 30;

    std::vector<std::vector<char>> map = std::vector<std::vector<char>>(height);

    for (int i = 0; i < height; i++) {
      map[i] = std::vector<char>(width);
      for (int j = 0; j < width; j++) {
        char c = ' ';
        if (rand() % 100 < p && !start.equals(j,i) && !goal.equals(j,i)) c = '#';
        map[i][j] = c;
      }
    }

    return map;
  }

}

#endif
