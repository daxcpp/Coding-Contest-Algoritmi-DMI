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
    Heap(int x): maxdim(x){
        heapsize = 0;
        vett = new H[maxdim];
        chiamate = 0;
    }

    ~Heap(){delete [] vett;}

    int getChiamate(){return chiamate;}

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

    void enqueue(H x){
        heapsize++;
        vett[heapsize] = x;

        int i = heapsize;
        while(i > 1 && vett[parent(i)] > vett[i]){
            swap(vett[parent(i)], vett[i]);
            i = parent(i);
        }
    }

    void extract(){
        swap(vett[1], vett[heapsize]);
        heapsize--;
        Heapify(1);
    }

    void print(ofstream &out){
        for(int i = 1; i <= heapsize; i++)
            out << vett[i] << " ";
        out << endl;
    }
};



int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        string type; in >> type;
        int n; in >> n;

        if(type == "int"){
            Heap<int>* t = new Heap<int>(n*2);

            for(int j = 0; j < n; j++){
                string tmp; in >> tmp;
               
                if(tmp == "extract")
                    t->extract();
                
                else{
                    string _val = tmp.substr(2, tmp.length());
                    int val = stoi(_val);
                    t->enqueue(val);
                }
            }
            out << t->getChiamate() << " ";
            t->print(out);
            delete t;
        }

        if(type == "bool"){
            Heap<bool>* t = new Heap<bool>(n*2);

            for(int j = 0; j < n; j++){
                string tmp; in >> tmp;

                if(tmp == "extract")
                    t->extract();
                else{
                    string _val = tmp.substr(2, tmp.length());
                    bool val = stoi(_val);
                    t->enqueue(val);
                }
            }
            out << t->getChiamate() << " ";
            t->print(out);
            delete t;
        }

        if(type == "double"){
            Heap<double>* t = new Heap<double>(n*2);

            for(int j = 0; j < n; j++){
                string tmp; in >> tmp;

                if(tmp == "extract")
                    t->extract();
                else{
                    string _val = tmp.substr(2, tmp.length());
                    double val = stod(_val);
                    t->enqueue(val);
                }
            }
            out << t->getChiamate() << " ";
            t->print(out);
            delete t;
        }

        if(type == "char"){
            Heap<char>* t = new Heap<char>(n*2);

            for(int j = 0; j < n; j++){
                string tmp; in >> tmp;

                if(tmp == "extract")
                    t->extract();
                else{
                    
                    char val = tmp[2];
                    t->enqueue(val);
                }
            }
            out << t->getChiamate() << " ";
            t->print(out);
            delete t;
        }
    }
    cout << endl;
}
