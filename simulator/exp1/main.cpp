#include<bits/stdc++.h>

#include "../board.h"

using namespace std;

struct entr{
  int x, y, col;
};


void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}


int winner[5];

int main(int argc, char * argv[])
{
  cout<<setprecision(6)<<fixed;
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  if(argc != 3){
    cerr<<"input error \n";
    return 0;
  }

  char buffer[50];
  char rndstr[50];
  int n = atoi(argv[1]);
  srand(atoi(argv[2]));

  vector<entr> hist;
  pair<int, int> zeros = {0, 0};
  
  int tt = 10000;

  gen_random(rndstr, 7);
  sprintf(buffer, "boards/%dx%d/%s.res", n, n, rndstr);
  freopen(buffer, "w", stdout);

  for(int i=1; i<=tt; ++i){
    hist.clear();

    // read-write

    Board* exp = new Board(n);

    pair<int, int> rs = {1, 1};

    int cen = n/2 + n%2;
    exp->move(cen, cen, 0);
    hist.push_back({cen, cen, 0});

    bool curr;
    int nrmoves = 50000;
    double game_eps = 0.005;
    while(rs != zeros)
    {
      curr = ((rand()%100)<50);

      for(int i=1; i<=100; ++i){
        rs = exp->generateMove(nrmoves/100, curr);
        int n = exp->boardSize();

        double diff = 0;
        for(int j=1; j<=n; ++j)
            for(int k=1; k<=n; ++k)
              diff = std::max(exp->getProb(j, k) - exp->getProbPr(j, k), diff);

        if(diff<game_eps)
          break;
      }
      exp->move(rs.first, rs.second, curr);
      hist.push_back({rs.first, rs.second, curr});
      cerr<<hist[hist.size()-1].x<<" "<<hist[hist.size()-1].y<<" "<<hist[hist.size()-1].col<<"\n";
      exp->resetMove();
    }
    cout<<hist.size()<<" "<<hist[hist.size() - 2].col<<"\n";
    cerr<<"board #"<<i<<" "<<hist.size()<<"\n";
    for(int j=0; j<hist.size(); ++j)
    {
      cout<<hist[j].x<<" "<<hist[j].y<<" "<<hist[j].col<<endl;
    }

    delete exp;
  }

}
