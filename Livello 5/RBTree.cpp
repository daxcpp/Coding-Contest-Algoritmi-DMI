#include <iostream>
#include <fstream>
using namespace std;


template <class H>
class Nodo{
private:
    H elemento;
    Nodo<H>* padre;
    Nodo<H>* dx;
    Nodo<H>* sx;
    char colore;
public:
    Nodo(H x){
        elemento = x;
        padre = NULL;
        dx = NULL;
        sx = NULL;
        colore = 'R';
    }

    //Get
    H getElemento(){return elemento;}
    Nodo<H>* getPadre(){return padre;}
    Nodo<H>* getDx(){return dx;}
    Nodo<H>* getSx(){return sx;}
    char getColore(){return colore;}

    //Set
    void setPadre(Nodo<H>* x){padre = x;}
    void setDx(Nodo<H>* x){dx = x;}
    void setSx(Nodo<H>* x){sx = x;}
    void setColore(char x){colore = x;}
};

template <class H>
class RBT{
private:
    Nodo<H>* radice;

    void Inorder(Nodo<H>*, ofstream&);
    void Postorder(Nodo<H>*, ofstream&);
    void Preorder(Nodo<H>*, ofstream&);
public:
    RBT(){radice = NULL;}

    void rLeft(Nodo<H>*);
    void rRight(Nodo<H>*);
    RBT<H>* Insert(H);
    void Insert_Fix(Nodo<H>*);
    void Print(string mode, ofstream&);
};

template <class H> void RBT<H>::Inorder(Nodo<H>* ptr, ofstream& out){
    if(ptr != NULL){
        Inorder(ptr->getSx(), out);
        out << "(" << ptr->getElemento() << "," << ptr->getColore() << ") ";
        Inorder(ptr->getDx(), out);
    }
}

template <class H> void RBT<H>::Postorder(Nodo<H>* ptr, ofstream &out){
    if(ptr != NULL){
        Postorder(ptr->getSx(), out);
        Postorder(ptr->getDx(), out);
        out << "(" << ptr->getElemento() << "," << ptr->getColore() << ") ";
    }
}

template <class H> void RBT<H>::Preorder(Nodo<H>* ptr, ofstream& out){
    if(ptr != NULL){
        out << "(" << ptr->getElemento() << "," << ptr->getColore() << ") ";
        Preorder(ptr->getSx(), out);
        Preorder(ptr->getDx(), out);
    }
}

template <class H> void RBT<H>::rLeft(Nodo<H>* y){
     if(y != NULL){
        Nodo<H>* x = y->getDx();
        Nodo<H>* z = y->getPadre();

        y->setDx(x->getSx());
        x->setSx(y);

        if(z != NULL){
            if(y == z->getDx())
                z->setDx(x);
            else
                z->setSx(x);
        }
        else
            radice = x;

        x->setPadre(z);
        y->setPadre(x);

        if(y->getDx())
            y->getDx()->setPadre(y); 
    }
}

template <class H> void RBT<H>::rRight(Nodo<H>* y){
    if(y != NULL ){
        Nodo<H>* x = y->getSx();
        Nodo<H>* z = y->getPadre();

        y->setSx(x->getDx());
        x->setDx(y);

        if(z != NULL){
            if(y == z->getSx())
                z->setSx(x);
            else
                z->setDx(x);
        }
        else
            radice = x;
        
        x->setPadre(z);
        y->setPadre(x);

        if(y->getSx())
            y->getSx()->setPadre(y);
    }
}

template <class H> RBT<H>* RBT<H>::Insert(H x){
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
    
    this->Insert_Fix(nuovo);
    
    return this;
}

template <class H> void RBT<H>::Insert_Fix(Nodo<H>* z){
    if(z->getPadre() != NULL && z->getPadre()->getColore() == 'B')
        return;
    if(z == radice){
        z->setColore('B');
        return;
    }
    Nodo<H>* padre = z->getPadre();
    Nodo<H>* nonno = padre->getPadre();
    Nodo<H>* zio = nonno->getDx();
    if(nonno->getDx() == padre)
        zio = nonno->getSx();
    
    if(zio != NULL && zio->getColore() == 'R'){
        zio->setColore('B');
        padre->setColore('B');
        nonno->setColore('R');
        this->Insert_Fix(nonno);
        return;
    }

    if(padre == nonno->getSx()){
        if(z == padre->getDx()){
            this->rLeft(padre);
            padre = z;
            z = padre->getSx();
        }

        this->rRight(nonno);
        padre->setColore('B');
        nonno->setColore('R');
        return;
    }
    else{
        if(z == padre->getSx()){
            this->rRight(padre);
            padre = z;
            z = padre->getDx();
        }

        padre->setColore('B');
        nonno->setColore('R');
        this->rLeft(nonno);
        return;
    }
}

template <class H> void RBT<H>::Print(string mode, ofstream &out){
    if(mode == "inorder")
        this->Inorder(radice, out);
    else if(mode == "preorder")
        this->Preorder(radice, out);
    else
        this->Postorder(radice, out);
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