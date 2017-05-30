#include<bits/stdc++.h>

#include "board.h"

using namespace std;

struct entr{
  int col, x, y;
};


int winner[5];

int main(int argc, char * argv[])
{
  cout<<setprecision(6)<<fixed;
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  if(argc != 2){
    cout<<"input error";
  }

  char buffer[50];
  int n = atoi(argv[1]);

  vector<int> hist;
  

  for(int i=1; i<=2; ++i){
    hist.clear();
    sprintf(buffer, "boards/%dx%d/%d.in", n, n, i);
    freopen(buffer, "w", stdout);

    // read-write

    Board* exp = new Board(n);

    pair<int, int> rs = make_pair(1, 1);

    exp->move(n/2, n/2, 0);
    hist.push_back({n/2, n/2, 0});

    bool curr;
    bool loser = 1;
    int nrmove = 40000;
    while(rs != std::make_pair(0, 0))
    {
      curr = ((rand()%100)<50);

      rs = exp->generateMove(nrmove, curr);
      exp->move(rs.first, rs.second, curr);
      hist.push_back({rs.first, rs.second, curr});
      exp->resetMove();
      nrmove -= 1000;
    }
    cout<<hist.size()<<"\n";
    jerr<<hist.size()<<"\n";
    for(int i=0; i<hist.size(); ++i)
    {
      cout<<hist[i].x<<" "<<hist[i].y<<" "<<hist[i].col<<"\n";
    }

    delete exp;

    fclose(stdout);
  }

}
