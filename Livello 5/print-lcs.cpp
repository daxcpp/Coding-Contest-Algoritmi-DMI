//Coded By daxcpp (Davide Carnemolla)
#include <iostream>
#include <fstream>
using namespace std;

void print_LCS(int** M, string x, string y, int n, int m, ofstream &out){
  int k=M[n][m];
  char o[k+1];
  o[k]='\0';
  int i=n;
  int j=m;
  while (i>0 && j>0){
    if (x[i-1]==y[j-1]){
      o[k-1]=x[i-1];
      k--; i--; j--;
    }
    else
      if (M[i][j-1] >= M[i-1][j])   
        j--;
      else
        i--;
  }
  out << o << endl;
  for (int a=0; a<n+1; a++)
    delete[] M[a];
  delete[] M;
}

void LCS(string x, string y, int n, int m, ofstream &out){
  int** M=new int*[n+1];
  for (int i=0; i<n+1; i++)
    M[i]=new int[m+1];
  for (int i=0; i<n+1; i++)
    M[i][0]=0;
  for (int i=0; i<m+1; i++)
    M[0][i]=0;


  for (int i=1; i<n+1; i++){
    for (int j=1; j<m+1; j++){
      if (x[i-1]==y[j-1])
        M[i][j]=M[i-1][j-1]+1;
      else
        M[i][j]=max(M[i-1][j], M[i][j-1]);
    }
  }
  print_LCS(M, x, y, n, m, out);
}


int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        int n; in >> n;
        int m; in >> m;
        string x; in >> x;
        string y; in >> y;

        LCS(x,y,n,m, out);
    }
}
