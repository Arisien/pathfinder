#include "pathfinder.hpp"

using namespace Pathfinder;

int main (void) {
  Position start = Position(0,0);
  Position goal = Position(5,6);

  Path path = pathfinder(generateMap(8,8, start, goal), start, goal);

  path.print();

  return 0;
}
