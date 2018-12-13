#include <iostream>
#include <fstream>
using namespace std;

int** LCSlenght(string x , string y, int n, int m){
    int** C = new int*[m+1];

    for(int i = 0; i < m+1; i++)    
        C[i] = new int[n+1];

    for(int i = 0; i < m+1; i++)
        C[i][0] = 0;
    for(int i = 0; i < n+1; i++)
        C[0][i] = 0;
    
    for(int i = 1; i < m+1; i++){
        for(int j = 1; j < n+1; j++){
            if(x[i-1] == y[j-1])
                C[i][j] = C[i-1][j-1]+1;
            else if(C[i-1][j] >= C[i][j-1])
                C[i][j] = C[i-1][j];
            else
                C[i][j] = C[i][j-1];
        }
    }

    return C;
}

void print_lcs(int** M, string x, string y, int i, int j, ofstream &out){
    if(i == 0 || j == 0)
        return;
    if(x[i-1] == y[j-1]){
        print_lcs(M, x, y, i-1, j-1, out);
        out << x[i-1];
    }
    else{
        if(M[i][j-1] >= M[i-1][j])
            print_lcs(M, x, y, i, j-1, out);
        else
            print_lcs(M, x, y, i-1, j, out);
    }
}

void Soluzione(string x, string y, int n, int m, ofstream &out){
    print_lcs(LCSlenght(x, y, n, m), x, y, m, n, out);
    out << endl;
}


int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        int n; in >> n;
        int m; in >> m;
        string x; in >> x;
        string y; in >> y;

        Soluzione(x,y,n,m,out);
    }
}