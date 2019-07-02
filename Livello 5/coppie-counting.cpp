//Coded By daxcpp (Davide Carnemolla)
#include <iostream>
#include <fstream>
using namespace std;

template <class H>
class Coppia{
private:
    H x;
    H y;
public:
    Coppia(H _x, H _y): x(_x), y(_y){}

    //Get
    H getX(){return x;}
    H getY(){return y;}

    friend ostream& operator<<(ostream &os, const Coppia &x){
        return os << "(" << x.x << "," << x.y << ")";
    }
};

int findMin(Coppia<int>** vett, int n){
    int min = 1;

    for(int i = 2; i <= n; i++)
        if(vett[i]->getX() < vett[min]->getX())
            min = i;
    return vett[min]->getX();
}

int findMax(Coppia<int>** vett, int n){
    int max = 1;

    for(int i = 2; i <= n; i++)
        if(vett[i]->getX() > vett[max]->getX())
            max = i;
    return vett[max]->getX();
}

void printvett(int* vett, int n, ofstream &out){
    for(int i = 0; i < n; i++)
        out << vett[i] << " ";
}

Coppia<double>** CountingSort(Coppia<double>** A, int n, ofstream &out){
    Coppia<int>** vett = new Coppia<int>*[n+1];

    for(int i = 1; i <= n; i++)
        vett[i] = new Coppia<int>(int(A[i]->getX()*10), int(A[i]->getY()*10));
    
    int max = findMax(vett, n);
    int min = findMin(vett, n);

    int k = max - min +1;

    int C[k+1];

    for(int i = 0; i <= k; i++)
        C[i] = 0;
    
    for(int i = 1; i <= n; i++)
        C[vett[i]->getX() - min +1]++;
    
    for(int i = 2; i <= k; i++)
        C[i] = C[i] + C[i-1];
    
    printvett(C, k, out);

    Coppia<double>** B = new Coppia<double>*[n+1];

    for(int i = n; i > 0; i--){
        B[C[vett[i]->getX() - min +1]] = new Coppia<double>(double(vett[i]->getX()/10.0), double(vett[i]->getY()/10.0));
        C[vett[i]->getX() - min +1]--;
    }

    delete [] vett;
    return B;
}

template <class H>
void printCoppie(Coppia<H>** vett, int n, ofstream &out){
    for(int i = 1; i <= n; i++)
        out << *vett[i] << " ";
    out << endl;
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        int n; in >> n;
        Coppia<double>** vett = new Coppia<double>*[n+1];

        for(int j = 1; j <= n; j++){
            char tmp; in >> tmp;
            double x; in >> x;
            double y; in >> y;
            in >> tmp;
            vett[j] = new Coppia<double>(x,y);
        }

        Coppia<double>** result = CountingSort(vett, n, out);
        printCoppie(result, n, out);

        for(int i = 1; i < n+1; i++){
            delete vett[i];
            delete result[i];
        }

        delete [] vett;
        delete [] result;
    }
}
