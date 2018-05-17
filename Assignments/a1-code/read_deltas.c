// Ren Jeik Ong 5343975

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "deltas.h"

int *read_text_deltas(char *fname, int *len){
    FILE *file = fopen(fname,"r");
    if(file == NULL){   //if there's no file in directory
        *len = -1;
        return NULL;
    }
    else{
        int random;
        int length =0;
        int x=0;
        while(fscanf(file, "%d", &random ) !=EOF){      // calculate the number of text integers in the file
            length++;
        }
        if(length ==0){  //if there's no integer, return NULL
            *len = -1;
            fclose(file);
            return NULL;
        }
        rewind(file);                                   // start from the beginning of read file
        int *names = (int *)malloc(sizeof(int)*length); // allocate the memory according to the given length

        for(int j=0; j< length ; j++){
            fscanf(file, "%d", &names[j]);        // read the text integers  and store it into allocated array
            if (j !=0 ){
                names[j] = names[j] + names[j-1];   // math operations between 2 points
            }
        }
        *len = length;
        fclose(file);
        return names;
    }
}

int *read_int_deltas(char *fname, int *len){
    struct stat sb;                                    // struct to hold
    int result = stat(fname, &sb);                     // unix system call to determine size of named file
    if(result==-1 || sb.st_size < sizeof(int)){        // if something went wrong or bail if file is too small
        *len = -1;
        return NULL;
    }

    int total_bytes = sb.st_size;                      // size of file in bytes
    int *names = (int *)malloc(total_bytes);
    FILE *file = fopen(fname,"r");

    if( file == NULL){
      *len = -1;
      return NULL;
     }
    int integer_space = total_bytes/4;     // there's only n number of integer space to store within total_bytes

    for(int j=0; j<integer_space; j++){
        fread(&names[j], sizeof(int), 1, file); // read the binary integers  and store it into allocated array
        if ((j !=0 ) ){
            names[j] = names[j] + names[j-1];   // math operations between 2 points
        }
    }
    *len = integer_space;
    fclose(file);
    return names;
}
