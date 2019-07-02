//Coded By daxcpp (Davide Carnemolla)
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


void Knapsack(vector<int> vett, int pmax, ostream &out){
    int sum = 0;
    sort(vett.begin(), vett.end(), greater<int>());

    for(int i = 0; i < pmax; i++)
        sum += vett[i];
    
    out << sum << endl;
}


int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");


    for(int i = 0; i < 100; i++){
        int n; in >> n;
        int pmax; in >> pmax;

        vector<int> vett;

        for(int j = 0; j < n; j++){
            int tmp; in >> tmp;
            vett.push_back(tmp);
        }

        Knapsack(vett, pmax, out);

        vett.~vector();
    }
}
