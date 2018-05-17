// Ren Jeik Ong 5343975

#include <stdio.h>  //HEADER
#include <string.h> //HEADER
#include "tree.h"   //HEADER

// global variable to control echoing, 0: echo off, 1: echo on
int ECHO = 0;

// Print the given string if echoing is turned on
void echo(char *s){
  if(ECHO){
    printf("%s",s);
  }
}

int main(int argc, char *argv[]){
  if(argc > 1 && strcmp("-echo",argv[1])==0){
    ECHO=1;
  }

  printf("BST Demo\n");
  printf("Commands:\n");
  printf("  print:          shows contents of the tree in sorted order\n");
  printf("  show:           shows contents in pre-order indicating its structure\n");
  printf("  clear:          eliminates all elements from the tree\n");
  printf("  quit:           exit the program\n");
  printf("  add <name>:     inserts the given string into the tree, duplicates ignored\n");
  printf("  find <name>:    prints FOUND if the name is in the tree, NOT FOUND otherwise\n");
  printf("  save <file>:    writes the contents of the tree in post order to the given file\n");
  printf("  load <file>:    clears the current tree and loads the one in the given file\n");

  char cmd[128];
  bst_t tree;
  int success;
  bst_init(&tree);

  while(1){
    printf("BST> ");                 // print prompt

    success = fscanf(stdin,"%s",cmd); // read a command
    if(success==EOF){
      break;                          // break from loop
    }

    if( strcmp("quit", cmd)==0 ){     // check for quit command
      echo("quit");echo("\n");
      printf("\n");
      break;                          // break from loop
    }
    else if( strcmp("add", cmd)==0 ){ // addition
      echo("add");
      fscanf(stdin,"%s",cmd);            // read string to insert
      echo(" ");echo(cmd); echo("\n");
      success = bst_insert(&tree, cmd);  // call bst_insert function
      // if(!success){                      // check for success
      //   printf("insert failed\n");
      // }
    }
    else if( strcmp("find", cmd)==0 ){     // find command
      echo("find");
      char index[128];
      fscanf(stdin,"%s",index);          // read string
      echo(" ");echo(index);echo("\n");
      int ith = bst_find(&tree, index);  // call bst_find function

      if (ith == 1){                    // check for success
        printf("FOUND\n");
      }else if(ith == 0){
        printf("NOT FOUND\n");
      }
    }
    else if( strcmp("clear", cmd)==0 ){   // clear command
      echo("clear"); echo("\n");
      bst_clear(&tree);
    }
    else if( strcmp("print", cmd)==0 ){   // print command
      echo("print");echo("\n");
      //echo(" ");
      bst_print_inorder(&tree);
    }
    else if( strcmp("show", cmd)==0 ){   // show command
      echo("show");echo("\n");
      bst_print_preorder(&tree);
    }
    else if(strcmp("save", cmd)==0){
      echo("save");
      fscanf(stdin,"%s",cmd);            // read string to save the file
      echo(" ");echo(cmd); echo("\n");
      bst_save(&tree, cmd);             // call bst_save function
    }
    else if(strcmp("load", cmd)==0){
      echo("load");
      fscanf(stdin,"%s",cmd);            // read string to load the file
      echo(" ");echo(cmd); echo("\n");
      bst_load(&tree, cmd);             // call bst_load function

    }
    else{                                 // unknown command
      printf("unknown command %s\n",cmd);
    }
  }
  // end of while loop
  bst_clear(&tree);                      // clean up the bst
  return 0;
}
