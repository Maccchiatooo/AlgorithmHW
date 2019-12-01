#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <map>
#include <set>




using namespace std;

struct v_l{ int v; struct v_l  *next;};
typedef struct v_l vertex_list;
 
 



int main(){

    vertex_list * graph[6], *result, *e, *tmp;
    int i,j, cross;
    int partition[6];

    // make empty graph     
    e = (vertex_list *) malloc( 10000* sizeof(vertex_list) );
    for(i=0; i<6; i++)
      graph[i] = NULL;
    printf("Test 1: A cycle with 1000 vertices\n");
    // now fill it as a cycle //
    for(i=0,j=0; i<6; i++)
      {  graph[i] = e+j; j+=1; //next available edge node //
	(graph[i])->v = (i+5)%6;
        (graph[i])->next = e+j; j+=1; //next available edge node //
        (graph[i])->next->v = (i+1)%6;
        (graph[i])->next->next = NULL;
      }






    for (int i=0;i<6;i++){
        cout<<graph[i]->next->v<<endl;
    }




    for(int i=0;i<3;i++){
        
        int temp;
        temp = graph[i]->v;
        graph[i]->v=graph[i+3]->v;
        graph[i+3]->v=temp;

        temp = graph[i]->next->v;
        graph[i]->next->v=graph[i+3]->next->v;
        graph[i+3]->next->v=temp;
        
    }
    for (int i=0;i<6;i++){
        cout<<graph[i]->next->v<<endl;
    }


}
