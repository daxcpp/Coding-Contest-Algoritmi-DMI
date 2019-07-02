//Coded By daxcpp (Davide Carnemolla)
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

class Edge{
protected:
    int peso;
    int s, f;
public:
    Edge(int _s, int _f, int _p): s(_s), f(_f), peso(_p){}

    int getPeso(){return peso;}
    int getS(){return s;}
    int getF(){return f;}
};


class Grafo{
protected:
    int len, n, m;

    Edge** M;

public:
    Grafo(int _n): n(_n){
        len = 1000;
        m = 0;
        M = new Edge*[len];
        for(int i = 0; i < len; i++)
            M[i] = NULL;
    }  

    ~Grafo(){
        for(int i = 0; i < m; i++)
            delete M[i];
        delete [] M;
    } 

    void addEdge(int x, int y, int p){
        M[m] = new Edge(x, y, p);
        m++;
    }

    void BellmanFord(int s, int f, int k, ofstream &out){
        int dist[n];
        int source = s;

        int dest = f;

        for(int i = 0; i < n; i++)
            dist[i] = INT_MAX;

        dist[source] = 0;

        for(int i = 1; i < k+1; i++){
            for(int j = 0; j < m; j++){
                if(M[j] != NULL){
                    int u = M[j]->getS();
                    int v = M[j]->getF();
                    int w = M[j]->getPeso();
                    if(dist[u] != INT_MAX && dist[u] + w < dist[v])
                        dist[v] = dist[u] + w;
                }
            }
        }
        
        if(dist[dest] == INT_MAX)
            out << "inf." << endl;
        else
            out << dist[dest] << endl;
    }
};


int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        int n, m, k; in >> n >> m >> k;

        Grafo* t = new Grafo(n);


        for(int j = 0; j < m; j++){
            char tmp; in >> tmp;
            int x, y, p;
            in >> x;
            in >> y;
            in >> p;
            in >> tmp;
            t->addEdge(x, y, p);
        }

        int s, f; in >> s >> f;

        t->BellmanFord(s,f, k, out);
        delete t;
        
    }
}
