//Coded By daxcpp (Davide Carnemolla)
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
public:
    Nodo(H el): elemento(el){
        padre = NULL;
        dx = NULL;
        sx = NULL;
    }

    //Set
    void setPadre(Nodo<H>* x){padre = x;}
    void setDx(Nodo<H>* x){dx = x;}
    void setSx(Nodo<H>* x){sx = x;}

    //Get
    H getElemento(){return elemento;}
    Nodo<H>* getPadre(){return padre;}
    Nodo<H>* getDx(){return dx;}
    Nodo<H>* getSx(){return sx;}
};

template <class H>
class BST{
private:
    Nodo<H>* radice;

    void Trapianta(Nodo<H>*, Nodo<H>*);
    void Preorder(Nodo<H>*, ofstream&);
    void Inorder(Nodo<H>*,ofstream&);
    void Postorder(Nodo<H>*,ofstream&);
public:
    BST(){radice = NULL;}

    void Insert(H);
    void Canc(H);
    Nodo<H>* Search(H);
    Nodo<H>* findMin(Nodo<H>*);
    void print(string type, ofstream &out);
    void Rotate(string, H);
    void rLeft(Nodo<H>*);
    void rRight(Nodo<H>*);
};

template <class H> void BST<H>::Trapianta(Nodo<H>* u, Nodo<H>* v){
    if(u->getPadre() == NULL)
        radice = v;
    else if(u == u->getPadre()->getDx()){
        u->getPadre()->setDx(v);
    }
    else
        u->getPadre()->setSx(v);
    
    if(v != NULL)
        v->setPadre(u->getPadre());
}

template <class H> Nodo<H>* BST<H>::Search(H x){
    Nodo<H>* iter = radice;

    while(iter != NULL && x != iter->getElemento()){
        if(x > iter->getElemento())
            iter = iter->getDx();
        else
            iter = iter->getSx();
    }

    return iter;
}

template <class H> Nodo<H>* BST<H>::findMin(Nodo<H>* p){
    Nodo<H>* iter = p;

    while(iter->getSx() != NULL)
        iter = iter->getSx();
    
    return iter;
}

template <class H> void BST<H>::Canc(H x){
    Nodo<H>* ptr = Search(x);

    if(ptr != NULL){
        if(ptr->getSx() == NULL)
            Trapianta(ptr, ptr->getDx());
        else if(ptr->getDx() == NULL)
            Trapianta(ptr, ptr->getSx());
        else{
            Nodo<H>* y = findMin(ptr->getDx());
            
            if(y->getPadre() != ptr){
                Trapianta(y, y->getDx());
                y->setDx(ptr->getDx());
                y->getDx()->setPadre(y);
            }
            Trapianta(ptr, y);
            y->setSx(ptr->getSx());
            y->getSx()->setPadre(y);
        }
    }
}

template <class H> void BST<H>::Insert(H x){
    Nodo<H>* nuovo = new Nodo<H>(x);
    if(radice == NULL)
        radice = nuovo;
    else{
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
        if(x > tmp->getElemento())
            tmp->setDx(nuovo);
        else
            tmp->setSx(nuovo);
    }
}

template <class H> void BST<H>::Inorder(Nodo<H>* ptr, ofstream &out){
    if(ptr != NULL){
        Inorder(ptr->getSx(), out);
        out << ptr->getElemento() << " ";
        Inorder(ptr->getDx(), out);
    }
}

template <class H> void BST<H>::Preorder(Nodo<H>* ptr, ofstream &out){
    if(ptr != NULL){
        out << ptr->getElemento() << " ";
        Preorder(ptr->getSx(), out);
        Preorder(ptr->getDx(), out);
    }
}

template <class H> void BST<H>::Postorder(Nodo<H>* ptr, ofstream &out){
    if(ptr != NULL){
        Postorder(ptr->getSx(), out);
        Postorder(ptr->getDx(), out);
        out << ptr->getElemento() << " ";
    }
}

template <class H> void BST<H>::print(string type, ofstream &out){
    if(type == "postorder")
        Postorder(radice, out);
    else if(type == "preorder")
        Preorder(radice, out);
    else
        Inorder(radice, out);
    out << endl;
}

template <class H> void BST<H>::Rotate(string type, H x){
    Nodo<H>* ptr = Search(x);
    if(ptr != NULL){
        if(type == "left")
            rLeft(ptr);
        else
            rRight(ptr);
    }
}

template <class H> void BST<H>::rLeft(Nodo<H>* y){
     if(y != NULL){
        Nodo<H>* x = y->getDx();
        Nodo<H>* z = y->getPadre();
        if(x != NULL){
            y->setDx(x->getSx());
            x->setSx(y);

            Trapianta(y, x);

            x->setPadre(z);
            y->setPadre(x);

            if(y->getDx())
                y->getDx()->setPadre(y); 
        }
    }
}

template <class H> void BST<H>::rRight(Nodo<H>* y){
    if(y != NULL ){
        Nodo<H>* x = y->getSx();
        Nodo<H>* z = y->getPadre();
        if(x != NULL){
            y->setSx(x->getDx());
            x->setDx(y);

            Trapianta(y, x);
            
            x->setPadre(z);
            y->setPadre(x);

            if(y->getSx())
                y->getSx()->setPadre(y);
        }
    }
}

int duepunti(string x){
    for(int i = 0; i < x.length(); i++)
        if(x[i] == ':')
            return i;
    return -1;
}

string op(string x){
    return x.substr(0, duepunti(x));
}

string value(string x){
    return x.substr(duepunti(x) + 1, x.length());
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        string typef; in >> typef;
        int n; in >> n;
        int m; in >> m;
        string typev; in >> typev;

        if(typef == "int"){
            BST<int>* t = new BST<int>();
    
            for(int j = 0; j < n+m; j++){
                string tmp; in >> tmp;

                string operation = op(tmp);
                
                if(operation == "ins")
                    t->Insert(stoi(value(tmp)));
                else if(operation == "canc")
                    t->Canc(stoi(value(tmp)));
                else if(operation == "right")
                    t->Rotate(operation, stoi(value(tmp)));
                else if(operation == "left")
                    t->Rotate(operation, stoi(value(tmp)));
            }

            t->print(typev, out);
            delete t;
        }

        else{
            BST<double>* t = new BST<double>();
    
            for(int j = 0; j < n+m; j++){
                string tmp; in >> tmp;

                string operation = op(tmp);

                if(operation == "ins")
                    t->Insert(stod(value(tmp)));
                else if(operation == "canc")
                    t->Canc(stod(value(tmp)));
                else if(operation == "right")
                    t->Rotate(operation, stod(value(tmp)));
                else if(operation == "left")
                    t->Rotate(operation, stod(value(tmp)));
            }

            t->print(typev, out);
            delete t;
        }
    }
}
