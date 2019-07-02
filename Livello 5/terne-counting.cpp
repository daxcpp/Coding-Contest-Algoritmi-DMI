//Coded By daxcpp (Davide Carnemolla)
#include <iostream>
#include <fstream>
using namespace std;

template <class H>
class Terna{
private:
    H x;
    H y;
    H z;
public:
    Terna(H _x, H _y, H _z): x(_x), y(_y), z(_z){}
    Terna(Terna<double> &t){
        this->x = int(t.getX()*10);
        this->y = int(t.getY()*10);
        this->z = int(t.getZ()*10);
    }

    Terna(Terna<int> &t){
        this->x = double(t.getX()/10.0);
        this->y = double(t.getY()/10.0);
        this->z = double(t.getZ()/10.0);
    }

    //Get
    H getX(){return x;}
    H getY(){return y;}
    H getZ(){return z;}

    friend ostream& operator<<(ostream &os, const Terna &x){
        return os << "(" << x.x << "," << x.y << "," << x.z << ")";
    }
};

int findMin(Terna<int>** vett, int n){
    int min = 1;

    for(int i = 2; i <= n; i++)
        if(vett[i]->getX() < vett[min]->getX())
            min = i;
    return vett[min]->getX();
}

int findMax(Terna<int>** vett, int n){
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

Terna<double>** CountingSort(Terna<double>** A, int n, ofstream &out){
    Terna<int>** vett = new Terna<int>*[n+1];

    for(int i = 1; i <= n; i++)
        vett[i] = new Terna<int>(*A[i]);
    
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

    Terna<double>** B = new Terna<double>*[n+1];
    
    for(int i = n; i > 0; i--){
        B[C[vett[i]->getX() - min +1]] = new Terna<double>(*vett[i]);
        C[vett[i]->getX() - min +1]--;
    }

    delete [] vett;
    return B;
} 

template <class H>
void printTerne(Terna<H>** vett, int n, ofstream& out){
    for(int i = 1; i <= n; i++)
        out << *vett[i] << " ";
    out << endl;
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        int n; in >> n;
        Terna<double>** vett = new Terna<double>*[n+1];

        for(int j = 1; j <= n; j++){
            char tmp; in >> tmp;
            double x; in >> x;
            double y; in >> y;
            double z; in >> z;
            in >> tmp;
            vett[j] = new Terna<double>(x,y,z);
        }

        Terna<double>** result = CountingSort(vett, n, out);
        printTerne(result, n, out);

        for(int i = 1; i < n+1; i++){
            delete vett[i];
            delete result[i];
        }

        delete [] vett;
        delete [] result;
    }
}
