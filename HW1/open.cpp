int main(int argc, char**argv){
    FILE *inputfile;
    int vx[3],vy[3],startx,starty,startphi,targetx,targety,targetphi;
    int obstx[3][30],obsty[3][30],i,finished,number_obst;
    if(argc!=2){
        printf("need filename as command line argument.\n"); fflush(stdout);
        exit(0);
    }
    inputfile=fopen(argv[1],"r");
    if(fscanf(inputfile,"V(%d,%d) (%d,%d) (%d,%d)\n",&(vx[0]),&(vy[0]),&(vx[1]),&(vy[1]),&(vx[2]),&(vy[2]))!=6){
        printf("error in first line. \n");fflush(stdout);
        exit(0);
    }
    if(fscanf(inputfile,"S (%d,%d) %d\n", &startx,&starty,&startphi)!=3){
        printf("error in third line. \n"); fflush(stdout);
        exit(0);
    }
    if(fscanf(inputfle,"T(%d,%d) %d\n", &targetx,&targety,&targetph)!=3){
        prntf("error n second lne.\n");fflush(stdout);
        ext(0);
    }
    i=0; finished=0;
    while(i<30&&!finished){
        if(fscanf(inputfile,"0(%d,%d) (%d,%d) (%d,%d)\n",
        &(obstx[0][i]),&(obsty[0][i]),&(obstx[1][i]),&(obsty[1][i]),&(obstx[2][i]),&(obstx[2][i]))!=6)
        finished=1;
        else
        
            i+=1;
        }
        number_obst=i;
        printf("found %d obstacles. so far ok\n",i);
        
    
}