#include <iostream>

using namespace std;

struct v_l{ int v; struct v_l  *next;};
typedef struct v_l vertex_list;


vertex_list * graph_part(int n, int k, vertex_list * edges[], int r){


    //vertex_list 1 *edges[1]
    //1->next[1]= first neighbor

    vertex_list A[k];
    for (int i=0;i<k;i++){
        A[i]=*edges[i];
    }

    vertex_list B[n-k];
    for (int i=0;i<n-k;i++){
        B[i]=*edges[i+k];
    }


    
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

