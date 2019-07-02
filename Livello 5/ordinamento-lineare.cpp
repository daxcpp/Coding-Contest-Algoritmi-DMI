//Coded By daxcpp (Davide Carnemolla)
#include <iostream>
#include <fstream>
using namespace std;

int findMin(int* vett, int n){
    int min = 1;

    for(int i = 2; i < n; i++)
        if(vett[i] <= vett[min])
            min = i;
    return vett[min];
}

int findMax(int* vett, int n){
    int max = 1;

    for(int i = 2; i <= n; i++)
        if(vett[i] > vett[max])
            max = i;
    return vett[max];
}

template <class H>
void printvett(H* vett, int n, ofstream &out){
    for(int i = 1; i <= n; i++)
        out << vett[i] << " ";
}

template <class H>
H* CountingSort(H* A, int n, ofstream& out){
    int* vett = new int[n+1];

    for(int i = 1; i <= n; i++)
        vett[i] = (int)(A[i]);

    int max = findMax(vett, n);
    int min = findMin(vett, n);

    int k = max - min + 1;

    int C[k+1];

    for(int i = 0; i <= k; i++)
        C[i] = 0;
    
    for(int i = 1; i <= n; i++)
        C[vett[i] - min + 1]++;
    
    for(int i = 2; i <= k; i++)
        C[i] = C[i] + C[i-1];
    
    printvett(C, k-1, out);

    H* B = new H[n+1];

    for(int i = n; i > 0; i--){
        B[C[vett[i]-min+1]] = vett[i];
        C[vett[i]-min+1]--;
    }
    delete [] vett;
    return B;
}

double* CountingSortD(double* A, int n, ofstream &out){
    int* vett = new int[n+1];

    for(int i = 1; i <= n; i++)
        vett[i] = (int)(A[i]*10);

    int max = findMax(vett, n);
    int min = findMin(vett, n);

    int k = max - min + 1;

    int C[k+1];

    for(int i = 0; i <= k; i++)
        C[i] = 0;
    
    for(int i = 1; i <= n; i++)
        C[vett[i] - min + 1]++;
    
    for(int i = 2; i <= k; i++)
        C[i] = C[i] + C[i-1];
    
    printvett(C, k-1, out);

    double* B = new double[n+1];

    for(int i = n; i > 0; i--){
        B[C[vett[i]-min+1]] = vett[i]/10.0;
        C[vett[i]-min+1]--;
    }
    delete [] vett;
    return B;
}



int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        string type; in >> type;
        int n; in >> n;

        out << "0 ";    //CMS bug
        if(type == "int" || type == "bool"){
            int* vett = new int[n+1];

            for(int j = 1; j <= n; j++)
                in >> vett[j];
            
            int* result = CountingSort(vett, n, out);
            printvett(result, n, out);
            delete [] vett;
            delete [] result;
        }
        else if(type == "char"){
            char* vett = new char[n+1];

            for(int j = 1; j <= n; j++)
                in >> vett[j];
            
            char* result = CountingSort(vett, n, out);
            printvett(result, n, out);
            delete [] vett;
            delete [] result;
        }
        else{
            double* vett = new double[n+1];

            for(int j = 1; j <= n; j++)
                in >> vett[j];
            
            double* result = CountingSortD(vett, n, out);
            printvett(result, n, out);
            delete [] vett;
            delete [] result;
        }
        out << endl;
    }
}
