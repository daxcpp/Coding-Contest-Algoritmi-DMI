//Coded By daxcpp (Davide Carnemolla)
#include <iostream>
#include <fstream>
using namespace std;

template <class H>
class Heap{
    private:
        H* vett;
        int heapsize;
        int maxdim;
        int chiamate;

        int left(int i){return i << 1;}
        int right(int i){return (i << 1) | 1;}
        int parent(int i){return i >> 1;}
    public:
        Heap(){
            heapsize = 0;
            chiamate = 0;
        }

        void Heapify(int i){
            if(heapsize >= 1)
                chiamate++;
            
            int l = left(i);
            int r = right(i);
            int max = i;

            if(l <= heapsize && vett[l] > vett[max])
                max = l;
            if(r <= heapsize && vett[r] > vett[max])
                max = r;
            
            if(max != i){
                swap(vett[max], vett[i]);
                Heapify(max);
            }
        }

        void buildHeap(H* A, int n){
            vett = A;
            heapsize = n;
            for(int i = heapsize/2; i > 0; i--)
                Heapify(i);
        }

        void extract(){
            swap(vett[1], vett[heapsize]);
            heapsize--;
            Heapify(1);
        }

        void empty(){
            while(heapsize != 0){
                this->extract();
            }
        }  

        void getChiamate(ofstream &out){
            out << chiamate << endl;
        }
};

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

            t->buildHeap(vett, n);
            t->empty();

            t->getChiamate(out);
            delete t;
            delete [] vett;
        }

        if(type == "bool"){
            Heap<bool>* t = new Heap<bool>();
            bool* vett = new bool[n+1];
            for(int j = 1; j <= n; j++){
                bool tmp; in >> tmp;
                vett[j] = tmp;
            }

            t->buildHeap(vett, n);
            t->empty();

            t->getChiamate(out);
            delete t;
            delete [] vett;
        }

        if(type == "double"){
            Heap<double>* t = new Heap<double>();
            double* vett = new double[n+1];
            for(int j = 1; j <= n; j++){
                double tmp; in >> tmp;
                vett[j] = tmp;
            }

            t->buildHeap(vett, n);
            t->empty();
    
            t->getChiamate(out);
            delete t;
            delete [] vett;
        }

        if(type == "char"){
            Heap<char>* t = new Heap<char>();
            char* vett = new char[n+1];
            for(int j = 1; j <= n; j++){
                char tmp; in >> tmp;
                vett[j] = tmp;
            }

            t->buildHeap(vett, n);
            t->empty();

            t->getChiamate(out);
            delete t;
            delete [] vett;
        }
    }
}
