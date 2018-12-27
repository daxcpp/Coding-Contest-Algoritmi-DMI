#include <iostream>
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

    void Inorder(Nodo<H>*);
    void Postorder(Nodo<H>*);
    void Preorder(Nodo<H>*);
public:
    RBT(){radice = NULL;}

    void rLeft(Nodo<H>*);
    void rRight(Nodo<H>*);
    RBT<H>* Insert(H);
    void Insert_Fix(Nodo<H>*);
    void Print();
};

template <class H> void RBT<H>::Inorder(Nodo<H>* ptr){
    if(ptr != NULL){
        Inorder(ptr->getSx());
        cout << "(" << ptr->getElemento() << " " << ptr->getColore() << ")" << " ";
        Inorder(ptr->getDx());
    }
}

template <class H> void RBT<H>::Postorder(Nodo<H>* ptr){
    if(ptr != NULL){
        Postorder(ptr->getSx());
        Postorder(ptr->getDx());
        cout << ptr->getElemento() << "\t";
    }
}

template <class H> void RBT<H>::Preorder(Nodo<H>* ptr){
    if(ptr != NULL){
        cout << ptr->getElemento() << "\t";
        Preorder(ptr->getSx());
        Preorder(ptr->getDx());
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

template <class H> void RBT<H>::Print(){
    Inorder(radice);
    cout << endl;
}



int main(){
    RBT<int>* t = new RBT<int>();

    t->Insert(40)->Insert(34)->Insert(7)->Insert(81)->Insert(90)->Insert(79)->Insert(36)->Insert(78)->Insert(4)->Insert(67)->Insert(45)->Insert(4)->Insert(77);
    t->Print();
}