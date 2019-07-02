//Coded By daxcpp (Davide Carnemolla)
#include <iostream>
#include <fstream>
using namespace std;

class Activity{
private:
    int s;
    int f;
public:
    Activity(int _s, int _f): s(_s), f(_f){}

    //Get
    int getS(){return s;}
    int getF(){return f;}
    int getProfit(){return f - s;}

    friend ostream& operator<<(ostream& os, Activity &x){
        return os << "(" << x.s << "," << x.f << ")";
    }
};

void SortA(Activity** vett, int n){
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            if(vett[i]->getF() > vett[j]->getF())
                swap(vett[i], vett[j]);
            else if(vett[i]->getF() == vett[j]->getF() && vett[i]->getS() < vett[j]->getS())
                swap(vett[i], vett[j]);
}

void printA(Activity** vett, int n, ofstream& out){
    for(int i = 0; i < n; i++)
        out << *vett[i] << " ";
    out << endl;
}

int latestNonConflict(Activity** vett, int i){
    for(int j = i-1; j >= 0; j--)
        if(vett[j]->getF() <= vett[i]->getS())
            return j;
    return -1;
}


void ActivitySelector(Activity** vett, int n, ofstream& out){
    SortA(vett, n);

    int table[n];
    table[0] = vett[0]->getProfit();

    for(int i = 1; i < n; i++){
        int tmprofit = vett[i]->getProfit();
        int l = latestNonConflict(vett, i);

        if(l != -1)
            tmprofit += table[l];
        if(tmprofit > table[i-1])
            table[i] = tmprofit;
        else
            table[i] = table[i-1];
        
    }

    out << table[n-1] << endl;
}


int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        int n; in >> n;

        Activity** vett = new Activity*[n];

        for(int j = 0; j < n; j++){
            char tmp; in >> tmp;
            int s; in >> s;
            //in >> tmp;
            int f; in >> f;
            in >> tmp;
            vett[j] = new Activity(s,f);
        }

        ActivitySelector(vett, n, out);

        delete [] vett;
    }
}
