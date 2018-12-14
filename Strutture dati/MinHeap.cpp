//MinHeap
#include <iostream>
using namespace std;

template <class H>
class Heap{
protected:
    H* vett;
    int heapsize;
    int maxdim;
    int chiamate;

    int left(int i){return i << 1;}
    int right(int i){return (i << 1) | 1;}
    int parent(int i){return i >> 1;}
public:
    Heap(int maxdim){
        this->maxdim = maxdim;
        this->heapsize = 0;
        this->chiamate = 0;
        vett = new H[maxdim];
    }

    int getChiamate(){return chiamate;}

    void Heapify(int);
    Heap<H>* Enqueue(H);
    H Extract();
    void Build(H*, int);
    void Empty();
    void Print();
};

template <class H> void Heap<H>::Heapify(int i){
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

template <class H> Heap<H>* Heap<H>::Enqueue(H x){
    heapsize++;
    vett[heapsize] = x;

    int i = heapsize;

    while(i > 0 && vett[parent(i)] > vett[i]){
        swap(vett[parent(i)], vett[i]);
        i = parent(i);
    }
    return this;
}

template <class H> H Heap<H>::Extract(){
    swap(vett[1], vett[heapsize]);
    heapsize--;
    Heapify(1);

    return vett[heapsize+1];
}

template <class H> void Heap<H>::Build(H* vett, int n){
    heapsize = n;
    this->vett = vett;

    for(int i = heapsize/2; i > 0; i--)
        Heapify(i);
}

template <class H> void Heap<H>::Empty(){
    while(heapsize != 0)
        this->Extract();
}

template <class H> void Heap<H>::Print(){
    for(int i = 1; i < heapsize+1; i++)
        cout << vett[i] << "\t";
    cout << endl;
}

int main(){
    Heap<int>* t = new Heap<int>(10);

    t->Enqueue(10)->Enqueue(0)->Enqueue(11)->Enqueue(9)->Extract();
    t->Print();
    t->Empty();
    t->Print();


}