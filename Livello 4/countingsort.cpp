//Coded By daxcpp (Davide Carnemolla)
#include <iostream>
#include <fstream>
using namespace std;


int findMax(int* vett, int n){
    int max = 1;

    for(int i = 2; i <= n; i++)
        if(vett[i] > vett[max])
            max = i;
    return vett[max];
}

int findMin(int* vett, int n){
    int min = 1;

    for(int i = 2;i <= n; i++)
        if (vett[i] < vett[min])
            min = i;
    return vett[min];
}

template <class H>
void printvett(H* vett, int n, ofstream &out){
    for(int i = 1; i <= n; i++)
        out << vett[i] << " ";
}

int* CountingSort(int* vett, int n, ofstream &out){
    int max = findMax(vett, n);
    int min = findMin(vett, n);

    int k = max - min +1;

    int C[k+1];

    for(int i = 0; i <= k; i++)
        C[i] = 0;
    
    for(int i = 1; i <= n; i++)
        C[vett[i] - min +1]++;
    
    for(int i = 2; i <= k; i++)
        C[i] = C[i] + C[i-1];
    
    printvett(C, k-1, out);

    int *B = new int[n+1];

    for(int i = n; i > 0; i--){
        B[C[vett[i] - min +1]] = vett[i];
        C[vett[i] - min +1]--;
    }
    
    return B;
}




int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        string type; in >> type;
        int n; in >> n;
        int* vett = new int[n+1];

        for(int j = 1; j <= n; j++)
            in >> vett[j];
        vett = CountingSort(vett, n, out);
        printvett(vett, n, out);
        delete [] vett;
   
        out << endl;
}
