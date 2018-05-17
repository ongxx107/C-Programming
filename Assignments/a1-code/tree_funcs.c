// Ren Jeik Ong 5343975

#include <stdio.h>          //HEADER
#include <stdlib.h>         //HEADER
#include <string.h>         //HEADER
#include "tree.h"           // HEADER
void bst_init(bst_t *tree){ // Initialize the tree
    tree->root = NULL;
    tree->size = 0;
    return;
}
int bst_insert(bst_t *tree, char name[]){
    node_t *result = node_insert(tree->root, name);
    if(result == NULL){           // duplicate found, ignore
        return 0;                   // 0 indicates not modified
    }
    else{                         // successful insert
        tree->root = result;        // head may have changed
        tree->size++;               // size now larger
        return 1;                   // 1 indicates modifed
    }
}
node_t *node_insert(node_t *cur, char name[]){
    
    int result= node_find(cur, name);           // if duplicate is found, stop and return NULL
    if (result == 1){
        return NULL;
    }
   
    if(cur == NULL){                            // found insertion point where it reaches leaf node
        node_t *new_node = malloc(sizeof(node_t)); // allocate
        strcpy(new_node->name, name);          // copy data
        new_node->left = NULL;
        new_node->right = NULL;
        cur = new_node;
        return cur;                           // successful insert
    }
    else if(strcmp(name, cur->name) > 0){            // insertion point to the right
        cur->right = node_insert(cur->right, name);
    }
    else if(strcmp(name, cur->name) < 0){            // insertion point to the left
        cur->left = node_insert(cur->left, name);
    }
//    else {                                          // diff == 0 // duplicate
//        return NULL;
//    }
    return cur;
}
int bst_find(bst_t *tree, char name[]){     // find the input name in the tree
    return node_find(tree-> root, name);
}
int node_find(node_t *cur, char name[]){    // iterate every node from current node to search given name
    int result=0;
    if (cur!=NULL){
        if (strcmp(name, cur -> name) == 0){
            result=1;;
            return result;
        }
        else if (strcmp(name, cur -> name) > 0){
            return node_find(cur->right, name);
        }
        else{
            return node_find(cur->left, name);
        }
    }
    return result;
}
void bst_clear(bst_t *tree){        // free the memory and start everything fresh
    node_remove_all(tree-> root);
    tree->root = NULL;              // set root to NULL
    tree->size =0;                  // set size to 0
}
void node_remove_all(node_t *cur){   // free the memory recursively
    if (cur == NULL){               // base case: if the current pointer node hits the leaf node,
        return;                     // it will free the node and return back to parent node recursively
    }
    node_remove_all(cur->left);
    node_remove_all(cur->right);
    free(cur);
}
void bst_print_inorder(bst_t *tree){
    node_print_inorder(tree->root);
}
void node_print_inorder(node_t *cur){
    if (cur == NULL){               // base case: returns if cur hits lead node
        return;
    }
    node_print_inorder(cur->left);
    printf("%s \n", cur->name );
    node_print_inorder(cur->right);
}
void bst_print_preorder(bst_t *tree){
    node_write_preorder(tree->root, stdout, 0);
}
void bst_save(bst_t *tree, char *fname){
    FILE *file= fopen(fname, "w");             // open the fname and start writing
    node_write_preorder(tree->root, file, 0);
    fclose(file);
}
void node_write_preorder(node_t *cur, FILE *out, int depth){
    if(out != NULL){
        if (cur == NULL){                           //base case for preorder traversal
            depth--;
            return;
        }
        for (int spaces=0; spaces< depth;spaces++){
            fprintf(out,"%s", " ");                 // write the spaces into the file named out
        }
        fprintf(out,"%s \n", cur->name);            // write the names into the file named out
	depth++;        
	if (cur!=NULL){
          node_write_preorder(cur->left, out, depth);
          node_write_preorder(cur->right, out, depth);
        }
    }
}
int bst_load(bst_t *tree, char *fname ){            // open the existing file in the directory
    bst_clear(tree);
    char temp[128];
    FILE *file= fopen(fname, "r");
    while (fscanf(file, "%s", temp) != EOF) { //fscanf or scanf stop reading if they meet white space
        bst_insert(tree, temp);
    }
    fclose(file);
    return 0;
}
