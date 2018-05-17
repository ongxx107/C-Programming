#include "matvec.h"
#include <stdlib.h>

int optimized_matrix_trans_mult_vec(matrix_t mat, vector_t vec, vector_t res){

  // store these struct element type into local variables that reduce calls
  long vecLen = vec.len;        // store the vector length to local variable
  long resLen = res.len;        // store the result(vec) length to local variable
  long rows = mat.rows;         // store the row length to local variable
  long cols = mat.cols;         // store the column length to local variable

  /*
  check if the length of column matches with vector length for matrix multi.
  */
  if(cols != vecLen){
    printf("mat.cols (%ld) != vec.len (%ld)\n",cols,vecLen);
    return 1;
  }

  /*
  check if the length of row matches with result length for matrix multi.
  */
  if(rows != resLen){
    printf("mat.rows (%ld) != res.len (%ld)\n",rows,resLen);
    return 2;
  }

  for(int i=0; i<resLen; i++){  // iteration vector which is 1-D array
    VSET(res,i,0);              // initialize res[i] to zero
  }

  /*
  This is row major matrix such that we start the computation through row by
  row so it takes less time and less jump as the next entry is stored in cache.
  In inner loop, we compute each row multiplication with 4 entries. Thus,
  we have j+=4 compared to j++ which runs every matrix entry individually in a
  single loop.
  */
  for(int i=0; i<rows; i++){
    int j;
    for( j=0; j<cols-4; j+=4){
      int vecj = VGET(vec,i);	  // reuse vecj since they all are the same entry

      int elij = MGET(mat,i,j);
      int prod = elij * vecj;
      int curr = VGET(res, j);
      int next = curr + prod;
      VSET(res,j, next);          // add on the newest product

      int elij1 = MGET(mat,i,j+1);
      int prod1 = elij1 * vecj;
      int curr1 = VGET(res, j+1);
      int next1 = curr1 + prod1;
      VSET(res,j+1, next1);        // add on the newest product

      int elij2 = MGET(mat,i,j+2);
      int prod2 = elij2 * vecj;
      int curr2 = VGET(res, j+2);
      int next2 = curr2 + prod2;
      VSET(res,j+2, next2);        // add on the newest product

      int elij3 = MGET(mat,i,j+3);
      int prod3 = elij3 * vecj;
      int curr3 = VGET(res, j+3);
      int next3 = curr3 + prod3;
      VSET(res,j+3, next3);        // add on the newest product
    }
    // do the remainder if the matrix isn't 2^n
    // do the cleanup if the array is reached the end
    for(; j<cols; j++){
      int elij1 = MGET(mat,i,j);
      int vecj1 = VGET(vec,i);
      int prod1 = elij1 * vecj1;
      int curr1 = VGET(res, j);
      int next1 = curr1 + prod1;
      VSET(res,j, next1);          // add on the newest product
    }

  }
  return 0;
}
