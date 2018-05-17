// Ren Jeik Ong 5343975

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deltas.h"
void print_graph(int *, int, int);

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("usage: %s <format> <filename>\n",argv[0]);
        printf(" <format> is one of\n");
        printf(" text : text ints are in the given filename\n");
        printf(" int  : binary ints are in the given filename\n");
        printf(" 4bit : 4bit binary ints are in the given filename\n");
        return 1;
    }
    char *format = argv[1];
    char *fname = argv[2];
    int max_height = atoi(argv[3]);
    int data_len = -1;
    int *data_vals = NULL;

    if( strcmp("text", format)==0 ){  //check if the input type is text
        printf("Reading text format\n");
        data_vals = read_text_deltas(fname, &data_len); // store the array of data in data_vals
    }

    else if( strcmp("int", format)==0 ){  // check if the input type is int
        printf("Reading binary int format\n");
        data_vals = read_int_deltas(fname, &data_len); // store the array of data in data_vals
    }
    else{
        printf("Unknown format '%s'\n",format); //printf if the input type is invalid
        return 1;
    }

    print_graph(data_vals, data_len, max_height);  //call the print graph function with 3 arguments
    free(data_vals);                                // free the pointer data_vals once the print is done
    return 0;
}
