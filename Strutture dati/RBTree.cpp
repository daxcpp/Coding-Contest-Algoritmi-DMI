#include <iostream>
using namespace std;


template <class H>
class Nodo{
private:
    H key;
    Nodo<H>* parent;
    Nodo<H>* dx;
    Nodo<H>* sx;
    char colore;
public:
    Nodo(H x){
        key = x;
        parent = NULL;
        dx = NULL;
        sx = NULL;
        colore = 'R';
    }

    //Get
    H getkey(){return key;}
    Nodo<H>* getParent(){return parent;}
    Nodo<H>* getDx(){return dx;}
    Nodo<H>* getSx(){return sx;}
    char getColore(){return colore;}

    //Set
    void setparent(Nodo<H>* x){parent = x;}
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
        cout << "(" << ptr->getkey() << " " << ptr->getColore() << ")" << " ";
        Inorder(ptr->getDx());
    }
}

template <class H> void RBT<H>::Postorder(Nodo<H>* ptr){
    if(ptr != NULL){
        Postorder(ptr->getSx());
        Postorder(ptr->getDx());
        cout << ptr->getkey() << "\t";
    }
}

template <class H> void RBT<H>::Preorder(Nodo<H>* ptr){
    if(ptr != NULL){
        cout << ptr->getkey() << "\t";
        Preorder(ptr->getSx());
        Preorder(ptr->getDx());
    }
}

template <class H> void RBT<H>::rLeft(Nodo<H>* y){
     if(y != NULL){
        Nodo<H>* x = y->getDx();
        Nodo<H>* z = y->getParent();

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

        x->setparent(z);
        y->setparent(x);

        if(y->getDx())
            y->getDx()->setparent(y); 
    }
}

template <class H> void RBT<H>::rRight(Nodo<H>* y){
    if(y != NULL ){
        Nodo<H>* x = y->getSx();
        Nodo<H>* z = y->getParent();

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
        
        x->setparent(z);
        y->setparent(x);

        if(y->getSx())
            y->getSx()->setparent(y);
    }
}

template <class H> RBT<H>* RBT<H>::Insert(H x){
    Nodo<H>* nuovo = new Nodo<H>(x);

    Nodo<H>* iter = radice;
    Nodo<H>* tmp = NULL;

    while(iter != NULL){
        tmp = iter;

        if(x > iter->getkey())
            iter = iter->getDx();
        else
            iter = iter->getSx();
    }

    nuovo->setparent(tmp);

    if(tmp == NULL)
        radice = nuovo;
    else if(x > tmp->getkey())
        tmp->setDx(nuovo);
    else
        tmp->setSx(nuovo);
    
    this->Insert_Fix(nuovo);
    
    return this;
}

template <class H> void RBT<H>::Insert_Fix(Nodo<H>* z){
    if(z->getParent() != NULL && z->getParent()->getColore() == 'B')
        return;
    if(z == radice){
        z->setColore('B');
        return;
    }
    Nodo<H>* parent = z->getParent();
    Nodo<H>* nonno = parent->getParent();
    Nodo<H>* zio = nonno->getDx();
    if(nonno->getDx() == parent)
        zio = nonno->getSx();
    
    if(zio != NULL && zio->getColore() == 'R'){
        zio->setColore('B');
        parent->setColore('B');
        nonno->setColore('R');
        this->Insert_Fix(nonno);
        return;
    }

    if(parent == nonno->getSx()){
        if(z == parent->getDx()){
            this->rLeft(parent);
            parent = z;
            z = parent->getSx();
        }

        this->rRight(nonno);
        parent->setColore('B');
        nonno->setColore('R');
        return;
    }
    else{
        if(z == parent->getSx()){
            this->rRight(parent);
            parent = z;
            z = parent->getDx();
        }

        parent->setColore('B');
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