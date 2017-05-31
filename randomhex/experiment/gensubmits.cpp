#include<bits/stdc++.h>
#define x first
#define pb push_back
#define y second
#define all(a) a.begin(), a.end()
#define l(x) (x<<1)
#define r(x) ((x<<1) | 1)
#define lsb(x) (x&(-x))
using namespace std;
typedef long long LL;
typedef long double LD;
typedef vector<LL> VLL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
typedef vector<int> VI;
typedef VI::iterator vit;
const LL INF=1e6;
const int NMAX=500;
const LD pi=acos(-1.0);

int main(int argc, char* argv[])
{
  time_t tic = clock();

  int tt=100;

  char buffer[50];

  for(int i=5; i<=19; ++i){
    sprintf(buffer, "submits/%d.sh", i);
    freopen(buffer, "w", stdout);

    // read-write
    cout<<"#!/bin/bash\n";
    cout<<"#SBATCH --time=10:00:00\n";
    cout<<"#SBATCH --nodes=1\n";
    cout<<"#SBATCH --ntasks=1\n";
    cout<<"#SBATCH --job-name=randomhex"<<i<<"\n";
    cout<<"#SBATCH --mem=500\n";

    cout<<"./A boards/"<<i<<"x"<<i<<"/ "<<i<<"\n";



    fclose(stdout);
  }

  time_t toc = clock(); 

  cout<<"\n";

  cout<<"It took "<<(double)(toc-tic)/CLOCKS_PER_SEC<<" s.";
  return 0;
}



