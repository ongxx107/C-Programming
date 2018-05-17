#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "search.h"

int main(int argc, char *argv[]){
  if (argc == 1){
    printf("%s \n", "usage: ./search_benchmark <minpow> <maxpow> <repeats> [which]");
    printf("%s \n", " which is a combination of:");
    printf("%s \n", "  a : Linear Array Search");
    printf("%s \n", "  l : Linked List Search");
    printf("%s \n", "  b : Binary Array Search");
    printf("%s \n", "  t : Binary Tree Search");
    printf("%s \n", "  (default all)");
    return 0;
  }
  if (argc == 5){
    int min   = atoi(argv[1]);
    int max   = atoi(argv[2]);
    int repeats   = atoi(argv[3]);
    char * which = argv[4];

    int do_linear_array   = 0;
    int do_linked_list    = 0;
    int do_binary_search  = 0;
    int do_tree_search    = 0;

    printf("%s", "  LENGTH SEARCHES" );

    if ( strchr(which, 'a') ){
      do_linear_array  = 1;
      printf("%s", "      array" );
    }
    if ( strchr(which, 'l') ){
      do_linked_list = 1;
      printf("%s", "       list" );
    }
    if ( strchr(which, 'b') ){
      do_binary_search = 1;
      printf("%s", "     binary" );
    }
    if ( strchr(which, 't') ){
      do_tree_search   = 1;
      printf("%s", "       tree" );
    }
    printf("\n");

    int min2 = 1 << min;   //2 ^ min
    int max2 = 1 << max;   // 2^ max

    clock_t begin, end;

    for (int i = min2; i<= max2; i*=2 ){

         printf("%8d %8d ", i, i*repeats*2);
         if(do_linear_array){
           // setup array

           int *arr = make_sequential_array(i);
           for (int p = 0; p<i ; p++){
             pb_srand(185184985);
             arr[p] = pb_rand();
           }


           // start timer
            //begin = clock();
           double norm_cpu_time = 0;
           for(int j=0; j< repeats; j++){ // search every query form arr[low] to arr[high]
              //  // setup array
              //  int *arr = make_sequential_array(i);
              //  // start timer
               begin = clock();

               // do
               // int linear_array_search(int array[], int len, int query
               int x=0;

               for (; x < i/2; x++){                   //success queries
                  linear_array_search(arr, i, x);
                  linear_array_search(arr, i, x+(i/2));
               }
               x = -1;

               for (; x >= (i/2)*(-1); x--){             //failed queries
                 linear_array_search(arr, i, x);
                 linear_array_search(arr, i, x-(i/2));
               }

               end = clock();
               norm_cpu_time += ((double) (end - begin)) / CLOCKS_PER_SEC;

             }

           // stop timer
          //  end = clock();
          //  // print output
          //  double norm_cpu_time = 0;
          //  norm_cpu_time += ((double) (end - begin)) / CLOCKS_PER_SEC;
           printf("%10.4e ", norm_cpu_time );
           // free the array
           free(arr);
         }
         if(do_linked_list){
           // setup array
           list_t *lst = make_sequential_list(i);

           double norm_cpu_time = 0;

           for(int j=0; j< repeats; j++){ // search every query form arr[low] to arr[high]
               begin = clock();
               int x=0;

               for (; x < i/2; x++){                   //success queries
                  linkedlist_search(lst, i, x);
                  linkedlist_search(lst, i, x+(i/2));
               }
               x = -1;

               for (; x >= (i/2)*(-1); x--){             //failed queries
                 linkedlist_search(lst, i, x);
                 linkedlist_search(lst, i, x-(i/2));
               }

               end = clock();
               norm_cpu_time += ((double) (end - begin)) / CLOCKS_PER_SEC;

             }
           printf("%10.4e ", norm_cpu_time );
           // free the array
           list_free(lst);
         }
         if(do_binary_search){
           // setup array
           int *arr = make_sequential_array(i);

           double norm_cpu_time = 0;
           for(int j=0; j< repeats; j++){ // search every query form arr[low] to arr[high]

               begin = clock();

               int x=0;

               for (; x < i/2; x++){                   //success queries
                  binary_array_search(arr, i, x);
                  binary_array_search(arr, i, x+(i/2));
               }
               x = -1;

               for (; x >= (i/2)*(-1); x--){             //failed queries
                 binary_array_search(arr, i, x);
                 binary_array_search(arr, i, x-(i/2));
               }

               end = clock();
               norm_cpu_time += ((double) (end - begin)) / CLOCKS_PER_SEC;

             }
           printf("%10.4e ", norm_cpu_time );
           // free the array
           free(arr);
         }
         if(do_tree_search){
           // setup array
           bst_t *t = make_sequential_tree(i);

           double norm_cpu_time = 0;
           for(int j=0; j< repeats; j++){ // search every query form arr[low] to arr[high]

               begin = clock();

               int x=0;

               for (; x < i/2; x++){                   //success queries
                  binary_tree_search(t, i, x);
                  binary_tree_search(t, i, x+(i/2));
               }
               x = -1;

               for (; x >= (i/2)*(-1); x--){             //failed queries
                 binary_tree_search(t, i, x);
                 binary_tree_search(t, i, x-(i/2));
               }

               end = clock();
               norm_cpu_time += ((double) (end - begin)) / CLOCKS_PER_SEC;

             }
           printf("%10.4e ", norm_cpu_time );
           // free the array
           bst_free(t);
         }
        printf("\n");
      }


    return 0;
  }
  else{
    int min   = atoi(argv[1]);
    int max   = atoi(argv[2]);
    int repeats   = atoi(argv[3]);

    int do_linear_array   = 1;
    int do_linked_list    = 1;
    int do_binary_search  = 1;
    int do_tree_search    = 1;

    printf("%s", "  LENGTH SEARCHES" );
    printf("%s", "      array" );
    printf("%s", "       list" );
    printf("%s", "     binary" );
    printf("%s", "       tree" );
    printf("\n");

    int min2 = 1 << min;
    int max2 = 1 << max;

    clock_t begin, end;

    for (int i = min2; i<= max2; i*=2 ){

         printf("%8d %8d ", i, i*repeats*2);
         if(do_linear_array){
           // setup array
           int *arr = make_sequential_array(i);

           double norm_cpu_time = 0;
           for(int j=0; j< repeats; j++){ // search every query form arr[low] to arr[high]

               begin = clock();
               int x=0;

               for (; x < i/2; x++){                   //success queries
                  linear_array_search(arr, i, x);
                  linear_array_search(arr, i, x+(i/2));
               }
               x = -1;

               for (; x >= (i/2)*(-1); x--){             //failed queries
                 linear_array_search(arr, i, x);
                 linear_array_search(arr, i, x-(i/2));
               }

               end = clock();
               norm_cpu_time += ((double) (end - begin)) / CLOCKS_PER_SEC;

             }
           printf("%10.4e ", norm_cpu_time );
           // free the array
           free(arr);
         }
         if(do_linked_list){
           // setup array
           list_t *lst = make_sequential_list(i);

           double norm_cpu_time = 0;
           for(int j=0; j< repeats; j++){ // search every query form arr[low] to arr[high]
               begin = clock();
               int x=0;

               for (; x < i/2; x++){                   //success queries
                  linkedlist_search(lst, i, x);
                  linkedlist_search(lst, i, x+(i/2));
               }
               x = -1;

               for (; x >= (i/2)*(-1); x--){             //failed queries
                 linkedlist_search(lst, i, x);
                 linkedlist_search(lst, i, x-(i/2));
               }

               end = clock();
               norm_cpu_time += ((double) (end - begin)) / CLOCKS_PER_SEC;

             }
           printf("%10.4e ", norm_cpu_time );
           // free the array
           list_free(lst);
         }
         if(do_binary_search){
           // setup array
           int *lst = make_sequential_array(i);

           double norm_cpu_time = 0;
           for(int j=0; j< repeats; j++){ // search every query form arr[low] to arr[high]

               begin = clock();

               int x=0;

               for (; x < i/2; x++){                   //success queries
                  binary_array_search(lst, i, x);
                  binary_array_search(lst, i, x+(i/2));
               }
               x = -1;

               for (; x >= (i/2)*(-1); x--){             //failed queries
                 binary_array_search(lst, i, x);
                 binary_array_search(lst, i, x-(i/2));
               }

               end = clock();
               norm_cpu_time += ((double) (end - begin)) / CLOCKS_PER_SEC;

             }
           printf("%10.4e ", norm_cpu_time );
           // free the array
           free(lst);
         }
         if(do_tree_search){
           // setup array
           bst_t *t = make_sequential_tree(i);

           double norm_cpu_time = 0;
           for(int j=0; j< repeats; j++){ // search every query form arr[low] to arr[high]

               begin = clock();

               int x=0;

               for (; x < i/2; x++){                   //success queries
                  binary_tree_search(t, i, x);
                  binary_tree_search(t, i, x+(i/2));
               }
               x = -1;

               for (; x >= (i/2)*(-1); x--){             //failed queries
                 binary_tree_search(t, i, x);
                 binary_tree_search(t, i, x-(i/2));
               }

               end = clock();
               norm_cpu_time += ((double) (end - begin)) / CLOCKS_PER_SEC;

             }
           printf("%10.4e ", norm_cpu_time );
           // free the array
           bst_free(t);
         }
        printf("\n");
      }
    return 0;
  }

}
