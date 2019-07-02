//Coded By daxcpp (Davide Carnemolla)
#include <iostream>
#include <fstream>
using namespace std;

class Activity{
private:
    int s;
    int f;
public:
    Activity(int s, int f){
        this->s = s;
        this->f = f;
    }

    //Get
    int getS(){return s;}
    int getF(){return f;}
};

void sortA(Activity** vett, int n){ //Fuck complexity
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            if(vett[i]->getF() < vett[j]->getF())
                swap(vett[i], vett[j]);
}

void ActivitySelect(Activity** vett, int n, ofstream & out){
    sortA(vett,n);

    int count = 1;
    int k = 0;

    for(int i = 1; i < n; i++)
        if(vett[i]->getS() >= vett[k]->getF()){
            count++;
            k = i;
        }
    out << count << endl;
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
            int f; in >> f;
            in >> tmp;

            vett[j] = new Activity(s,f);
        }

        ActivitySelect(vett, n, out);
        
        for(int i = 0; i < n; i++)
            delete vett[i];
        
        delete [] vett;
    }
}
