#include<bits/stdc++.h>
#include<dirent.h>

using namespace std;

typedef long long LL;
typedef long double LD;
int A[300555];

int main(int argc, char * argv[])
{
  cout<<setprecision(12)<<fixed;
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  DIR *pdir;
  struct dirent *entry;
  char dirname[50];
  char buffer[50];
  char file[50];
  int totg=0;
  ofstream fout("results.txt");
  for(int i=5; i<=19; ++i){
    sprintf(dirname, "./boards/%dx%d/", i, i);
    cerr<<dirname<<"\n";
    int k = 0;
    LD totw = 0;
    int win = 0;
    int n = 0;
    int games = 0;
    if(pdir = opendir(dirname))
    {
      while(entry = readdir(pdir)){
        sprintf(buffer, "%s", entry->d_name);
        cerr<<buffer<<"\n";
        if(strcmp(buffer, ".")==0 || strcmp(buffer, "..")==0)
          continue;
        sprintf(file, "%s%s", dirname, buffer);
        cerr<<file<<"\n";
        ifstream rfile(file);
        int a, b, col;
        while(rfile>>n>>win){
          for(int i=1; i<=n; ++i){
            rfile>>a>>b>>col;
          }
          games++;
        }
      }

      fout<<i<<" "<<games<<"\n";
      totg += games;
      closedir(pdir);
    }
  }
  cout<<totg<<" - tot nr of games\n";
}
