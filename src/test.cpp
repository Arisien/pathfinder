#include "pathfinder.hpp"

int main (void) {
  Position start = Position(0,0);
  Position goal = Position(5,6);

  vector<vector<char>> map = generateMap(8,8, start, goal);

  Path path = *pathfinder(map, start, goal);

  path.print();

  return 0;
}
