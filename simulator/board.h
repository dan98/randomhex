#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <vector>
#include <utility>

class Board
{

public:

  Board(int size, int type = 0, int x = 1);
  ~Board();

  int getColor(int x, int y);
  int getColor(int key);
  bool isBridge(int x, int y);
  int boardSize();
  void fillRandom(int p);
  int findArticulationPoints(int col);
  std::pair<int,int> generateMove(int t, bool col);
  void move(int i, int j, bool col);
  double getProb(int x, int y);
  double getProbPr(int x, int y);
  bool isFixed(int i, int j);
  void resetMove();

  void disableCenter(int k);

  std::pair<int, int> marked;

private:
  static const int BMAX = 19 + 4;
  static const int NMAX = BMAX*BMAX + 10;

  const int B1 = BMAX*BMAX + 1;
  const int B2 = BMAX*BMAX + 2;
  const int W1 = BMAX*BMAX + 3;
  const int W2 = BMAX*BMAX + 4;

  /*
  static const int dx[] = {1, 0, -1, 0, 1, -1};
  static const int dy[] = {0, 1, 0, -1, -1, 1};
  */


  int n;

  void dfs(int v, bool color);
  bool dfs2(int v, bool color);
  void buildGraph();
  void buildGraphTriangle(int x);
  void buildGraphTrapezium(int x);
  double prob[BMAX][BMAX];
  double probpr[BMAX][BMAX];
  int cnt[BMAX][BMAX];
  bool fixed[BMAX][BMAX];

  bool viz[NMAX];
  int pr[NMAX];
  int depth[NMAX];
  bool piv[NMAX];
  bool vB2[NMAX];
  bool vW2[NMAX];
  int art[NMAX];
  int low[NMAX];
  int m,t;

  // Boardsides

  int color[BMAX][BMAX];

  std::pair<int, int> key[NMAX];
  int id[BMAX][BMAX];


  // Graph edges
  std::vector<int> G[NMAX];
};

#endif
