#include <stdio.h>
#include <stdlib.h>

struct v_l ( int v; struct v_l * next; } ;
typedef struct v_l vertex_list;
vertex_list * graph_part( int n, int k, vertex_list * edges[], int r );


int main()
{   vertex_list * graph[1000], *result, *e, *tmp;
    int i,j, cross;
    int partition[1000];

    /* make empty graph */    
    e = (vertex_list *) malloc( 10000* sizeof(vertex_list) );
    for(i=0; i<1000; i++)
      graph[i] = NULL;
    printf("Test 1: A cycle with 1000 vertices\n");
    /* now fill it as a cycle */
    for(i=0,j=0; i<1000; i++)
      {  graph[i] = e+j; j+=1; /*next available edge node */
	(graph[i])->v = (i+999)%1000;
        (graph[i])->next = e+j; j+=1; /*next available edge node */
        (graph[i])->next->v = (i+1)%1000;
        (graph[i])->next->next = NULL;
      }
    printf("Made a cycle, now try to partition it\n"); fflush(stdout);
    result=graph_part(1000, 500, graph, 100);
    for(i=0; i<1000; i++)
       partition[i]=0;
    for( i=0, tmp=result; tmp != NULL; tmp=tmp->next )
    {   partition[tmp->v]=1; i+=1; }
    if( i != 500 )
      printf("the partition has %d vertices, not 500\n", i);fflush(stdout);
    for(i=0, cross = 0; i< 1000; i++)
    {  for( tmp = graph[i]; tmp != NULL; tmp = tmp-> next )  
       {  j = tmp->v;
	  if(partition[i] != partition[j])
             cross +=1;
       }
    }
    printf("Partition has %d crossing edges\n\n", cross/2); fflush(stdout);
    printf("Test 2: 300 cycles with 3 vertices each\n");
    /* now fill the graph*/
    for(i=0,j=0; i<300; i++)
    {    graph[3*i] = e+j; j+=1; /*next available edge node */
	(graph[3*i])->v = 3*i+1;
        (graph[3*i])->next = e+j; j+=1; /*next available edge node */
        (graph[3*i])->next->v = 3*i+2;
        (graph[3*i])->next->next = NULL;
         graph[3*i+1] = e+j; j+=1; /*next available edge node */
	(graph[3*i+1])->v = 3*i;
        (graph[3*i+1])->next = e+j; j+=1; /*next available edge node */
        (graph[3*i+1])->next->v = 3*i+2;
        (graph[3*i+1])->next->next = NULL;
         graph[3*i+2] = e+j; j+=1; /*next available edge node */
	(graph[3*i+2])->v = 3*i;
        (graph[3*i+2])->next = e+j; j+=1; /*next available edge node */
        (graph[3*i+2])->next->v = 3*i+1;
        (graph[3*i+2])->next->next = NULL;
    }
    printf("Made 300 K_, now try to partition it\n"); fflush(stdout);
    result=graph_part(900, 300, graph, 100);
    for(i=0; i<9000; i++)
       partition[i]=0;
    for( i=0, tmp=result; tmp != NULL; tmp=tmp->next )
    {   partition[tmp->v]=1; i+=1; }
    if( i != 300 )
      printf("the partition has %d vertices, not 300\n", i);fflush(stdout);
    for(i=0, cross = 0; i< 900; i++)
    {  for( tmp = graph[i]; tmp != NULL; tmp = tmp-> next )  
       {  j = tmp->v;
	  if(partition[i] != partition[j])
             cross +=1;
       }
    }
    printf("Partition has %d crossing edges\n", cross/2); fflush(stdout);

    exit(0);
} 
