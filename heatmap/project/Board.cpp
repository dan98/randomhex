#include<algorithm>
#include "Board.h"

Board::Board(int size){
  std::fill(&color[0][0], &color[0][0] + sizeof(color)/sizeof(color[0][0]), 0);
  n = size;
}

bool Board::getColor(Position p){
  return color[p.x][p.y];
}

void Board::fillRandom(int p){
  srand(time(0));
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++){
      color[i][j] = ((rand() % 100) < p);
    }
    color[0][i] = 1;
    color[n+1][i] = 1;
  }
}

void Board::buildGraph()
{

  int dx[] = {1, 0, -1, 0, 1, -1};
  int dy[] = {0, 1, 0, -1, -1, 1};

  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
      id[i][j] = n*(i-1) + j, key[n*(i-1)+ j] = {i,j};

  key[B1] = {0, 1};
  key[B2] = {n+1, 1};

  key[W1] = {1, 0};
  key[W2] = {1, n+1};

  for(int i=1; i<=n; ++i){
    id[0][i] = B1;
    id[n+1][i] = B2;
  
    id[i][0] = W1;
    id[i][n+1] = W2;

    G[B1].push_back(id[1][i]);
    G[id[1][i]].push_back(B1);

    G[B2].push_back(id[n][i]);
    G[id[n][i]].push_back(B2);

    G[W1].push_back(id[i][1]);
    G[id[i][1]].push_back(W1);

    G[W2].push_back(id[i][n]);
    G[id[i][n]].push_back(W2);
  }

  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
      for(int k=0; k<6; ++k){
        if((i+dx[k]<1 || i+dx[k]>n) + (j+dy[k]<0 || j+dy[k]>n) < 2)
        {
          bool nu = 0;
          for(auto el: G[id[i][j]])
            if(el == id[i+dx[k]][j+dy[k]])
              nu = 1;
          if(!nu){
            G[id[i][j]].push_back(id[i+dx[k]][j+dy[k]]);
            G[id[i+dx[k]][j+dy[k]]].push_back(id[i][j]);
          }
        }
      }
}
