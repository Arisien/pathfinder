# Pathfinder

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Pathfinder is a C++ program which searches for the ideal path from point A to B in within a 2 dimensional character vector. Walls are denoted with hashtags while empty spaces are marked with the space character. The program will mark the distance of all reachable points on the map from the starting position. If the goal position is reachable it will then backtrace to the starting position and find the best move to reach the goal in the least amount of steps.

## Usage

The path to your goal destination can be found by calling the pathfinder function. Its parameters are the character vector containing the map, the starting position, and the ending position. Positions are simple objects containing public x and y integer properties. The pathfinder will return a pointer to a Path object. The following is a sample use of the pathfinding function:

```cpp
#include "pathfinder.hpp"

int main (void) {
  Pathfinder::Position start = Pathfinder::Position(0,0);
  Pathfinder::Position goal = Pathfinder::Position(5,6);

  std::vector<std::vector<char>> map = Pathfinder::generateMap(8,8, start, goal);

  Pathfinder::Path path = *Pathfinder::pathfinder(map, start, goal);

  path.print();

  return 0;
}
```

The Path objects contains information about the pathfinding attempt. It has the inputed starting and goal positions, whether or not the goal is reachable, the length of the path (labeled distance), and a vector containing the sequence of moves used to reach the goal position. The following is the sample output:

```
$ 1 2 3 4 5 . .
# # # . # 6 . .
# . . # . 7 . #
. . . . . 8 9 0
# # # # # # # 1
# # . # # . . 2
. # . . . X 4 3
. . . . . . # .

Starting Position: [0, 0]
Goal: [5, 6]
Distance: 15
Suggested Move: Right
```

The map is drawn with $ being the starting position and X being the goal. The information about the path below is printed to console when path.print() is called.


## Building

*Note: a C++ compiler is required to run the program. Alternatively download the binaries from releases*

* Compile the source file within the source directory: `g++ test.cpp`
* Run pathfinder by running the created binary: `./a.out`

## Todo

* Clean up code
* Map files

## Contributors

* [Arisien](https://github.com/Arisien) - Main developer

## License
Pathfinder is licensed under the [MIT](LICENSE) license. Feel free to fork the repository or modify the code as you see fit.
