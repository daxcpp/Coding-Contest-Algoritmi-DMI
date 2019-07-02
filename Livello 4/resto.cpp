//Coded By daxcpp (Davide Carnemolla)
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

int minCoin(int* vett, int n, int r){
    int table[r+1];

    table[0] = 0;

    for(int i = 1; i < r+1; i++)
        table[i] = INT_MAX;
    
    for(int i = 1; i < r+1; i++){
        for(int j = 0; j < n; j++){
            if(vett[j] <= i){
                int sub_res = table[i - vett[j]];
                if(sub_res != INT_MAX && sub_res + 1 < table[i])
                    table[i] = sub_res + 1;
            }
        }
    }

    return table[r];
}


int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        int r; in >> r;
        int n; in >> n;

        int* vett = new int[n];

        for(int j = 0; j < n; j++)
            in >> vett[j];

        out << minCoin(vett, n, r) << endl;

        delete [] vett;
    }
}
