#include<bits/stdc++.h>

using namespace std;

int inc[100000];
int idcell[5][5];
int gamesize = 0;
int nrgames;

int main(){
  int k = 0;
  for(int i=1; i<5; i++){
    for(int j=1; j<5; j++){
      idcell[i][j] = k++;
    }
  }
  nrgames = 50343;

  ofstream cout("counted.out");
  for(int i=0; i<=nrgames; ++i){
    char buff[50];
    sprintf(buff, "%.4d.sgf", i);
    ifstream cin(buff);

    int b=0,w=0;
    int step = 0;
    string s;
    while(cin>>s){
      if(s.size() == 6)
      {
        step ++;
        if(s[1] == 'B')
          b+=(1<<idcell[s[3]-'a' + 1][s[4]-'0']);
        else
          w+=(1<<idcell[s[3]-'a' + 1][s[4]-'0']);
      }
    }
    if(w == 57690){
      cerr<<i<<"\n";
    }
    inc[b]++;
    inc[w]++;

    gamesize += step;
  }
  for(int id=0; id<(1<<16); id++){
    if(inc[id])
    cout<<id<<" "<<inc[id]<<"\n";
  }
  cerr<<"Average game length "<<1.0L*gamesize / nrgames<<"\n";

  return 0;
}
