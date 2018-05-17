// Ren Jeik Ong 5343975

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deltas.h"

void print_graph(int *data, int len, int max_height){
    printf("%s %d \n", "length:", len);
    int min=100000;
    int max=0;

    for (int i=0; i< len; i++){
        if(data[i] < min ){
            min = data[i];              // calculation for minimum element
        }
        if(data[i] > max){
            max = data[i];              // calculation for maximum element
        }
    }
    int range = max-min;                // calculation for range
    float units_per_height = (range*1.0/max_height*1.0);    // calculation for unit per height

    printf("%s %d \n", "min:", min);
    printf("%s %d \n", "max:", max);
    printf("%s %d \n", "range:", range);
    printf("%s %d \n", "max_height:", max_height);
    printf("%s %.2f \n", "units_per_height:", units_per_height);

    int remainder = len%5;
    int divide = len/5;

    printf("%s ", "    ");                      //starting with +----
    for(int i=0; i<divide; i++){                //starting with +----
        printf("%s", "+----");                  //starting with +----
    }                                           //starting with +----
    if(len%5 !=0){                              //starting with +----
        printf("%s", "+");                      //starting with +----
    }                                           //starting with +----
    for(int i=1; i< remainder; i++){            //starting with +----  //print the remainders of "+----"
        printf("%s", "-");                      //starting with +----
    }                                           //starting with +----
    printf("\n");                               //starting with +----
    printf("%s ", "     ");                     //starting with +----
    printf("\n");                               //starting with +----

    for (int row = max_height ; row>=0 ; row--){   // Iteration for printing the graph to the output
        int out = min + row * units_per_height;
        printf("%3d |", out);                       //print the column numbers according to the unit per height
        for (int col=0; col<len; col++){
            if(data[col]>= out){
                printf("%s", "X");
            }
            else{
                printf("%s", " ");
            }
        }
        printf("\n");
    }
    
    printf("%s ", "    ");                      //ending with +----
    for(int i=0; i<divide; i++){                //ending with +----
        printf("%s", "+----");                  //ending with +----
    }                                           //ending with +----
    if(len%5 !=0){                              //ending with +----
        printf("%s", "+");                      //ending with +----
    }                                           //ending with +----
    for(int i=1; i< remainder; i++){            //ending with +----  //print the remainders of "+----"
        printf("%s", "-");                      //ending with +----
    }                                           //ending with +----
    printf("\n");                               //ending with +----
    printf("%s ", "     ");
    for(int i=0; i<len; i=i+5){                 //print the row numbers with unit per height of 5
        printf("%d", i);
        if(i < 10){
            printf("%s ", "   ");
        }
        else if (i>=10 && i<100){
            printf("%s ", "  ");
        }
        else{
            printf("%s ", " ");
        }
    }
    printf("\n");
}
