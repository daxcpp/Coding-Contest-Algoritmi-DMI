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
    Coppia(H x, H y){
        this->x = x;
        this->y = y;
    }

    friend bool operator>(Coppia &a, Coppia &b){
        if(a.x > b.x)
            return 1;
        else if(a.x == b.x && a.y > b.y)
            return 1;
        return 0;
    }

    friend ostream& operator<<(ostream &os, Coppia &a){
        return os << "(" << a.x << " " << a.y << ")";
    }
};


template <class H>
class Heap{
private:
    Coppia <H>** vett;
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

    void Heapify(int i){
        if(heapsize >= 1)
            chiamate++;
        int l = left(i);
        int r = right(i);
        int max = i;

        if(l <= heapsize && *vett[l] > *vett[max])
            max = l;
        if(r <= heapsize && *vett[r] > *vett[max])
            max = r;

        if(max != i){
            swap(vett[max], vett[i]);
            Heapify(max);
        }
    }

    void Build(Coppia<H>** vett, int n){
        this->vett = vett;
        heapsize = n;

        for(int i = heapsize/2; i > 0; i--)
            Heapify(i);
    }

    Coppia <H>* extract(){
        swap(vett[1], vett[heapsize]);
        heapsize--;
        Heapify(1);

        return vett[heapsize+1];
    }

    int getChiamate(){return chiamate;}
};

template <class H>
void printvett(Coppia<H>** vett, int n, ostream &out){
    for(int i = 1; i <= n; i++)
        out << *vett[i] << " ";
    out << endl;
}


int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        string type; in >> type;
        int n; in >> n;

        if(type == "int" || type == "bool"){
            Coppia <int>** vett = new Coppia <int>*[n+1];
            Heap<int>* t = new Heap<int>();
            for(int j = 1; j <= n; j++){
                char tmp; in >> tmp;
                int x; in >> x;
                int y; in >> y;
                in >> tmp;
                vett[j] = new Coppia <int>(x, y);
            }
            Coppia <int>** vettordinato = new Coppia<int>*[n+1];
            t->Build(vett, n);
            for(int j = n; j > 0; j--)
            vettordinato[j] = t->extract();

            out << t->getChiamate() << " ";
            printvett(vettordinato, n, out);
        }
        else if(type == "double"){
            Coppia <double>** vett = new Coppia <double>*[n+1];
            Heap<double>* t = new Heap<double>();
            for(int j = 1; j <= n; j++){
                char tmp; in >> tmp;
                double x; in >> x;
                double y; in >> y;
                in >> tmp;
                vett[j] = new Coppia <double>(x, y);
            }
            Coppia <double>** vettordinato = new Coppia<double>*[n+1];
            t->Build(vett, n);
            for(int j = n; j > 0; j--)
                vettordinato[j] = t->extract();

            out << t->getChiamate() << " ";
            printvett(vettordinato, n, out);
        }
        else if(type == "char"){
                Coppia <char>** vett = new Coppia <char>*[n+1];
                Heap<char>* t = new Heap<char>();
                for(int j = 1; j <= n; j++){
                    char tmp; in >> tmp;
                    char x; in >> x;
                    char y; in >> y;
                    in >> tmp;
                    vett[j] = new Coppia <char>(x, y);
                }
                Coppia <char>** vettordinato = new Coppia<char>*[n+1];
                t->Build(vett, n);
                for(int j = n; j > 0; j--)
                vettordinato[j] = t->extract();

                out << t->getChiamate() << " ";
                printvett(vettordinato, n, out);
        }

    }
}
