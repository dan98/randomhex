#include<bits/stdc++.h>

#include "board.h"

using namespace std;

int winner[5];

int main()
{
  for(int i=1; i<=100; ++i)
  {
    cout<<"play #"<<i<<"\n";
    Board* exp = new Board(6);

    pair<int, int> rs = make_pair(1, 1);
    bool curr;
    while(rs != std::make_pair(0, 0))
    {
      curr = ((rand()%100)<50);
      rs = exp->generateMove(5000, curr);
      exp->move(rs.first, rs.second, curr);
      exp->resetMove();
    }

    winner[curr]++;

    delete exp;
  }
  cout<<winner[0]<<" "<<winner[1]<<"\n";


}
