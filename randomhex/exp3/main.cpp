#include<bits/stdc++.h>

#include "../board.h"

using namespace std;
typedef long long LL;
typedef long double LD;

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

  int tt = 10000000;
  LD rs = 0;

  gen_random(rndstr, 7);
  sprintf(buffer, "boards/%dx%d/%s.res", n, n, rndstr);
  freopen(buffer, "w", stdout);

  Board* exp = new Board(n);
  for(int i=1; i<=tt; ++i){
    // read-write

    exp->fillRandom(50);
    rs += exp->findArticulationPoints(2);
  }

  cout<<(rs/tt)<<"\n";

}
