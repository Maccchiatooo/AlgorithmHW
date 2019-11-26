#include <list>
#include <iostream>
using namespace std;

struct v_l{ int v; struct v_l  *next;};
typedef struct v_l vertex_list;

vertex_list * graph_part(int n, int k, vertex_list * edges[], int r){


    //vertex_list 1 *edges[1]
    //1->next[1]= first neighbor

    //construct left list and right list
    list <vertex_list> L;
    list <vertex_list> R;
    list <vertex_list>::iterator it;
    vertex_list *l;
    vertex_list *r;
    for (int i=0; i<k; i++){
        L.push_back(*Edges[i]);
    }
    for (int R=0; i<n-k; i++){
        R.push_back(*Edges[i]);
    }

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

    for(it=L.begin();it!=L.end();++it){
        vertex_list a=*it;
        

    }


    
}