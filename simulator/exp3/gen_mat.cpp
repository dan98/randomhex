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
  ofstream fout("results.txt");
  for(int i=5; i<=19; ++i){
    sprintf(dirname, "./boards/%dx%d/", i, i);
    cerr<<dirname<<"\n";
    int k = 0;
    LD tot = 0;
    LD val;
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
        cin>>val;
        cout<<val<<" ";
        tot+=val;
        k++;
      }
      cout<<i<<" "<<(tot/k)<<"\n";
      closedir(pdir);
    }
  }
}
