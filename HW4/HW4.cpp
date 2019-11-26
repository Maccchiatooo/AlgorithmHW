#include <iostream>
#include <list>
#include <map>


using namespace std;

struct v_l{ int v; struct v_l  *next;};
typedef struct v_l vertex_list;


vertex_list * graph_part(int n, int k, vertex_list * edges[], int r){




    int Gmax=0;

    do{  
    //vertex_list 1 *edges[1]
    //1->next[1]= first neighbor

    //construct left list and right list
    map <int,vertex_list> L;
    map <int,vertex_list> R;
    map <int,vertex_list>::iterator it;
    vertex_list *l;
    vertex_list *r;
    for (int i=0; i<k; i++){
        L.insert(makepair(i,*edges[i]));
    }
    for (int i=k; i<n; i++){
        R.insert(makepair(i,*edges[i]));
    }

    //calcualte the number of neibors
    int *Numofnei;
    vertex_list *Edges;
    for(int i=0; i<n; i++){
        Edges[i]= * edges[i];
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
    int nl=0;
    int nr=0;
    //construct the left vertex
    for(it=L.find(0);it!=L.find(k);++it){
        l[nl]=it->second;
        nl++;
    }
    
    //construct the right vertex
    for(it=R.find(k);it!=R.find(n);++it){    
        r[nr]=it->second;
        nr++;
    }





    //calculate the external/ internal link for the left side
    for (int i=0; i<k; i++){
        inter[i]=0;
        exter[i]=0;
        for (int j=0; j<Numofnei[i]; j++){
            //internal value
            for (int p=i+1; p<k; p++){
                if (l[i].next[j].v==l[p].v){
                    cost[i][p]=1;
                    inter[i]++;
                }
            }
            //external value
            for (int q=0; q<n-k; q++){

                if (l[i].next[j].v==r[q].v){
                    cost[i][q]=1;
                    exter[i]++;
                }
            }
        }    
        D[i]=exter[i]-inter[i];
    }
    //calculate the external/ internal link for the right side
    for (int i=k; i<n; i++){
        inter[i]=0;
        exter[i]=0;
        for (int j=0; j<Numofnei[i]; j++){
            //internal value
            for (int p=i+1; p<n; p++){
                if (r[i-k].next[j].v==r[p-k].v){
                    inter[i]++;
                    cost[i][p]=1;
                }
            }

            for (int q=0; q<k; q++){

                if (r[i-k].next[j].v==l[q].v){
                    exter[i]++;
                    cost[i][q]=1;
                }
            }
        }
        D[i]=exter[i]-inter[i];    
    }

    //calculation of the gain value
    int ** g;
    for (int i=0;i<k;i++){
        for (int j=k;j<n;j++){
            for(int o=0;o<Numofnei[i];o++){
                if (l[i].next[o].v==r[j-k].v)
                g[i][j]=D[i]-D[j]-2;
            }
            g[i][j]=D[i]-D[j];
        }
    }

    //caculation of the max value of the gain
    int *ld;
    int *rd;
    int *gmax;
    int num=0;
    int *Gadd;

    for(int i=0;i<k;i++){
        for(int j=k;j<n;j++){
            if (gmax[num]<g[i][j]){
                gmax[num]=g[i][j];
                ld[num]=i;
                rd[num]=j;
            }    
        }
    }
    Gadd[0]=gmax[num];
     
     
    vertex_list *ll;
    vertex_list *rr;
    do{
        for (it=L.begin();it!=L.end();it++){
        if ((it->second).v==ld[num]){
        ll[num]=it->second;
        erase(it);
        }
    }    
    for (it=R.begin();it!=R.end();it++){
        if (*it.v==rd[num]){
        rr[num]=it->second;
        erase(it);
        }
    }  

    int nl=0;
    int nr=0;
    //construct the left vertex
    for(it=L.begin();it!=L.end();++it){
        l[nl]=it->second;
        nl++;
    }
    
    //construct the right vertex
    for(it=R.begin();it!=R.end();++it){    
        r[nr]=it->second;
        nr++;
    }

    //recalculate the D and the gain value
    for (int i=0;i<nl+nr;i++){
    D[i]=D[i]+2*cost[i][ld[num]]-2*cost[i][rd[num]];}

    for (int i=0;i<nl;i++){
        for (int j=nl;j<nl+nr;j++){
        g[i][j]=D[i]-D[j]-2*c[i][j];
        }
    }

    //recalculate the Gain max
        
    num++;  
    for(int i=0;i<nl;i++){
        for(int j=nl;j<nl+nr;j++){
            if (gmax[num]<g[i][j]){
                gmax[num]=g[i][j];
                ld[num]=i;
                rd[num]=j;
            }    
        }
    }
    }while(nl==1);



    for(int i=1;i<k;i++){
         
         Gadd[i]=Gadd[i-1]+gmax[i];
    }
    
    int GG=0;
    for(int i=0;i<k;i++){
        if (Gmax<Gadd[i]){
            Gmax=Gadd[i];
            GG=i;
        }
    }
    for (int i=0;i<GG;i++){

        vertex_list ret[i]=l[i];
    }

    for (int i=GG;i<2*GG;i++){

        vertex_list ret[i]=r[i-GG];
    }
    
    
    }while(Gmax<0||Gmax==0);


    







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

