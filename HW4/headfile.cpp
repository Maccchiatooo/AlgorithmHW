#include <iostream>
#include <list>
#include <map>

using namespace std;

struct v_l{ int v; struct v_l  *next;};
typedef struct v_l vertex_list;

int **cost;

int * Calofnei(int n, vertex_list *edges[]){

    vertex_list *Edges;
    int * num;
    for (int i=0;i<n;i++){
        Edges[i]=*edges[i];
        num[i]=0;
        while(Edges[i].next){
            Edges[i].next++;
            num[i]++;
        }
    }
    return num;
};

int * Calofinter(int k, int* numofnei, vertex_list *l){
    int *inter;

    for(int i=0;i<k;i++){
        inter[i]=0;
        for(int j=0;j<numofnei[i];j++){
            for(int p=i+1;p<k;p++){
                if(l[i].next[j].v==l[p],v){
                    cost[i][p]=1;
                    inter[i]++;
                }
            }
        }
    }

    return inter;
}

int * Calofexter(int k, int* numofnei, vertex_list *l){
    int *inter;

    for(int i=0;i<k;i++){
        inter[i]=0;
        for(int j=0;j<numofnei[i];j++){
            for(int q=0;p<n-k;p++){
                if(l[i].next[j].v==l[p],v){
                    cost[i][p]=1;
                    inter[i]++;
                }
            }
        }
    }

    return inter;
}