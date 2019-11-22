#include <iostream>
#include <string>
#include <vector>
using namespace::std;



bool equals(string large,int start,string small){

    for(int i=0;i<small.length();i++){
        if(large.at(i+start)!=small.at(i)){
            return false;
        }
    }
    return true;
} 

int moduleHash(int hash,int addition, int prime, int largePrime){
    return (hash*prime%largePrime+addition)%largePrime;
}
int nonNegative(int hash, int largePrime){
    if(hash<0){
        hash+=largePrime;
    }
    return hash;
}
int strsrii(string large,string small){
        if(large.length()<small.length()){
            return -1;
        }
        if (small.length()==0){
            return 0;
        }
        int largePrime = 10001;
        int prime = 31;
        int seed = 1;
        int targetHash = small.at(0)%largePrime;
        for (int i=1;i<small.length();i++){
            seed = moduleHash(seed,0,prime,largePrime);
            targetHash = moduleHash(targetHash,small.at(i),prime,largePrime);

        }

        int hash=0;
        for(int i=0;i<small.length();i++){
            hash = moduleHash(hash,large.at(i),prime,largePrime);

        }
        if(hash == targetHash && equals(large,0,small)){
            return 0;
        }
        for (int i=1;i<large.length()-small.length();i++){
            hash = nonNegative(hash - seed*large.at(i-1)%largePrime,largePrime);
            hash =moduleHash(hash,large.at(i+small.length()-1),prime,largePrime);
            
            if (hash==targetHash && equals(large,i,small)){
            return i;
            }
        } 
        return -1;
}    

int multi_string_match(int k, char *forbidden_strings,int n, char *input_string){
                                    string large = "";
                                    for(int z = 0; z < n; z++){
                                        large+= input_string[z];
                                    }
                                for (int i=0;i<k;i++){
                                    string small = "";
                                    for(int j = 0; j < 7; j++){
                                        small += forbidden_strings[i*8+j];
                                    }
                                        int ss=strsrii(large,small);
                                    if(ss!=-1){
                                        return ss;
                                    }else{
                                        continue;
                                    }
                                }
                                return -1;

                            
};


int main()
{   char *teststring;
    int i, j; 
    char *forbidden;
    
    teststring = (char *) malloc( 1000000* sizeof(char) );
    for(i=0; i< 1000000; i++ )
    {  switch( i%7 )
       {  case 0 : teststring[i] = 'a'; break;
          case 1 : teststring[i] = 'a'; break;
          case 2 : if (rand()%2==0 ) teststring[i] = 'b'; 
	           else teststring[i] = 'c'; break;
          case 3 : switch(rand()%3)
	           { case 0: teststring[i] = 'a'; break;
	             case 1: teststring[i] = 'b'; break;
	             case 2: teststring[i] = 'c'; break;
                     default: printf("?1.\n"); fflush(stdout); break;
                   } break;
          case 4 : if (rand()%2==0 ) teststring[i] = 'b'; 
	           else teststring[i] = 'c'; break;
          case 5 : switch(rand()%3)
	           { case 0: teststring[i] = 'a'; break;
	             case 1: teststring[i] = 'b'; break;
	             case 2: teststring[i] = 'c'; break;
                     default: printf("?2.\n"); fflush(stdout); break;
                   } break;
          case 6 : if (rand()%2==0 ) teststring[i] = 'b'; 
	           else teststring[i] = 'c'; break;
         default: printf("This should not happen.\n"); fflush(stdout); break;
       }
    }
    printf("Prepared teststring. It starts like \n");
    for(i=0; i<70; i++)
      printf("%c", teststring[i]);
    printf("\n");
    forbidden = (char *) malloc( 16*81* sizeof(char) );
    for(i=0; i<81; i++)
    {  forbidden[8*i] = forbidden[8*i+1]=forbidden[8*i+2] = 'a';
       switch( i%3 )
       { case 0: forbidden[8*i+3] = 'a'; break;
	 case 1: forbidden[8*i+3] = 'b'; break;
	 case 2: forbidden[8*i+3] = 'c'; break;
       }
       switch( (i/3)%3 )
       { case 0: forbidden[8*i+4] = 'a'; break;
	 case 1: forbidden[8*i+4] = 'b'; break;
	 case 2: forbidden[8*i+4] = 'c'; break;
       }
       switch( (i/9)%3 )
       { case 0: forbidden[8*i+5] = 'a'; break;
	 case 1: forbidden[8*i+5] = 'b'; break;
	 case 2: forbidden[8*i+5] = 'c'; break;
       }
       switch( (i/27)%3 )
       { case 0: forbidden[8*i+6] = 'a'; break;
	 case 1: forbidden[8*i+6] = 'b'; break;
	 case 2: forbidden[8*i+6] = 'c'; break;
       }
       forbidden[8*i+7] = '\0';
    }
    for(i=0; i<81; i++)
    {  forbidden[8*i + 81*8] = forbidden[8*i+1 + 81*8]= 'a';
       switch( i%3 )
       { case 0: forbidden[8*i+2 + 81*8] = 'a'; break;
	 case 1: forbidden[8*i+2 + 81*8] = 'b'; break;
	 case 2: forbidden[8*i+2 + 81*8] = 'c'; break;
       }
       switch( (i/3)%3 )
       { case 0: forbidden[8*i+3+81*8] = 'a'; break;
	 case 1: forbidden[8*i+3+81*8] = 'b'; break;
	 case 2: forbidden[8*i+3+81*8] = 'c'; break;
       }
       forbidden[8*i+4 + 81*8]= 'a';
       switch( (i/9)%3 )
       { case 0: forbidden[8*i+5+81*8] = 'a'; break;
	 case 1: forbidden[8*i+5+81*8] = 'b'; break;
	 case 2: forbidden[8*i+5+81*8] = 'c'; break;
       }
       switch( (i/27)%3 )
       { case 0: forbidden[8*i+6+81*8] = 'a'; break;
	 case 1: forbidden[8*i+6+81*8] = 'b'; break;
	 case 2: forbidden[8*i+6+81*8] = 'c'; break;
       }
       forbidden[8*i+7+81*8] = '\0';
    }
    printf("Prepared forbidden strings. They start like \n");
    for(i=0; i<20; i++)
       printf("%s\n", forbidden+ (8*i) );
    printf("\n");
    printf("Forbidden strings have the form aaaxyzw or aaxyazw\n");
    
    printf("Now call multi_string_match()\n");
    j = multi_string_match(81*2, forbidden, 1000000, teststring );
    if( j == -1 )
      printf("Passed first test\n");
    else
    {  printf("found %c%c%c%c%c%c%c at position %d. Is it forbidden?\n",
                teststring[j], teststring[j+1], teststring[j+2], 
                teststring[j+3], teststring[j+4], teststring[j+5],
                teststring[j+6]); fflush(stdout);
    }
    /* now modify teststring */
    teststring[7*123456 + 2] = 'a';
    printf("Call multi_string_match() again\n");
    j = multi_string_match(81*2, forbidden, 1000000, teststring );
    if( j == -1 )
      printf("Failed second test\n");
    else
    {  printf("found %c%c%c%c%c%c%c at position %d. Is it forbidden?\n",
                teststring[j], teststring[j+1], teststring[j+2], 
                teststring[j+3], teststring[j+4], teststring[j+5],
	      teststring[j+6], j); fflush(stdout);
    }
  
    exit(0);
} 

