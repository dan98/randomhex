#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef long double LD;
const LL LLinf=9e18+5;
const int MOD=1e9 + 7;
const int NMAX = 19*19 + 200;
const int BMAX = 19 + 2;
const int INF = 0x3f3f3f3f;

int dx[] = {1, 0, -1, 0, 1, -1};
int dy[] = {0, 1, 0, -1, -1, 1};

int n;

// Boardsides
int b1 = BMAX*BMAX + 1;
int b2 = BMAX*BMAX + 2;
int w1 = BMAX*BMAX + 3;
int w2 = BMAX*BMAX + 4;

int tab[BMAX][BMAX];
int id[BMAX][BMAX];

pair<int, int> key[NMAX];

vector<int> G[NMAX];
bool viz[NMAX];
int pr[NMAX];
int depth[NMAX];
bool piv[NMAX];
int piv2[NMAX];
int low[NMAX];
int m,t;
 
void dfs(int v)
{
  pair<int, int> pp = key[v];
  if(tab[pp.x][pp.y] == 0){
    return;
  }

  int ch = 0;
  viz[v] = 1;
  depth[v] = ++t;
  low[v] = t;
  for(auto e: G[v])
  {
    int w = e;
    pair<int, int> pp = key[w];
    if(tab[pp.x][pp.y] == 0){
      continue;
    }
    if(!viz[w]){
      pr[w] = v;
      ch++;
      dfs(w);
      if(low[w] >= depth[v] && pr[v])
        piv[v]=1;
      low[v] = min(low[v], low[w]);
    }else if(w != pr[v])
      low[v] = min(low[v], depth[w]);
  }
  if(!pr[v] && ch > 1)
    piv[v] = 1;
}

bool dfs2(int v, int p){
  viz[v] = 1;
  pair<int, int> pp = key[v];
  if(tab[pp.x][pp.y] == 0){
    return 0;
  }
  if(v == b2){
    return 1; 
  }

  for(auto e: G[v]){
    int w = e;
    if(viz[w])
      continue;
    pair<int, int> pp = key[w];
    if(tab[pp.x][pp.y] == 0){
      continue;
    }
    if(dfs2(w, v))
    {
      if(piv[v]){
        piv2[v]++;
      }
      return 1;
    }
  }
  return 0;

}

bool qq;
 
bool check(int i, int j){
  return (j>=1) && (j<=n) && (i>=0) && (i<=n+1);
}

void generateBoard(int p){
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++){
      tab[i][j] = ((rand() % 100) < p);
    }
  }
}

void solve(){
  n = 15;
  m = 0;
  
  srand(time(0));

  // Build the graph
  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
      id[i][j] = n*(i-1) + j, key[n*(i-1)+ j] = {i,j};

  key[b1] = {0, 1};
  key[b2] = {n+1, 1};


  for(int i=1; i<=n; ++i){
    id[0][i] = b1;
    id[n+1][i] = b2;
  
    tab[0][i] = 1;
    tab[n+1][i] = 1;

    G[b1].push_back(id[1][i]);
    G[id[1][i]].push_back(b1);

    G[b2].push_back(id[n][i]);
    G[id[n][i]].push_back(b2);
  }

  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
      for(int k=0; k<6; ++k){
        if(check(i+dx[k], j+dy[k]))
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

  // p=P({the hex is black}); (in percentages)

  int T = 100000;
  for(int tt=1; tt<=T; ++tt){
    generateBoard(50);
    memset(viz, 0, sizeof(viz));
    memset(low, 0, sizeof(low));
    memset(piv, 0, sizeof(piv));
    memset(depth, 0, sizeof(depth));
    memset(pr, 0, sizeof(pr));

    // Fnd Articulation Vertices
    for(int i=1; i<=b2; ++i)
      if(!viz[i])
        t=0, dfs(i);
   
    memset(viz, 0, sizeof(viz));
     
    dfs2(b1, 0);
  }

  for(int i=1; i<n+1; i++){
    for(int j=1; j<=n; j++){
      cout<<piv2[id[i][j]]<<" ";
    }
    cout<<";\n";
  }
}

int main()
{
  cout<<setprecision(6)<<fixed;
	ios_base::sync_with_stdio(0);
	cin.tie(0);


  solve();
	 
	return 0;
}
