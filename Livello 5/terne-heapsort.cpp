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
    Terna(H x, H y, H z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    friend bool operator>(Terna &a, Terna &b){
        if(a.x > b.x)
            return 1;
        else if(a.x == b.x && a.y > b.y)
            return 1;
        else if(a.x == b.x && a.y == b.y && a.z > b.z)
            return 1;
        return 0;
    }

    friend ostream& operator<<(ostream &os, Terna &a){
        return os << "(" << a.x << " " << a.y << " " << a.z << ")";
    }
};

template <class H>
class Heap{
private:
    Terna<H>** vett;
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

    void Build(Terna<H>** vett, int n){
        this->vett = vett;
        heapsize = n;

        for(int i = heapsize/2; i > 0; i--)
            Heapify(i);
    }

    Terna<H>* extract(){
        swap(vett[1], vett[heapsize]);
        heapsize--;
        Heapify(1);

        return vett[heapsize+1];
    }

    int getChiamate(){return chiamate;}
};

template <class H>
void printvett(Terna<H>** vett, int n, ostream &out){
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
            Terna <int>** vett = new Terna <int>*[n+1];
            Heap<int>* t = new Heap<int>();
            for(int j = 1; j <= n; j++){
                char tmp; in >> tmp;
                int x; in >> x;
                int y; in >> y;
                int z; in >> z;
                in >> tmp;
                vett[j] = new Terna <int>(x, y,z);
            }
            Terna <int>** vettordinato = new Terna<int>*[n+1];
            t->Build(vett, n);
            for(int j = n; j > 0; j--)
            vettordinato[j] = t->extract();

            out << t->getChiamate() << " ";
            printvett(vettordinato, n, out);

            for(int i = 0; i < n+1; i++)
                delete vett[i];
            delete [] vett;
            delete t;
        }
        else if(type == "double"){
            Terna <double>** vett = new Terna <double>*[n+1];
            Heap<double>* t = new Heap<double>();
            for(int j = 1; j <= n; j++){
                char tmp; in >> tmp;
                double x; in >> x;
                double y; in >> y;
                double z; in >> z;
                in >> tmp;
                vett[j] = new Terna <double>(x, y, z);
            }
            Terna <double>** vettordinato = new Terna<double>*[n+1];
            t->Build(vett, n);
            for(int j = n; j > 0; j--)
                vettordinato[j] = t->extract();

            out << t->getChiamate() << " ";
            printvett(vettordinato, n, out);

            for(int i = 0; i < n+1; i++)
                delete vett[i];
            delete [] vett;
            delete t;
        }
        else if(type == "char"){
                Terna <char>** vett = new Terna <char>*[n+1];
                Heap<char>* t = new Heap<char>();
                for(int j = 1; j <= n; j++){
                    char tmp; in >> tmp;
                    char x; in >> x;
                    char y; in >> y;
                    char z; in >> z;
                    in >> tmp;
                    vett[j] = new Terna <char>(x, y, z);
                }
                Terna <char>** vettordinato = new Terna<char>*[n+1];
                t->Build(vett, n);
                for(int j = n; j > 0; j--)
                vettordinato[j] = t->extract();

                out << t->getChiamate() << " ";
                printvett(vettordinato, n, out);

                for(int i = 0; i < n+1; i++)
                    delete vett[i];
                delete [] vett;
                delete t;
        }

    }
}
