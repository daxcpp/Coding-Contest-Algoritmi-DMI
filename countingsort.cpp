#include <iostream>
#include <fstream>
using namespace std;

int findMax(int* vett, int n){
    int max = 0;

    for(int i = 1; i < n; i++)
        if(vett[i] > vett[max])
            max = i;
    return vett[max];
}

int findMin(int* vett, int n){
    int min = 0;

    for(int i = 1; i < n; i++)
        if(vett[i] < vett[min])
            min = i;
    return vett[min];
}

void printvett(int* vett, int n, ofstream& out){
    for(int i = 0; i < n; i++)
        out << vett[i] << " ";
}


void CountingSort(int* vett, int n, ofstream& out){
    int min = findMin(vett, n);
    int max = findMax(vett, n);
    int k = max - min + 1;

    int C[k];

    for(int i = 0; i < k; i++)
        C[i] = 0;
    
    for(int i = 0; i < n; i++)
        C[vett[i] - min + 1]++;
    
    for(int i = 1; i < k; i++)
        C[i] = C[i] + C[i-1];
    
    printvett(C, k, out);
}

void CountingSort2(int* vett, int n, ofstream& out){
    int min = findMin(vett, n);
    int max = findMax(vett, n);
    int k = max - min + 1;

    int C[k];

    for(int i = 0; i < k; i++)
        C[i] = 0;
    
    for(int i = 0; i < n; i++)
        C[vett[i] - min]++;
    
    
    int j = 0;

    for(int i = 0; i < k; i++){
        while(C[i] > 0){
            vett[j] = i + min;
            C[i]--;
            j++;
        }
    }
    
    printvett(vett, n, out);

    out << endl;
}




int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        int n; in >> n;
        int* vett = new int[n];

        for(int j = 0; j < n; j++)
            in >> vett[j];
        
        CountingSort(vett, n, out);
        CountingSort2(vett, n, out);
    }
}