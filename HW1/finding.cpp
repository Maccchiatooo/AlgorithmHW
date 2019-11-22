//  Compile Command:g++ finding.cpp -lX11 -lm -L/usr/X11R6/lib^C
//  Run command:./a.out test1


#include <fstream>   
#include <iostream>
#include <vector>
#include <math.h>
#include <map>
#include <list>
#include <queue>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <stdio.h>
using namespace std;




//xlib.h
Display *display_ptr;
Screen *screen_ptr;
int screen_num;
char *display_name = NULL;
unsigned int display_width, display_height;

Window win;
int border_width;
unsigned int win_width, win_height;
int win_x, win_y;

XWMHints *wm_hints;
XClassHint *class_hints;
XSizeHints *size_hints;
XTextProperty win_name, icon_name;
char *win_name_string = "Example Window";
char *icon_name_string = "Icon for Example Window";

XEvent report;

GC gc, gc_yellow, gc_red, gc_grey;
unsigned long valuemask = 0;
XGCValues gc_values, gc_yellow_values, gc_red_values, gc_grey_values;
Colormap color_map;
XColor tmp_color1, tmp_color2;

// our coding
class Pair{
    public:
    int x;
    int y;
    Pair(){
        x=0;
        y=0;
    }
    Pair(int x, int y){
        this->x=x;
        this->y=y;
    }
};
class Tri{
    public:
    int x;
    int y;
    int z;
    Tri(int x, int y, int z){
        this->x=x;
        this->y=y;
        this->z=z;
    }
    Tri(){
        x=0;
        y=0;
        z=0;
    }
};
struct vehicle{
    Pair a;
    Pair b;
    Pair c;

};
class Obstacle{
    public:
    Pair a;
    Pair b;
    Pair c;
    Obstacle(Pair a,Pair b,Pair c){
        this->a=a;
        this->b=b;
        this->c=c;    
    }
    Obstacle(){
        a=Pair(0,0);
        b=Pair(0,0);
        c=Pair(0,0);
    }
};
bool equal(Tri a,Tri b){
    if(a.x == b.x && a.y == b.y && a.z == b.z){
        return true;
    }else{
        return false;
    }
}
struct compare{
        bool operator()(const Tri a, const Tri b) const {
        return ((1000000*a.x+1000*a.y+a.z)>(1000000*b.x+1000*b.y+b.z));

    }

};
Pair rotation(Pair a,int theta){
    int newX,newY;
    
    newX=a.x*cos((float)theta/180*3.14159)+a.y*sin((float)theta/180*3.14159);
    newY=a.y*cos((float)theta/180*3.14159)-a.x*sin((float)theta/180*3.14159);
    return Pair(newX,newY);
}
int sign(int a){
        if(a>0) return 1;
        else if(a<0) return -1;
        else return 0;
}

void Drawtri(GC gc,int X1,int Y1,int X2,int Y2,int X3,int Y3){
    XDrawLine(display_ptr,win,gc,X1,Y1,X2,Y2);
    XDrawLine(display_ptr,win,gc,X1,Y1,X3,Y3);
    XDrawLine(display_ptr,win,gc,X3,Y3,X2,Y2);

}

