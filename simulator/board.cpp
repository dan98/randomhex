#include <algorithm>
#include <utility>
#include <iostream>

#include "board.h"

#include <cmath>
#include <cstring>


Board::Board(int size, int type, int x){
  n = size;
  std::memset(prob, 0, sizeof(prob));
  std::memset(cnt, 0, sizeof(cnt));
  std::memset(art, 0, sizeof(art));
  std::memset(color, -1, sizeof(color));
  std::memset(fixed, 0, sizeof(fixed));
  for(int i=1; i<=W2; ++i){
    G[i].clear();
  }

  if(type == 0){
    buildGraph();
  }
  if(type == 1){
    buildGraphTriangle(x);
  }
  if(type == 2){
    buildGraphTrapezium(x);
  }
  if(type == 3){
    buildGraph();
    disableCenter(x);
  }
}

Board::~Board(void){
  std::memset(art, 0, sizeof(art));
  std::memset(color, -1, sizeof(color));
  for(int i=1; i<=W2; ++i){
    G[i].clear();
  }
  std::memset(G, 0, sizeof(G));
  std::memset(id, 0, sizeof(id));
}

int Board::getColor(int x, int y){
  return color[x][y];
}

int Board::getColor(int k){
  return color[key[k].first][key[k].second];
}

double Board::getProb(int x, int y){
    return prob[x][y];
}

double Board::getProbPr(int x, int y){
    return probpr[x][y];
}

void Board::disableCenter(int k){
  int cen = n/2;

  for(int i = -k+1; i<=k + (n%2); ++i){
    for(int j = -k+1; j<=k + (n%2); ++j){
      color[cen + i][cen + j] = -2;
      fixed[cen + i][cen + j] = 1;
    }
  }
}

int Board::boardSize(){
    return n;
}

void Board::fillRandom(int p){
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++){
      if(!fixed[i][j])
        color[i][j] = ((rand() % 100) < p);
    }
  }
  std::memset(art, 0, sizeof(art));
}

void Board::resetMove()
{
  std::memset(cnt, 0, sizeof(cnt));
}

void Board::move(int i, int j, bool col)
{
  fixed[i][j] = 1;
  color[i][j] = col;
  prob[i][j] = 0;
}

std::pair<int,int> Board::generateMove(int t, bool col){

    std::pair<int, int> rs = {-1, -1};

    for(int i=1; i<=t; ++i){
        fillRandom(50);
        findArticulationPoints(col);

        for(int j=1; j<=n; ++j)
            for(int k=1; k<=n; ++k)
                if(isBridge(j,k) && !(fixed[j][k]))
                    cnt[j][k] = cnt[j][k] + 1;
    }

    int maxk = 0;
    for(int j=1; j<=n; ++j)
        for(int k=1; k<=n; ++k)
            if(cnt[j][k] > maxk){
                maxk = cnt[j][k];
                rs = {j,k};
            }
    long double ssum=0;
    for(int j=1; j<=n; ++j)
        for(int k=1; k<=n; ++k)
          ssum += cnt[j][k]*cnt[j][k];
    ssum = sqrt(ssum);

    for(int j=1; j<=n; ++j)
        for(int k=1; k<=n; ++k)
          probpr[j][k] = prob[j][k];

    for(int j=1; j<=n; ++j)
        for(int k=1; k<=n; ++k)
            prob[j][k]=1.0L * cnt[j][k]/std::max(ssum, 1.0L);

    for(int j=1; j<=n; ++j)
        for(int k=1; k<=n; ++k)
          if(!fixed[j][k])
            color[j][k] = -1;
    std::memset(art, 0, sizeof(art));

    return rs;
}

bool Board::isBridge(int i, int j){
    return art[id[i][j]];
}

bool Board::isFixed(int i, int j){
    return fixed[i][j];
}

