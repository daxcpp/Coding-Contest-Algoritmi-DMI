//Coded By daxcpp (Davide Carnemolla)
#include <iostream>
#include <fstream>
using namespace std;


void Edit(string x, string y, int m, int n, ofstream &out){
    int C[m+1][n+1];

    for(int i = 0; i < m+1; i++)
        C[i][0] = i;
    for(int i = 0; i < n+1; i++)
        C[0][i] = i;
    
    for(int i = 1; i < m+1; i++){
        for(int j = 1; j < n+1; j++){
            if(x[i-1] != y[j-1])
                C[i][j] = min(min(C[i][j-1], C[i-1][j]), C[i-1][j-1]) + 1;
            else
                C[i][j] = C[i-1][j-1];
        }
    }
    out << C[m][n] << endl;
}




int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        int m; in >> m;
        int n; in >> n;
        string x; in >> x;
        string y; in >> y;

        Edit(x, y, m, n, out);

    }
}