vector<Tri> getneighbor(Tri a){

    vector<Tri> b;
    if(a.x>0&&a.x<500&&a.y>0&&a.y<500&&a.z>0&&a.z<355){
            b.push_back(Tri(a.x+5,a.y,a.z));
            b.push_back(Tri(a.x-5,a.y,a.z));
            b.push_back(Tri(a.x,a.y+5,a.z));
            b.push_back(Tri(a.x,a.y-5,a.z));
            b.push_back(Tri(a.x,a.y,a.z+5));
            b.push_back(Tri(a.x,a.y,a.z-5));
    }else if(a.y==0){
        if (a.x==0){
            if(a.z==0)
            {b.push_back(Tri(a.x+5,a.y,a.z));
            b.push_back(Tri(a.x,a.y+5,a.z));
            b.push_back(Tri(a.x,a.y,5));
            b.push_back(Tri(a.x,a.y,355));}
            else if(a.z==355){
            b.push_back(Tri(a.x+5,a.y,a.z));
            b.push_back(Tri(a.x,a.y+5,a.z));
            b.push_back(Tri(a.x,a.y,350));
            b.push_back(Tri(a.x,a.y,0));
            }else{
            b.push_back(Tri(a.x+5,a.y,a.z));
            b.push_back(Tri(a.x,a.y+5,a.z));
            b.push_back(Tri(a.x,a.y,a.z+5));
            b.push_back(Tri(a.x,a.y,a.z-5));
            }
                       
        }else if(a.x==500){
             if(a.z==355){
                b.push_back(Tri(a.x-5,a.y,a.z));
                b.push_back(Tri(a.x,a.y+5,a.z));
                b.push_back(Tri(a.x,a.y,350));
                b.push_back(Tri(a.x,a.y,0));
            }else if(a.z==0)
            {b.push_back(Tri(a.x-5,a.y,a.z));
            b.push_back(Tri(a.x,a.y+5,a.z));
            b.push_back(Tri(a.x,a.y,a.z+5));
            b.push_back(Tri(a.x,a.y,355));}
            else{
                b.push_back(Tri(a.x-5,a.y,a.z));
                b.push_back(Tri(a.x,a.y+5,a.z));
                b.push_back(Tri(a.x,a.y,a.z+5));
                b.push_back(Tri(a.x,a.y,a.z-5));
            }
        }
        else if(a.z==0){
            b.push_back(Tri(a.x+5,a.y,a.z));
            b.push_back(Tri(a.x-5,a.y,a.z));
            b.push_back(Tri(a.x,a.y+5,a.z));
            b.push_back(Tri(a.x,a.y,a.z+5));
            b.push_back(Tri(a.x,a.y,355));
            }
        else if(a.z==355){
            b.push_back(Tri(a.x+5,a.y,a.z));
            b.push_back(Tri(a.x-5,a.y,a.z));
            b.push_back(Tri(a.x,a.y+5,a.z));
            b.push_back(Tri(a.x,a.y,0));
            b.push_back(Tri(a.x,a.y,350));
        }else{
            b.push_back(Tri(a.x+5,a.y,a.z));
            b.push_back(Tri(a.x-5,a.y,a.z));
            b.push_back(Tri(a.x,a.y+5,a.z));
            b.push_back(Tri(a.x,a.y,a.z+5));
            b.push_back(Tri(a.x,a.y,a.z-5));

        }
    }else if(a.y==500){
        if (a.x==0){
            if(a.z==0)
            {b.push_back(Tri(a.x+5,a.y,a.z));
            b.push_back(Tri(a.x,a.y-5,a.z));
            b.push_back(Tri(a.x,a.y,5));
            b.push_back(Tri(a.x,a.y,355));}
            else if(a.z==355){
            b.push_back(Tri(a.x+5,a.y,a.z));
            b.push_back(Tri(a.x,a.y-5,a.z));
            b.push_back(Tri(a.x,a.y,0));
            b.push_back(Tri(a.x,a.y,350));
            }else{
            b.push_back(Tri(a.x+5,a.y,a.z));
            b.push_back(Tri(a.x,a.y-5,a.z));
            b.push_back(Tri(a.x,a.y,a.z+5));
            b.push_back(Tri(a.x,a.y,a.z-5));
            }
                       
        }else if(a.x==500){
             if(a.z==355){
                b.push_back(Tri(a.x-5,a.y,a.z));
                b.push_back(Tri(a.x,a.y-5,a.z));
                b.push_back(Tri(a.x,a.y,0));
                b.push_back(Tri(a.x,a.y,350));
            }else if(a.z==0){
                b.push_back(Tri(a.x-5,a.y,a.z));
                b.push_back(Tri(a.x,a.y-5,a.z));
                b.push_back(Tri(a.x,a.y,a.z+5));
                b.push_back(Tri(a.x,a.y,355));
            }
            else{
                b.push_back(Tri(a.x-5,a.y,a.z));
                b.push_back(Tri(a.x,a.y-5,a.z));
                b.push_back(Tri(a.x,a.y,a.z+5));
                b.push_back(Tri(a.x,a.y,a.z-5));
            }
        }
        else if(a.z==0){
            b.push_back(Tri(a.x+5,a.y,a.z));
            b.push_back(Tri(a.x-5,a.y,a.z));
            b.push_back(Tri(a.x,a.y-5,a.z));
            b.push_back(Tri(a.x,a.y,a.z+5));
            b.push_back(Tri(a.x,a.y,355));
            }
        
        else if(a.z==355){
            b.push_back(Tri(a.x+5,a.y,a.z));
            b.push_back(Tri(a.x-5,a.y,a.z));
            b.push_back(Tri(a.x,a.y-5,a.z));
            b.push_back(Tri(a.x,a.y,0));
            b.push_back(Tri(a.x,a.y,350));

        }else{
            b.push_back(Tri(a.x+5,a.y,a.z));
            b.push_back(Tri(a.x-5,a.y,a.z));
            b.push_back(Tri(a.x,a.y-5,a.z));
            b.push_back(Tri(a.x,a.y,a.z+5));
            b.push_back(Tri(a.x,a.y,a.z-5));

        }
    }else if(a.z==355){
        if(a.x==0){
            b.push_back(Tri(a.x+5,a.y,a.z));
            b.push_back(Tri(a.x,a.y+5,a.z));
            b.push_back(Tri(a.x,a.y-5,a.z));
            b.push_back(Tri(a.x,a.y,0));
            b.push_back(Tri(a.x,a.y,350));
        }else if(a.x==500){
            b.push_back(Tri(a.x-5,a.y,a.z));
            b.push_back(Tri(a.x,a.y+5,a.z));
            b.push_back(Tri(a.x,a.y-5,a.z));
            b.push_back(Tri(a.x,a.y,0));
            b.push_back(Tri(a.x,a.y,350));
        }else{
            b.push_back(Tri(a.x-5,a.y,a.z));
            b.push_back(Tri(a.x+5,a.y,a.z));
            b.push_back(Tri(a.x,a.y+5,a.z));
            b.push_back(Tri(a.x,a.y-5,a.z));
            b.push_back(Tri(a.x,a.y,0));
            b.push_back(Tri(a.x,a.y,350));
        }
    }else if(a.z==0){
        if(a.x==0){
            b.push_back(Tri(a.x+5,a.y,a.z));
            b.push_back(Tri(a.x,a.y+5,a.z));
            b.push_back(Tri(a.x,a.y-5,a.z));
            b.push_back(Tri(a.x,a.y,5));
            b.push_back(Tri(a.x,a.y,355));}
        else if(a.x==500){
            b.push_back(Tri(a.x-5,a.y,a.z));
            b.push_back(Tri(a.x,a.y+5,a.z));
            b.push_back(Tri(a.x,a.y-5,a.z));
            b.push_back(Tri(a.x,a.y,5));
            b.push_back(Tri(a.x,a.y,355));
        }else{
            b.push_back(Tri(a.x-5,a.y,a.z));
            b.push_back(Tri(a.x+5,a.y,a.z));
            b.push_back(Tri(a.x,a.y+5,a.z));
            b.push_back(Tri(a.x,a.y-5,a.z));
            b.push_back(Tri(a.x,a.y,5));
            b.push_back(Tri(a.x,a.y,355));
            }
    }
    else if(a.x==0){
            b.push_back(Tri(a.x+5,a.y,a.z));
            b.push_back(Tri(a.x,a.y+5,a.z));
            b.push_back(Tri(a.x,a.y-5,a.z));
            b.push_back(Tri(a.x,a.y,a.z+5));
            b.push_back(Tri(a.x,a.y,a.z-5));}

    else if(a.x==500){
            b.push_back(Tri(a.x-5,a.y,a.z));
            b.push_back(Tri(a.x,a.y+5,a.z));
            b.push_back(Tri(a.x,a.y-5,a.z));
            b.push_back(Tri(a.x,a.y,a.z+5));
            b.push_back(Tri(a.x,a.y,a.z-5));
            }
    return b;
}

