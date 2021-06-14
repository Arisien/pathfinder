# Pathfinder

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Pathfinder is a C++ program which searches for the ideal path from point A to B in within a 2 dimensional character array. Walls are denoted with hashtags while empty spaces are marked with the space character. The program will mark the distance of all reachable points on the map from the starting position. If the goal position is reachable it will then backtrace to the starting position and find the best move to reach the goal.

## Usage

The path to your goal destination can be found by calling the pathfinder function. Its parameters are the character array containing the map, the starting position, and the ending position. Positions are simple objects containing public x and y integer properties. The pathfinder will return a pointer to a Path object. The following is a sample use of the pathfinding function:

```cpp
int main (void) {
  char map [6][6] = {
    {' ', ' ', ' ', ' ', '#', ' '},
    {' ', '#', '#', ' ', '#', ' '},
    {' ', '#', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', '#', '#', '#'},
    {'#', ' ', '#', ' ', '#', ' '},
    {' ', ' ', ' ', ' ', ' ', '#'}
  };

  Path path = *pathfinder(map, Position(0,0), Position(3,4));

  printMap(map, path.start, path.goal);

  path.print();

  return 0;
}
```

The Path objects contains information about the pathfinding attempt. It has the inputed starting and goal positions, whether or not the goal is reachable, the length of the path (labeled distance), and the suggested adjacent position to move to reach the goal as quickly as possible. The following is the sample output:

```
$   #
 ## #
 #
   ###
# #X#
     #

Starting Position: [0, 0]
Goal: [3, 4]
Distance: 9
Suggested Move: [0, 1]
```

The map is drawn with $ being the starting position and X being the goal. The information about the path below is printed to console when path.print() is called.


## Building

*Note: a C++ compiler is required to run the program. Alternatively download the binaries from releases*

* Compile the source file within the source directory: `g++ pathfinder.cpp`
* Run pathfinder by running the created binary: `./a.out`

## Todo

* Random generation of maps
* Configurable size of maps (not just 6*6)
* Map files

## Contributors

* [Arisien](https://github.com/Arisien) - Main developer

## License
Pathfinder is licensed under the [MIT](LICENSE) license. Feel free to fork the repository or modify the code as you see fit.
