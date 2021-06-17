#include "pathfinder.hpp"

int main (void) {
  Pathfinder::Position start = Pathfinder::Position(0,0);
  Pathfinder::Position goal = Pathfinder::Position(5,6);

  std::vector<std::vector<char>> map = Pathfinder::generateMap(8,8, start, goal);

  Pathfinder::Path path = *Pathfinder::pathfinder(map, start, goal);

  path.print();

  return 0;
}
