#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <map>
#include <set>




using namespace std;

struct v_l{ int v; struct v_l  *next;};
typedef struct v_l vertex_list;


vertex_list * graph_part(int n, int k, vertex_list * edges[], int r){

        int h=0;
        //define the exter and the inter
        int *exter;
        int *inter;
        exter=(int*) malloc( n* sizeof(int) );
        inter=(int*) malloc( n* sizeof(int) );
        for(int i=0;i<n;i++){
            exter[i]=0;
            inter[i]=0;  
        }
        
        //define the cost
        int **cost = new int*[n];
        for (int i = 0; i < n; ++i) {
        cost[i] = new int[n];
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cost[i][j]=0;
            }
        }

        //define the gain
        int **gain = new int*[n];
        for (int i = 0; i < n; ++i) {
        gain[i] = new int[n];
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                gain[i][j]=0;
            }
        }

        //define the D
        int *D;
        D=(int*) malloc( n* sizeof(int) );



    //define the return vertex_list *
    vertex_list *ret[n];
    //define the Gmax value
    int Gmax=1;
    //define the time T
    int T=1;

    //Start the loop
    while(Gmax==0||Gmax>0){ 

    //calculate the cost 
     
        for (int i=0; i<n;i++){
            cost[i][edges[i]->next->v]=1;
            
            }
   //calculate the internal 

    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            if(edges[i]->next->v==edges[j]->v){
                inter[i]++;
                inter[j]++;
            }
        }
    }

    for(int i=k;i<n;i++){
        for(int j=k;j<n;j++){
            if(edges[i]->next->v==edges[j]->v){
                inter[i]++;
                inter[j]++;
            }
        }
    }
    //calculate the external
    for(int i=0;i<k;i++){
        for(int j=k;j<n;j++){
            if(edges[i]->next->v==edges[j]->v){
                exter[i]++;
                exter[j]++;    
            }
        }
    }

    for(int i=k;i<n;i++){
        for(int j=0;j<k;j++){
            if(edges[i]->next->v==edges[j]->v){
                exter[i]++;
                exter[j]++;
            }
        }
    }

    //calculation of the D value
    for(int i=0;i<n;i++){
        D[i]=exter[i]-inter[i];   

        //cout<<D[i]<<endl;     
    }

    //calculation of the gain value 
    int gmax=-10000;
    int left=0;
    int right=0;

    for (int i=0;i<k;i++){
        for (int j=k;j<n;j++){

            if(edges[i]->next->v==edges[j]->v||edges[i]->v==edges[j]->next->v){
                gain[i][j]=D[i]-D[j]-2;
               /* cout<<D[i]<<endl;
                cout<<D[j]<<endl;
                cout<<gain[i][j]<<endl;
                cout<<i<<endl;
                cout<<j<<endl;*/
                
            }else gain[i][j]=D[i]-D[j];
                
            if(gmax<gain[i][j]){
                gmax=gain[i][j];

                
                left=i;
                right=j;
                
            }
        }            
    }
    //calculate the first vertex position
    int ggv[k];
    int llv[k];
    int rrv[k];

    for(int i=0;i<k;i++){
        ggv[i]=0;
        llv[i]=0;
        rrv[i]=0;
    }
    set <int> lr;
    set <int> ::iterator its;

    ggv[0]=gmax;
    gmax=-10000;
    llv[0]=left;
    rrv[0]=right;

    
    lr.insert(left);
    lr.insert(right);
   
    //define the circle number
    int num=1;
    while(num<k){
        for(int i=0;i<n;i++){
            if(lr.count(i)==0){
                D[i]=D[i]+2*cost[i][left]-2*cost[i][right];
                
            }
        }
        
        for(int i=0;i<k;i++){
            for (int j=k;j<n;j++){
                if(lr.count(i)==0&&lr.count(j)==0){    
                    gain[i][j]=D[i]-D[j]-2*cost[i][j];
                    if(gmax<=gain[i][j]){
                        gmax=gain[i][j];   
                        left=i;
                        right=j;   
                        
                    }    
                }
            } 
        } 
        ggv[num]=gmax;
        //cout<<gmax<<endl;
        llv[num]=left;
        rrv[num]=right;
        gmax=-1000000;
        
        lr.insert(left);
        lr.insert(right);
        num++;
    }
    Gmax=0;
    //define the adding value
    int Gadd[k];
    //define the position
    int Gmad=0;
    //the first adding value
    Gadd[0]=ggv[0];
    //calculate the adding value
    for(int i=1;i<k;i++){
        Gadd[i]=Gadd[i-1]+ggv[i];
        
    }

    for(int i=0;i<k;i++){
        if(Gmax<Gadd[i]){
            Gmax=Gadd[i];
            Gmad=i;
        }
        cout<<Gadd[i]<<endl;
    }
    //cout<<Gmad<<endl;

    
    
    //exchange the value
    for(int i=0;i<Gmad;i++){
        int temp;
        temp = edges[llv[i]]->v;
        edges[llv[i]]->v=edges[rrv[i]]->v;
        edges[rrv[i]]->v=temp;

        temp = edges[llv[i]]->next->v;
        edges[llv[i]]->next->v=edges[rrv[i]]->next->v;
        edges[rrv[i]]->next->v=temp;

        edges[llv[i]]->next->next = NULL;
        edges[rrv[i]]->next->next = NULL;

    }





    

    T++;
    for(its=lr.begin();its!=lr.end();++its){
        lr.erase(its);
    }
    

    if(T==2) break;
}



return *edges;
};

int main()
{   vertex_list * graph[6], *result, *e, *tmp;
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



      
      printf("Made a cycle, now try to partition it\n"); fflush(stdout);
    result=graph_part(6, 3, graph, 100);

  


    


}