void Board::buildGraphTrapezium(int x)
{
  int dx[] = {1, 0, -1, 0, -1, 1};
  int dy[] = {0, 1, 0, -1, 1, -1};

  int h = 0;
  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
      if(i+j>n && i>x)
        id[i][j] = ++h, key[h] = {i,j};

  for(int i=0; i<=n+1; ++i)
    for(int j=0; j<=n+1; ++j)
      if(i+j<n || i<=x || (i==n+1 && j==0) || (i==n+1 && j==n+1)
          || (i==0 && j==n+1))
      {
        color[i][j] = -2;
        fixed[i][j] = 1;
      }

  for(int i=1; i<=W2; ++i){
    G[i].clear();
  }

  for(int i=x+1; i<n; ++i){
    color[0+i][n-i] = 0;
    id[0+i][n-i] = W1;
    G[W1].push_back(id[0+i+1][n-i]);
    G[id[0+i+1][n-i]].push_back(W1);
    fixed[0+i][n-i] = 1;
  }
  for(int i=1; i<=x; ++i){
    color[x][n-i+1] = 1;
    id[x][n-i+1] = B1;
    G[B1].push_back(id[x+1][n-i+1]);
    G[id[x+1][n-i+1]].push_back(B1);
    fixed[x][n-i+1] = 1;
  }
  G[B1].push_back(id[x+1][n-x]);
  G[id[x+1][n-x]].push_back(B1);

  color[n][0] = -2;
  fixed[n][0] = 1;

  key[B1] = {x, n};
  key[B2] = {n+1, 1};

  key[W1] = {x+1, n-x-1};
  key[W2] = {n, n+1};


  for(int i=1; i<=n; ++i){
    id[n+1][i] = B2;
    color[n+1][i] = 1;
    if(i>x)
    {
      id[i][n+1] = W2;
      color[i][n+1] = 0;
      fixed[i][n+1] = 1;
    }

    fixed[n+1][i] = 1;

    G[B2].push_back(id[n][i]);
    G[id[n][i]].push_back(B2);

    G[W2].push_back(id[i][n]);
    G[id[i][n]].push_back(W2);
  }

  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++){
      if(i+j <= n || i<=x)
        continue;
      for(int k=0; k<6; ++k){
        if((i+dx[k]<1 || i+dx[k]>n) + (j+dy[k]<1 || j+dy[k]>n) < 2)
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
}

void Board::buildGraphTriangle(int x)
{
  int dx[] = {1, 0, -1, 0, -1, 1};
  int dy[] = {0, 1, 0, -1, 1, -1};

  int h = 0;
  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
      if(i+j>n)
        id[i][j] = ++h, key[h] = {i,j};

  for(int i=0; i<=n+1; ++i)
    for(int j=0; j<=n+1; ++j)
      if(i+j<n || (i==n+1 && j==0) || (i==n+1 && j==n+1)
          || (i==0 && j==n+1))
      {
        color[i][j] = -2;
        fixed[i][j] = 1;
      }

  for(int i=1; i<=W2; ++i){
    G[i].clear();
  }

  for(int i=0; i<n; ++i){
    color[0+i][n-i] = (i<x);
    if(i<x){
      id[0+i][n-i] = B1;
      G[B1].push_back(id[0+i+1][n-i]);
      G[id[0+i+1][n-i]].push_back(B1);
    }
    else{
      id[0+i][n-i] = W1;
      G[W1].push_back(id[0+i+1][n-i]);
      G[id[0+i+1][n-i]].push_back(W1);
    }

    fixed[0+i][n-i] = 1;
  }

  color[n][0] = -2;
  fixed[n][0] = 1;

  key[B1] = {0, n};
  key[B2] = {n+1, 1};

  key[W1] = {n-1, 1};
  key[W2] = {1, n+1};


  for(int i=1; i<=n; ++i){
    id[n+1][i] = B2;
    color[n+1][i] = 1;
    id[i][n+1] = W2;
    color[i][n+1] = 0;

    fixed[n+1][i] = 1;
    fixed[i][n+1] = 1;

    G[B2].push_back(id[n][i]);
    G[id[n][i]].push_back(B2);

    G[W2].push_back(id[i][n]);
    G[id[i][n]].push_back(W2);
  }

  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++){
      if(i+j <= n)
        continue;
      for(int k=0; k<6; ++k){
        if((i+dx[k]<1 || i+dx[k]>n) + (j+dy[k]<1 || j+dy[k]>n) < 2)
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
}

void Board::buildGraph()
{
  int dx[] = {1, 0, -1, 0, -1, 1};
  int dy[] = {0, 1, 0, -1, 1, -1};

  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
      id[i][j] = n*(i-1) + j, key[n*(i-1)+ j] = {i,j};

  color[0][0] = -2;
  color[n+1][n+1] = -2;
  color[n+1][0] = -2;
  color[0][n+1] = -2;

  for(int i=1; i<=n; ++i){
    color[0][i] = 1;
    color[n+1][i] = 1;
    color[i][0] = 0;
    color[i][n+1] = 0;
    fixed[0][i] = 1;
    fixed[n+1][i] = 1;
    fixed[i][0] = 1;
    fixed[i][n+1] = 1;
  }


  fixed[0][0] = 1;
  fixed[n+1][n+1] = 1;
  fixed[n+1][0] = 1;
  fixed[0][n+1] = 1;

  key[B1] = {0, 1};
  key[B2] = {n+1, 1};

  key[W1] = {1, 0};
  key[W2] = {1, n+1};

  for(int i=1; i<=W2; ++i){
    G[i].clear();
  }

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
        if((i+dx[k]<1 || i+dx[k]>n) + (j+dy[k]<1 || j+dy[k]>n) < 2)
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

int Board::findArticulationPoints(int col){
    std::memset(viz, 0, sizeof(viz));
    std::memset(piv, 0, sizeof(piv));
    std::memset(art, 0, sizeof(art));
    std::memset(depth, 0, sizeof(depth));
    std::memset(pr, 0, sizeof(pr));
    std::memset(vB2, 0, sizeof(vB2));
    std::memset(vW2, 0, sizeof(vW2));
    std::memset(low, 0, sizeof(low));

    t = 0;
    dfs(B1, 1);
    t = 0;
    dfs(W1, 0);


    std::memset(viz, 0, sizeof(viz));
    int nr = 0;

    if(col == 2){
        for(int i=1; i<=B2; ++i){
            if(vB2[i] || vW2[i]){
                art[i] = piv[i];
            }
        }
    }
    else{
      for(int i=1; i<=B2; ++i){
          if((vB2[i] && col) || (vW2[i] && !col)){
              art[i] = piv[i];
          }
      }
    }
    for(int i=1; i<=n; ++i){
      for(int j=1; j<=n; ++j){
        nr += art[id[i][j]];
      }
    }
    return nr;
}


void Board::dfs(int v, bool c)
{
  std::pair<int, int> pp = key[v];
  if(color[pp.first][pp.second] != c){
    return;
  }
  vB2[v] |= (v == B2);
  vW2[v] |= (v == W2);

  int ch = 0;
  viz[v] = 1;
  depth[v] = ++t;
  low[v] = t;
  for(auto e: G[v])
  {
    int w = e;
    std::pair<int, int> pp = key[w];
    if(color[pp.first][pp.second] != c){
      continue;
    }
    if(!viz[w]){
      pr[w] = v;
      ch++;
      dfs(w, c);
      vB2[v] |= vB2[w];
      vW2[v] |= vW2[w];
      if(low[w] >= depth[v] && pr[v])
        piv[v]|=(vB2[w] || vW2[w]);
      low[v] = std::min(low[v], low[w]);
    }else if(w != pr[v])
      low[v] = std::min(low[v], depth[w]);
  }
  if(!pr[v] && ch > 1)
    piv[v] = (vB2[v] || vW2[v]);
}