int  orien(Pair a,Pair b,Pair c){
    return sign(a.x*b.y+b.x*c.y+c.x*a.y-a.y*b.x-b.y*c.x-c.y*a.x);
}
bool orienin(Pair a,Pair b,Pair c,Pair p){
        if(orien(a,b,p)*orien(b,c,p)>0&&orien(b,c,p)*orien(c,a,p)>0){
            return true;
        }else return false;

}
bool orieninter(Pair a,Pair b,Pair x,Pair y){
        if(orien(a,b,x)*orien(a,b,y)<0&&orien(x,y,a)*orien(x,y,b)<0){
            return true;
        }else return false;
}

bool judgeint(vehicle v,Obstacle o, Tri c){
//transfer to orgin
    v.a=rotation(v.a,c.z);
    v.b=rotation(v.b,c.z);
    v.c=rotation(v.c,c.z);

    v.a.x+=c.x;
    v.a.y+=c.y;
    v.b.x+=c.x;
    v.b.y+=c.y;
    v.c.x+=c.x;
    v.c.y+=c.y;
    
    if(orieninter(v.a,v.b,o.a,o.b)||orieninter(v.a,v.b,o.a,o.c)||orieninter(v.a,v.b,o.b,o.c)
    ||orieninter(v.a,v.c,o.a,o.b)||orieninter(v.a,v.c,o.a,o.c)||orieninter(v.a,v.c,o.b,o.c)
    ||orieninter(v.b,v.c,o.a,o.b)||orieninter(v.b,v.c,o.a,o.c)||orieninter(v.b,v.c,o.b,o.c))
    {return true;}
    else 
    return false;
}
bool judgein(vehicle v,Obstacle o,Tri c){
    //transfer to orgin
    v.a=rotation(v.a,c.z);
    v.b=rotation(v.b,c.z);
    v.c=rotation(v.c,c.z);

    v.a.x+=c.x;
    v.a.y+=c.y;
    v.b.x+=c.x;
    v.b.y+=c.y;
    v.c.x+=c.x;
    v.c.y+=c.y;

    if(orienin(o.a,o.b,o.c,v.a)||orienin(o.a,o.b,o.c,v.b)||orienin(o.a,o.b,o.c,v.c)
    ||orienin(v.a,v.b,v.c,o.a)||orienin(v.a,v.b,v.c,o.b)||orienin(v.a,v.b,v.c,o.c))
    
    {return true;}
    else {return false;}
}


