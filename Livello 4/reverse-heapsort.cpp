//Coded By daxcpp (Davide Carnemolla)
#include <iostream>
#include <fstream>
using namespace std;

template <class H>
class Heap{
    private:
        H* vett;
        int heapsize;
        int chiamate;

        int left(int i){return i << 1;}
        int right(int i){return (i << 1) | 1;}
        int parent(int i){return i >> 1;}
    public:
        Heap(){
            heapsize = 0;
            chiamate = 0;
        }

        ~Heap(){delete [] vett;}

        void Heapify(int i){
            if(heapsize >= 1)
                chiamate++;
            int l = left(i);
            int r = right(i);
            int min = i;

            if(l <= heapsize && vett[l] < vett[min])
                min = l;
            if(r <= heapsize && vett[r] < vett[min])
                min = r;
            
            if(min != i){
                swap(vett[min], vett[i]);
                Heapify(min);
            }
        }

        void Build(H* A, int n){
            vett = A;
            heapsize = n;

            for(int i = heapsize/2; i > 0; i--)
                Heapify(i);
        }

        H extract(){
            swap(vett[1], vett[heapsize]);
            heapsize--;
            Heapify(1);

            return vett[heapsize+1];
        }

        int getChiamate(){return chiamate;}
};

template <class H>
void printvett(H* vett, int n, ofstream& out){
    for(int i = 1; i <= n; i++)
        out << vett[i] << " ";
    out << endl;
}


int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        string type; in >> type;
        int n; in >> n;

        if(type == "int"){
            Heap<int>* t = new Heap<int>();
            int* vett = new int[n+1];
            for(int j = 1; j <= n; j++){
                int tmp; in >> tmp;
                vett[j] = tmp;
            }

            t->Build(vett, n);
            int* A = new int[n+1];

            for(int i = n; i > 0; i--)
                A[i] =  t->extract();

            out << t->getChiamate() << " ";
            printvett(A, n, out);

            delete t;
            delete []vett;
            delete [] A;
        }

        if(type == "bool"){
            Heap<bool>* t = new Heap<bool>();
            bool* vett = new bool[n+1];
            for(int j = 1; j <= n; j++){
                bool tmp; in >> tmp;
                vett[j] = tmp;
            }

            t->Build(vett, n);
            bool* A = new bool[n+1];
            for(int i = n; i > 0; i--)
                A[i] = t->extract();

            out << t->getChiamate() << " ";
            printvett(A, n, out);

            delete t;
            delete []vett;
            delete [] A;
        }

        if(type == "double"){
            Heap<double>* t = new Heap<double>();
            double* vett = new double[n+1];
            for(int j = 1; j <= n; j++){
                double tmp; in >> tmp;
                vett[j] = tmp;
            }

            t->Build(vett, n);
            double* A = new double[n+1];
            for(int i = n; i > 0; i--)
                A[i] = t->extract();
            
            out << t->getChiamate() << " ";
            printvett(A, n, out);

            delete t;
            delete []vett;
            delete [] A;
        }

        if(type == "char"){
            Heap<char>* t = new Heap<char>();
            char* vett = new char[n+1];

            for(int j = 1; j <= n; j++){
                char tmp; in >> tmp;
                vett[j] = tmp;
            }

            t->Build(vett, n);
            char* A = new char[n+1];
            for(int i = n; i > 0; i--)
                A[i] = t->extract();

            out << t->getChiamate() << " ";
            printvett(A, n, out);

            delete t;
            delete []vett;
            delete [] A;
        }
    }
}
