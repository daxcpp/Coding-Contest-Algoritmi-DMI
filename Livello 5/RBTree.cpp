//Coded By daxcpp (Davide Carnemolla)
#include <iostream>
#include <fstream>
using namespace std;

#define B 0
#define R 1

template <class H>
class Nodo{
private:
    H elemento;
    Nodo<H>* padre;
    Nodo<H>* dx;
    Nodo<H>* sx;
    bool colore;
public:
    Nodo(H x){
        elemento = x;
        padre = dx = sx = NULL;
        colore = R;
    }
    ~Nodo(){
        delete dx;
        delete sx;
    }
    //Get
    H getElemento(){return elemento;}
    Nodo<H>* getPadre(){return padre;}
    Nodo<H>* getDx(){return dx;}
    Nodo<H>* getSx(){return sx;}
    bool getColore(){return colore;}

    //Set
    void setPadre(Nodo<H>* x){padre = x;}
    void setDx(Nodo<H>* x){dx = x;}
    void setSx(Nodo<H>* x){sx = x;}
    void setColore(bool x){colore = x;}

    friend ostream& operator<<(ostream &os, Nodo<H> &a){
        os << "(" << a.elemento << ", ";
        if(a.colore == B)
            os << 'B' << ") ";
        else
            os << 'R' << ") ";
        
        return os;
    }
};

template <class H>
class RBT{
private:
    Nodo<H>* radice;

    void Inorder(Nodo<H>*, ofstream&);
    void Postorder(Nodo<H>*, ofstream&);
    void Preorder(Nodo<H>*, ofstream&);

    void Trapianta(Nodo<H>*, Nodo<H>*);
    void rLeft(Nodo<H>*);
    void rRight(Nodo<H>*);
    void Insert_Fixup(Nodo<H>*);
public:
    RBT(){radice = NULL;}
    ~RBT(){delete radice;}
    
    void Insert(H);
    void Print(string mode, ofstream&);
};

template <class H> void RBT<H>::Inorder(Nodo<H>* ptr, ofstream& out){
    if(ptr != NULL){
        Inorder(ptr->getSx(), out);
        out << *ptr << " ";
        Inorder(ptr->getDx(), out);
    }
}

template <class H> void RBT<H>::Postorder(Nodo<H>* ptr, ofstream &out){
    if(ptr != NULL){
        Postorder(ptr->getSx(), out);
        Postorder(ptr->getDx(), out);
        out << *ptr << " ";
    }
}

template <class H> void RBT<H>::Preorder(Nodo<H>* ptr, ofstream& out){
    if(ptr != NULL){
        out << *ptr << " ";
        Preorder(ptr->getSx(), out);
        Preorder(ptr->getDx(), out);
    }
}

template <class H> void RBT<H>::Trapianta(Nodo<H>* u, Nodo<H>* v){
    if(u->getPadre() == NULL)
        radice = v;
    else if(u->getPadre()->getDx() == u)
        u->getPadre()->setDx(v);
    else
        u->getPadre()->setSx(v);
    
    if(v != NULL)
        v->setPadre(u->getPadre());
}

template <class H> void RBT<H>::rLeft(Nodo<H>* y){
     if(y != NULL){
        Nodo<H>* x = y->getDx();
        
        if(x != NULL){
            y->setDx(x->getSx());

            if(y->getDx() != NULL)
                y->getDx()->setPadre(y);
            
            Trapianta(y, x);

            x->setSx(y);
            y->setPadre(x);
        }
     }
}

template <class H> void RBT<H>::rRight(Nodo<H>* y){
    if(y != NULL ){
        Nodo<H>* x = y->getSx();

        if(x != NULL){
            y->setSx(x->getDx());

            if(y->getSx() != NULL)
                y->getSx()->setPadre(y);
            
            Trapianta(y, x);

            x->setDx(y);
            y->setPadre(x);
        }
    }
}

template <class H> void RBT<H>::Insert(H x){
    Nodo<H>* nuovo = new Nodo<H>(x);

    Nodo<H>* iter = radice;
    Nodo<H>* tmp = NULL;

    while(iter != NULL){
        tmp = iter;

        if(x > iter->getElemento())
            iter = iter->getDx();
        else
            iter = iter->getSx();
    }

    nuovo->setPadre(tmp);

    if(tmp == NULL)
        radice = nuovo;
    else if(x > tmp->getElemento())
        tmp->setDx(nuovo);
    else
        tmp->setSx(nuovo);
    
    Insert_Fixup(nuovo);
}

template <class H> void RBT<H>::Insert_Fixup(Nodo<H>* z){
    if(z->getPadre() != NULL && z->getPadre()->getColore() == B)
        return;
    if(z == radice){
        z->setColore(B);
        return;
    }
    Nodo<H>* padre = z->getPadre();
    Nodo<H>* nonno = padre->getPadre();
    Nodo<H>* zio = nonno->getDx();
    if(nonno->getDx() == padre)
        zio = nonno->getSx();
    
    if(zio != NULL && zio->getColore() == R){
        zio->setColore(B);
        padre->setColore(B);
        nonno->setColore(R);
        Insert_Fixup(nonno);
        return;
    }

    if(padre == nonno->getSx()){
        if(z == padre->getDx()){
            rLeft(padre);
            padre = z;
            z = padre->getSx();
        }

        rRight(nonno);
        padre->setColore(B);
        nonno->setColore(R);
        return;
    }
    else{
        if(z == padre->getSx()){
            rRight(padre);
            padre = z;
            z = padre->getDx();
        }

        padre->setColore(B);
        nonno->setColore(R);
        rLeft(nonno);
        return;
    }
}

template <class H> void RBT<H>::Print(string mode, ofstream &out){
    if(mode == "inorder")
        Inorder(radice, out);
    else if(mode == "preorder")
        Preorder(radice, out);
    else
        Postorder(radice, out);
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        string type; in >> type;
        int n; in >> n;
        string mode; in >> mode;

        if(type == "int" || type == "bool"){
            RBT<int>* t = new RBT<int>();

            for(int j = 0; j < n; j++){
                int tmp; in >> tmp;
                t->Insert(tmp);
            }

            t->Print(mode, out);
            delete t;
        }
        else if(type == "char"){
            RBT<char>* t = new RBT<char>();

            for(int j = 0; j < n; j++){
                char tmp; in >> tmp;
                t->Insert(tmp);
            }

            t->Print(mode, out);
            delete t;
        }
        else{
            RBT<double>* t = new RBT<double>();

            for(int j = 0; j < n; j++){
                double tmp; in >> tmp;
                t->Insert(tmp);
            }

            t->Print(mode, out);
            delete t;
        }
        out << endl;
    }
}
