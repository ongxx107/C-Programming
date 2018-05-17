#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <math.h>

#define BUFSIZE 128
#define NSTAGES 10

int main(int argc, char **argv){
          char* input = "444555666";
          long a = atol(input);

          char ans[9] = {};
         for(int i=0; i<8; i++){
            ans[i] = (char) (a >> (7*i) & 0x7F);
            printf("%ld\n", a );
          }

          char *accept = "Victory!";
          if(strcmp(ans,accept)==0){
            printf("         '%s' seems very appropriate. Congrads!\n",ans);
          }


          printf("%s\n", "faill" );
        }
