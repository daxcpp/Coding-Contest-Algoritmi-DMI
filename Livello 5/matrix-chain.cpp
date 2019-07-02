//Coded By daxcpp (Davide Carnemolla)
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

int MatrixChain(int* vett, int n){
    int m[n][n];

    for(int i = 1; i < n; i++)
        m[i][i] = 0;
    
    for(int l = 2; l < n; l++){
        for(int i = 1; i < n-l+1;i++){
            int j = i+l-1;

            m[i][j] = INT_MAX;

            for(int k = i; k <= j-1; k++){
                int q = m[i][k] + m[k+1][j] + vett[i-1]*vett[k]*vett[j];

                if(q < m[i][j])
                    m[i][j] = q;
            }
        }
    }

   
    return m[1][n-1];
}


int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        int n; in >> n;
        int* vett = new int[n+1];
        int r, c;

        for(int j = 0; j < n; j++){
            char tmp; in >> tmp;
            in >> r;
            in >> tmp;
            in >> c;
            in >> tmp;
            vett[j] = r;
        }
        vett[n] = c;

        
        out << MatrixChain(vett, n+1) << endl;

        delete [] vett;
    }
}


        

