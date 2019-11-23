#include <iostream>
#include <list>


using namespace std;

struct v_l{ int v; struct v_l  *next;};
typedef struct v_l vertex_list;


vertex_list * graph_part(int n, int k, vertex_list * edges[], int r){


    //vertex_list 1 *edges[1]
    //1->next[1]= first neighbor

    //construct left list and right list
    list <vertex_list> L;
    list <vertex_list> R;
    for (int i=0; i<k; i++){
        L.push_back(*Edges[i]);
    }
    for (int R=0; i<n-k; i++){
        B.push_back(*Edges[i]);
    }

    //calcualte the number of neibors
    int *Numofnei;
    for(int i=0; i<n; i++){
        vertex_list Edges[i]= * edges[i];
        Numofnei[i]=0;
        while(Edges[i].next){
            Edges[i].next++;
            Numofnei[i]++;
        }
    }
    //calculate the external link/internal link and the cost

    int *exter;
    int *inter;
    int **cost;
    int *D;
    //calculate the external/ internal link
    for (int u=0; u<k; u++){
        inter[u]=0;
        exter[u]=0;
        for (int v=0; v<Numofnei[u]; v++){
            
            for (int w=u+1; w<k; w++){
                if (A[u].next[v].v==A[j].v){
                    g[i][j]=1;
                    inter[i]++;
                }
            }

            for (int ii=0; ii<n-k; ii++){

                if (A[i].next[jj].v==B[ii].v){
                    exter[i]++;
                    g[i][ii]=1;
                }
        
            }
        
        }
        
        D[i]=exter[i]-inter[i];

    }

    for (int i=k; i<n; i++){
        inter[i]=0;
        exter[i]=0;
        for (int jj=0; jj<len[i];jj++){
            
            for (int j=i+1; j<n; j++){
                if (A[i].next[jj].v==A[j].v){
                    inter[i]++;
                }
            }

            for (int ii=0; ii<k; ii++){

                if (A[i].next[jj].v==B[ii].v){
                    exter[i]++;
                }
        
            }
        
        }

        D[i]=exter[i]-inter[i];    
    
    }


    int ** g;

    for (int i=0;i<k;i++){
        for (int j=k;j<n;j++){
            for(int jj=0;jj<len[i];jj++){
                if (A[i].next[jj].v==B[j].v)
                g[i][k]=D[i]-D[j]-2;
            }
            g[i][k]=D[i]-D[j];
        }
    }
    int b=0;
    int c=0;
    int a=g[0][0];
     for (int i=0;i<k;i++){
        for (int j=k;j<n;j++){
        

        if (a<g[i][j]) {
            a=g[i][j];
            b=i;
            c=j;
        }
        
        }
     }
    int n=0; 
    int G[n]=a;
    
    int Gm=0;
    for (int i=0;i<n;i++){
        Gm+=G[i]
    }
    A[b].v=0;
    B[c].v=0;

    while(Gm<0||Gm==0);


};
/*
int main(){

    vertex_list a;
    a.v=5;
    vertex_list b;
    b.v=20;
    a.next[0]=b;
    vertex_list b1;
    b1.v=30;
    a.next[1]=b1;
    vertex_list b2;
    b2.v=30;
    a.next[2]=b2;
    int as=a.next;
    cout<<as;
}*/