list<Tri> BFS(vehicle v,list<Obstacle> o,Tri st,Tri ta,int number_ob){
    bool visited[101][101][72];
     for (int i=0;i<101;i++){
        for (int j=0;j<101;j++){
            for (int k=0;k<72;k++){
                visited[i][j][k]=false;
            }
        }
    }
    map<Tri,Tri,compare> pathMap;
    map<Tri,Tri,compare>::iterator it;
    queue<Tri> Q;

    visited[st.x/5][st.y/5][st.z/5]=true;
    Q.push(st);
    pathMap.insert(make_pair(Tri(1000,1000,1000),st));

    while(!Q.empty()){
        Tri ccc=Q.front();
        Tri cur=Q.front();
        Q.pop();

        
        //termination condition
        if(equal(cur,ta)){
            Tri co=ta;
            it=pathMap.find(ta);
            list<Tri> res;
            res.push_back(it->first);
            while(!equal(co,st)){
                it=pathMap.find(co);
                res.push_back(it->second);
                co=it->second;
            }
            return res;
        }

        vector<Tri> neighbors=getneighbor(cur);
        for(int i=0;i<neighbors.size();i++){
            Tri abc=neighbors[i];
            bool jud;

            //list<Obstacle>::iterator k=o.begin();
            //jud=judgein(v,*k,neighbors[i])||judgeint(v,*k,neighbors[i]);
           for(list<Obstacle>::iterator k=o.begin();k!=o.end();k++){
                jud=judgein(v,*k,neighbors[i])||judgeint(v,*k,neighbors[i]);
                if (jud==true) 
                break;
                
            }
           // jud=judgein(v,o.,neighbors[i])||judgeint(v,c,neighbors[i]);
            


            if(!visited[neighbors[i].x/5][neighbors[i].y/5][neighbors[i].z/5]&&!jud){     
            visited[neighbors[i].x/5][neighbors[i].y/5][neighbors[i].z/5]=true;
            pathMap.insert(make_pair(neighbors[i],cur));
            Q.push(neighbors[i]);}
        }
    }
}


