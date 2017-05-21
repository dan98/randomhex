#ifndef BOARD_HPP
#define BOARD_HPP

#include <map>
#include <vector>
#include <utility>

class Board
{
public: 

  Board(int size);

  bool getColor(int p);
  void fillRandom(int p);
  void buildGraph();

private:
  static const int BMAX = 19 + 2;
  static const int NMAX = BMAX*BMAX + 10;

  /*
  static const int dx[] = {1, 0, -1, 0, 1, -1};
  static const int dy[] = {0, 1, 0, -1, -1, 1};
  */

  int n;

  // Boardsides
  const int B1 = BMAX*BMAX + 1;
  const int B2 = BMAX*BMAX + 2;
  const int W1 = BMAX*BMAX + 3;
  const int W2 = BMAX*BMAX + 4;

  int color[BMAX][BMAX];

  std::pair<int, int> key[NMAX];
  int id[BMAX][BMAX];
  

  // Graph edges
  std::vector<int> G[NMAX];
};

#endif
