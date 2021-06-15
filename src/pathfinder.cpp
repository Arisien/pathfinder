#include <iostream>
#include <climits>

using namespace std;

class Position {
  public:
    int x;
    int y;
    Position (int a, int b)  {
      x = a;
      y = b;
    }
};

class Path {
  public:
    Position start;
    Position goal;
    Position move;
    bool possible;
    int distance;
    Path (Position s, Position g, Position m, bool p, int d): start {s}, goal {g}, move{m} {
      start = s;
      goal = g;
      possible = p;
      distance = d;
    }
    void print () {
      cout << "Starting Position: [" << start.x << ", " << start.y << "]" << endl;
      cout << "Goal: [" << goal.x << ", " << goal.y << "]" << endl;

      if (!possible) cout << "Goal is unreachable!" << endl;
      else {
        cout << "Distance: " << distance << endl;
        cout << "Suggested Move: [" << move.x << ", " << move.y << "]" << endl;
      }
    }
};

void printMap (char map[][6], Position start, Position goal) {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      if (start.y == i && start.x == j) cout << '$';
      else if (goal.y == i && goal.x == j) cout << 'X';
      else cout << map[i][j];
    }
    cout << endl;
  }
  cout << endl;
}


void pathfind (int levels[][6], int x, int y, int value) {
  levels[y][x] = value;

  if (y < 5 && levels[y+1][x] > levels[y][x] + 1) pathfind(levels, x, y+1, levels[y][x]+1);
  if (y > 0 && levels[y-1][x] > levels[y][x] + 1) pathfind(levels, x, y-1, levels[y][x]+1);
  if (x < 5 && levels[y][x+1] > levels[y][x] + 1) pathfind(levels, x+1, y, levels[y][x]+1);
  if (x > 0 && levels[y][x-1] > levels[y][x] + 1) pathfind(levels, x-1, y, levels[y][x]+1);
}

Path* pathfinder (char map[][6], Position start, Position goal) {

  int levels[6][6];

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      if (map[i][j] == '#') levels[i][j] = -1;
      else levels[i][j] = INT_MAX;
    }
  }

  if (map[goal.y][goal.x] != '#') pathfind(levels, start.x, start.y, 0);

  int x = goal.x;
  int y = goal.y;

  int distance = levels[y][x];
  bool possible = true;

  if (distance == -1 || distance == INT_MAX) possible = false;

  int temp = distance;

  while (possible && distance > 1) {
    if (x < 5 && levels[y][x+1] == distance-1) x++;
    else if (x > 0 && levels[y][x-1] == distance-1) x--;
    else if (y < 5 && levels[y+1][x] == distance-1) y++;
    else if (y > 0 && levels[y-1][x] == distance-1) y--;
    else break;
    distance--;
  }

  distance = temp;

  Position move = *(new Position(x,y));

  return new Path(start, goal, move, possible, distance);
}

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
