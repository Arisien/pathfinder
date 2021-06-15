#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

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
    string toString () {
      return "[" + to_string(x) + ", " + to_string(y) + "]";
    }
};

class Path {
  public:
    Position start;
    Position goal;
    vector<Position> moves;
    vector<vector<int>> levels;
    bool possible;
    int distance;
    Path (Position s, Position g, vector<Position> m, vector<vector<int>> l, bool p, int d): start {s}, goal {g}, moves{m}, levels{l} {
      start = s;
      goal = g;
      possible = p;
      distance = d;
      levels = l;
      moves = m;
    }
    Path (Position s, Position g, vector<vector<int>> l, bool p, int d): start {s}, goal {g}, levels{l} {
      start = s;
      goal = g;
      possible = p;
      distance = d;
      levels = l;
      moves = vector<Position>(0);
    }
    void print () {
      for (int i = 0; i < levels.size(); i++) {
        for (int j = 0; j < levels[i].size(); j++) {
          if (levels[i][j] == -1) cout << "# ";
          else if (start.x == j && start.y == i) cout << "$ ";
          else if (goal.x == j && goal.y == i) cout << "X ";
          else {
            bool isPath = false;
            if (possible) {
              for (int k = 0; k < moves.size(); k++) {
                if (moves[k].x == j && moves[k].y == i) {
                  isPath = true;
                  cout << (k+1)%10 << " ";
                  break;
                }
              }
            }
            if (!isPath) cout << ". ";
          }
        }
        cout << endl;
      }
      cout << endl;

      cout << "Starting Position: " << start.toString() << endl;
      cout << "Goal: " << goal.toString() << endl;

      if (!possible) cout << "Goal is unreachable!" << endl;
      else {
        cout << "Distance: " << distance << endl;
        cout << "Suggested Move: ";
        if (moves[0].x > start.x) cout << "Right";
        else if (moves[0].x < start.x) cout << "Left";
        else if (moves[0].y > start.y) cout << "Down";
        else cout << "Up";
        cout << endl;
      }
    }
};

void pathfind (vector<vector<int>> &levels, int x, int y, int value) {
  levels[y][x] = value;

  if (y < levels.size() - 1 && levels[y+1][x] > value + 1) pathfind(levels, x, y+1, value+1);
  if (y > 0 && levels[y-1][x] > value + 1) pathfind(levels, x, y-1, value+1);
  if (x < levels[y].size() - 1 && levels[y][x+1] > value + 1) pathfind(levels, x+1, y, value+1);
  if (x > 0 && levels[y][x-1] > value + 1) pathfind(levels, x-1, y, value+1);

}

Path* pathfinder (vector<vector<char>> map, Position start, Position goal) {

  vector<vector<int>> levels(map.size());

  for (int i = 0; i < map.size(); i++) {

    levels[i] = vector<int>(map[i].size());

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

    vector<Position> moves(distance-1);

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

int main (int argc, char *argv[]) {

  Position start, goal;

  if (argc == 5) {
    start = Position(stoi(argv[1]), stoi(argv[2]));
    goal = Position(stoi(argv[3]), stoi(argv[4]));
  }
  else {
    start = Position(0, 0);
    goal = Position(3, 5);
  }

  vector<vector<char>> map = {
    {' ', ' ', ' ', ' ', '#', ' '},
    {' ', '#', '#', ' ', '#', ' '},
    {' ', '#', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', '#', '#', '#'},
    {'#', ' ', '#', ' ', '#', ' '},
    {' ', ' ', ' ', ' ', ' ', '#'}
  };

  Path path = *pathfinder(map, start, goal);

  path.print();

  return 0;
}