int main(int argc,char **argv){
//read the test file and transfer the value
int vx[3],vy[3],startx,starty,startphi,targetx,targety,targetphi;
FILE *input;
list<Obstacle> o;
vehicle ve;
Obstacle cc;
Tri start,target;
int obstx[3][30],obsty[3][30],i,finished,number_obst;
if(argc!=2){
    printf("need filename as command line. \n");fflush(stdout);
    exit(0);
}
input=fopen(argv[1],"r");

    if(fscanf(input,"V (%d,%d) (%d,%d) (%d,%d)\n",&(vx[0]),&(vy[0]),&(vx[1]),&(vy[1]),&(vx[2]),&(vy[2]))!=6){
        printf("error in first line. \n");fflush(stdout);
        exit(0);
    }

    ve.a.x=vx[0];
    ve.a.y=vy[0];
    ve.b.x=vx[1];
    ve.b.y=vy[1];
    ve.c.x=vx[2];
    ve.c.y=vy[2];

    cout<<ve.a.x<<' '<<ve.a.y<<' '<<ve.b.x<<' '<<ve.b.y<<' '<<ve.c.x<<' '<<ve.c.y<<endl;

    if(fscanf(input,"S (%d,%d) %d\n", &startx,&starty,&startphi)!=3){
        printf("error in second line. \n"); fflush(stdout);
        exit(0);
    }
    start.x=startx;
    start.y=starty;
    start.z=startphi;
    cout<<start.x<<' '<<start.y<<' '<<start.z<<endl;

    if(fscanf(input,"T (%d,%d) %d\n", &targetx,&targety,&targetphi)!=3){
        printf("error in third line. \n");fflush(stdout);
        exit(0);
    }
    target.x=targetx;
    target.y=targety;
    target.z=targetphi;
    cout<<target.x<<' '<<target.y<<' '<<target.z<<endl;

    i=0; finished=0;
    while(i<30&&!finished){
        if(fscanf(input,"O (%d,%d) (%d,%d) (%d,%d)\n",
        &(obstx[0][i]),&(obsty[0][i]),&(obstx[1][i]),&(obsty[1][i]),&(obstx[2][i]),&(obsty[2][i]))!=6)
        finished=1;
        else

        
        cc=Obstacle(Pair(obstx[0][i],obsty[0][i]),Pair(obstx[1][i],obsty[1][i]),Pair(obstx[2][i],obsty[2][i]));
        o.push_front(cc);

        
            i+=1;
        }
        number_obst=i-1;
    printf("found %d obstacles. so far ok\n",i-1);
//do the bfs


list<Tri> ans=BFS(ve,o,start,target,number_obst);
//output
for(list<Tri>::iterator it=ans.begin();it!=ans.end();it++){
    cout<<'('<<it->x<<' '<<it->y<<' '<<it->z<<')'<<endl;
}

//draw the line
  if( (display_ptr = XOpenDisplay(display_name)) == NULL )
    { printf("Could not open display. \n"); exit(-1);}
  printf("Connected to X server  %s\n", XDisplayName(display_name) );
  screen_num = DefaultScreen( display_ptr );
  screen_ptr = DefaultScreenOfDisplay( display_ptr );
  color_map  = XDefaultColormap( display_ptr, screen_num );
  display_width  = DisplayWidth( display_ptr, screen_num );
  display_height = DisplayHeight( display_ptr, screen_num );

  printf("Width %d, Height %d, Screen Number %d\n", 
           display_width, display_height, screen_num);
  /* creating the window */
  border_width = 10;
  win_x = 0; win_y = 0;
  win_width = display_width/2;
  win_height = (int) (win_width / 1.7); /*rectangular window*/
  
  win= XCreateSimpleWindow( display_ptr, RootWindow( display_ptr, screen_num),
                            win_x, win_y, win_width, win_height, border_width,
                            BlackPixel(display_ptr, screen_num),
                            WhitePixel(display_ptr, screen_num) );
  /* now try to put it on screen, this needs cooperation of window manager */
  size_hints = XAllocSizeHints();
  wm_hints = XAllocWMHints();
  class_hints = XAllocClassHint();
  if( size_hints == NULL || wm_hints == NULL || class_hints == NULL )
    { printf("Error allocating memory for hints. \n"); exit(-1);}

  size_hints -> flags = PPosition | PSize | PMinSize  ;
  size_hints -> min_width = 60;
  size_hints -> min_height = 60;

  XStringListToTextProperty( &win_name_string,1,&win_name);
  XStringListToTextProperty( &icon_name_string,1,&icon_name);
  
  wm_hints -> flags = StateHint | InputHint ;
  wm_hints -> initial_state = NormalState;
  wm_hints -> input = False;

  class_hints -> res_name = "x_use_example";
  class_hints -> res_class = "examples";

  XSetWMProperties( display_ptr, win, &win_name, &icon_name, argv, argc,
                    size_hints, wm_hints, class_hints );

  /* what events do we want to receive */
  XSelectInput( display_ptr, win, 
            ExposureMask | StructureNotifyMask | ButtonPressMask );
  
  /* finally: put window on screen */
  XMapWindow( display_ptr, win );

  XFlush(display_ptr);

  /* create graphics context, so that we may draw in this window */
  gc = XCreateGC( display_ptr, win, valuemask, &gc_values);
  XSetForeground( display_ptr, gc, BlackPixel( display_ptr, screen_num ) );
  XSetLineAttributes( display_ptr, gc, 1, LineSolid, CapRound, JoinRound);
  /* and three other graphics contexts, to draw in yellow and red and grey*/
  gc_yellow = XCreateGC( display_ptr, win, valuemask, &gc_yellow_values);
  XSetLineAttributes(display_ptr, gc_yellow, 6, LineSolid,CapRound, JoinRound);
  if( XAllocNamedColor( display_ptr, color_map, "yellow", 
			&tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color yellow\n"); exit(-1);} 
  else
    XSetForeground( display_ptr, gc_yellow, tmp_color1.pixel );
  gc_red = XCreateGC( display_ptr, win, valuemask, &gc_red_values);
  XSetLineAttributes( display_ptr, gc_red, 1, LineSolid, CapRound, JoinRound);
  if( XAllocNamedColor( display_ptr, color_map, "red", 
			&tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color red\n"); exit(-1);} 
  else
    XSetForeground( display_ptr, gc_red, tmp_color1.pixel );
  gc_grey = XCreateGC( display_ptr, win, valuemask, &gc_grey_values);
  if( XAllocNamedColor( display_ptr, color_map, "light grey", 
			&tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color grey\n"); exit(-1);} 
  else
    XSetForeground( display_ptr, gc_grey, tmp_color1.pixel );

  /* and now it starts: the event loop */
  while(1)
    { XNextEvent( display_ptr, &report );
      switch( report.type )
	{
	case Expose:
          /* (re-)draw the example figure. This event happens
             each time some part ofthe window gets exposed (becomes visible) */
	  //XDrawLine(display_ptr, win, gc, win_width /10, win_height/ 10,
               //    9*win_width/10, win_height/10 );

    /*
    XDrawLine(display_ptr, win, gc, win_width /10, win_height/ 10,
                   9*win_width/10, 9*win_height/10 );
	  XDrawLine(display_ptr, win, gc, win_width /10, 9*win_height/ 10,
                   9*win_width/10, 9*win_height/10 );
    XDrawLine(display_ptr, win, gc, 9*win_width /10, 9*win_height/ 10,
                   9*win_width/10, win_height/10 );
	  XDrawLine(display_ptr, win, gc_red, 9*win_width /10, 9*win_height/ 10,
                   9*win_width/10,8* win_height/10 );
    XDrawLine(display_ptr, win, gc_red, 9*win_width /10, 9*win_height/ 10,
                   9*win_width/10,8* win_height/10 );*/
                   
                   for (i=0;i<number_obst;i++){
                   Drawtri(gc,obstx[0][i],obsty[0][i],obstx[1][i],obsty[1][i],obstx[2][i],obsty[2][i]);
                   }

                   Drawtri(gc,start.x+ve.a.x,start.y+ve.a.y,start.x+ve.b.x,start.y+ve.b.y,start.x+ve.c.x,start.y+ve.c.y);
                
                for(list<Tri>::iterator it=ans.begin();it!=ans.end();it++){
                vehicle venew=ve;

        venew.a=rotation(ve.a,it->z);
        venew.b=rotation(ve.b,it->z);
        venew.c=rotation(ve.c,it->z);
        Drawtri(gc_red,it->x+venew.a.x,it->y+venew.a.y,it->x+venew.b.x,it->y+venew.b.y,it->x+venew.c.x,it->y+venew.c.y);
                }

          break;
        case ConfigureNotify:
          /* This event happens when the user changes the size of the window*/
          win_width = report.xconfigure.width;
          win_height = report.xconfigure.height;
          break;
       /* case ButtonPress:
          /* This event happens when the user pushes a mouse button. I draw
            a circle to show the point where it happened, but do not save 
            the position; so when the next redraw event comes, these circles
	    disappear again. 
          {  
             int x, y;
  	     x = report.xbutton.x;
             y = report.xbutton.y;
             if (report.xbutton.button == Button1 )
	        XFillArc( display_ptr, win, gc_red, 
                       x -win_height/40, y- win_height/40,
                       win_height/20, win_height/20, 0, 360*64);
             else
	        XFillArc( display_ptr, win, gc_yellow, 
                       x - win_height/40, y - win_height/40,
                       win_height/20, win_height/20, 0, 360*64);

          }
          break;*/
        default:
	  /* this is a catch-all for other events; it does not do anything.
             One could look at the report type to see what the event was */ 
          break;
	}

    }
  exit(0);

}