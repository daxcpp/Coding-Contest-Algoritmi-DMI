//Coded By daxcpp (Davide Carnemolla)
#include <iostream>
#include <fstream>
using namespace std;

template <class H>
class Heap{
  private:
    H* vett;
    int heapsize;

    int left(int i){return i << 1;}
    int right(int i){return (i<<1)|1;}
    int parent(int i){return i >> 1;}
  public:
    Heap(){
      heapsize = 0;
    }

    void Heapify(int i){
      int l = left(i);
      int r = right(i);
      int max = i;

      if(l <= heapsize && vett[l] > vett[max])
        max = l;
      if(r <= heapsize && vett[r] > vett[max])
        max = r;
      if(max != i){
        swap(vett[i], vett[max]);
        Heapify(max);
      } 
    }

    void Build(H* A, int n){
      heapsize = n;
      vett = A;
      for(int i = heapsize/2; i > 0; i--)
        Heapify(i);
    }

    void print(ofstream &out){
      for(int i = 1; i <= heapsize; i++)
        out << vett[i] << "\t";
      out << "\n";
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
      int* vett = new int[200];
      for(int j = 1; j <= n; j++){
        int tmp; in >> tmp;
        vett[j] = tmp;
      }
      t->Build(vett, n);
      t->print(out);
      delete t;
      delete []vett;
    }
    else if(type == "bool"){
      Heap<bool>* t = new Heap<bool>();
      bool* vett = new bool[200];
      for(int j = 1; j <= n; j++){
        bool tmp; in >> tmp;
        vett[j] = tmp;
      }
      t->Build(vett, n);
      t->print(out);
      delete t;
      delete []vett;
    }
    else if(type == "double"){
      Heap<double>* t = new Heap<double>();
      double* vett = new double[200];
      for(int j = 1; j <= n; j++){
        double tmp; in >> tmp;
        vett[j] = tmp;
      }
      t->Build(vett, n);
      t->print(out);
      delete t;
      delete []vett;
    }
    else if(type == "char"){
      Heap<char>* t = new Heap<char>();
      char* vett = new char[200];
      for(int j = 1; j <= n; j++){
        char tmp; in >> tmp;
        vett[j] = tmp;
      }
      t->Build(vett, n);
      t->print(out);
      delete t;
      delete []vett;
    }
  }
}
