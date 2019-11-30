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


    
    int nnn=0;
    int Gmax=0;
    int num=0;
    vertex_list *record;
      
    //vertex_list 1 *edges[1]
    //1->next[1]= first neighbor

    //construct left list and right list
    map <int,vertex_list> LL;
    map <int,vertex_list> RR;
    map <int,vertex_list> L;
    map <int,vertex_list> R;
    map <int,vertex_list>::iterator it;
    vertex_list *l;
    vertex_list *rr;
    
    for (int i=0; i<k; i++){
        L.insert(make_pair(i,*edges[i]));
    }
    for (int i=k; i<n; i++){
        R.insert(make_pair(i,*edges[i]));
    }
   
    
    
    //do{ 
        
        //set the calculation vertex list
        LL=L;
        RR=R;
        //calculate the external link/internal link and the cost

        int *exter;
        int *inter;
        exter=(int*) malloc( n* sizeof(int) );
        inter=(int*) malloc( n* sizeof(int) );


        for(int i=0;i<n;i++){
            exter[i]=0;
            inter[i]=0;

            
        }
        

        
        int **cost = new int*[n];
        for (int i = 0; i < n; ++i) {
        cost[i] = new int[n];
        }

        

       

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cost[i][j]=0;
            }
        }

        int **gain = new int*[n];
        for (int i = 0; i < n; ++i) {
        gain[i] = new int[n];
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                gain[i][j]=0;
            }
        }

    

        int *D;
        D=(int*) malloc( n* sizeof(int) );

    //calculate the external and internal and the D and the cost 

        
        for (int i=0; i<n;i++){
            cost[i][edges[i]->next->v]=1;
            
            }
   //calculate the internal and the external

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
       

        
    }

    //calculation of the gain value
    int gmax=0;
    int left=0;
    int right=0;

    for (int i=0;i<k;i++){
            for (int j=k;j<n;j++){

                if(edges[i]->next->v==edges[j]->v||edges[i]->v==edges[j]->next->v){
                    gain[i][j]=D[i]-D[j]-2;
                }else gain[i][j]=D[i]-D[j];
                
              
                
                if(gmax<gain[i][j]){
                    
                    gmax=gain[i][j];
                    
                    left=i;
                    right=j;

                    
                    
                }

           }
                
    }

    list <int> gv;
    list <int> lv;
    list <int> rv;
    set <int> lr;
    set <int> ::iterator its;
    list <int>::iterator itr;
    list <int>::iterator itrr;

    gv.push_back(gmax);
    gmax=0;
    lv.push_back(left);
    rv.push_back(right);
    lr.insert(left);
    lr.insert(right);
   // cout<<left<<endl;
   // cout<<right<<endl;
   


    while(lv.size()!=k){

        
        
         
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
    
        gv.push_back(gmax);
        
        gmax=-1000;
        lv.push_back(left);
        rv.push_back(right);

        
        lr.insert(left);
        lr.insert(right);

        

    }


  //  for (itr=gv.begin();itr!=gv.end();++itr){
    //    cout<<*itr<<endl;
    //}
        
    for (itr=lv.begin();itr!=lv.end();++itr){
        cout<<*itr<<endl;
    }

   for (itr=rv.begin();itr!=rv.end();++itr){
        cout<<*itr<<endl;
    }








return l;
};

int main()
{   vertex_list * graph[1000], *result, *e, *tmp;
    int i,j, cross;
    int partition[1000];

    // make empty graph     
    e = (vertex_list *) malloc( 10000* sizeof(vertex_list) );
    for(i=0; i<1000; i++)
      graph[i] = NULL;
    printf("Test 1: A cycle with 1000 vertices\n");
    // now fill it as a cycle //
    for(i=0,j=0; i<1000; i++)
      {  graph[i] = e+j; j+=1; //next available edge node //
	(graph[i])->v = (i+999)%1000;
        (graph[i])->next = e+j; j+=1; //next available edge node //
        (graph[i])->next->v = (i+1)%1000;
        (graph[i])->next->next = NULL;
      }
      printf("Made a cycle, now try to partition it\n"); fflush(stdout);
    result=graph_part(1000, 500, graph, 100);

  


    


}
