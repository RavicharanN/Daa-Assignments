#include<stdio.h>
#include<time.h>
#include<stdlib.h>
float time_eval = 0;  // Calcluate the time of execution

// Generates a random matrix.
int ** createMatrix(int n) {
  int i,j;
  int **matrix = (int **)malloc(n*sizeof(int*)) ;
  srand(time(0));
  for(i = 0;i<n;i++) {
    time_eval += 3;
    matrix[i] = (int *)malloc(n*(sizeof(int)));
    for(j = 0;j<n;j++) {
      time_eval += 4;
      matrix[i][j] = rand()%10;
    }
  }
  return matrix;
}

// Prints the matrix
void printMatrix(int **matrix,int n) {
  int i,j;
  for(i = 0;i<n;i++) {
    time_eval += 3;
    for(j = 0;j<n;j++) {
      time_eval += 4;
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
  return;
}

void swap(int *xp, int *yp)
{
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
  time_eval += 3;
}

// Uses bubble sort.
void sortArray(int *arr,int n) {
  int i, j;
  for (i = 0; i < n-1; i++)        
    for (j = 0; j < n-i-1; j++) 
      if (arr[j] > arr[j+1])
        swap(&arr[j], &arr[j+1]);
  time_eval += n*n;
}

// Recursive function to check the traversabilty.
int recFunc(int **statusMatrix,int **matrix,int *a,int k,int i, int j,int n) { 
  if(a[k] == a[n*n - 1]) { // OPtimisation for the best case.
    time_eval += 1;
    return 1;              // If all the elements in the subMatrix are equal,then return without calling the recursive function
  }
  statusMatrix[i][j] = 1;  // If the elements is visited, then mark the corresponding entry in the matrix as 1.
  int flag = 0;
  time_eval += 2;
  if(k == 8) {
    time_eval += 1;
    return 1;
  }
    
  if( (i+1<n) && (statusMatrix[i+1][j]!=1) && (matrix[i+1][j] == a[k]) ) { // down
    printf("i+1\n");
    flag = recFunc(statusMatrix,matrix,a,k+1,i+1,j,n);
    time_eval += 4;
    if(flag) 
      return 1;
  }
  if( (i-1>=0) && (statusMatrix[i-1][j]!=1) && (matrix[i-1][j] == a[k]) ) { //up
    printf("i-1\n");
    flag = recFunc(statusMatrix,matrix,a,k+1,i-1,j,n);
    time_eval += 4;
    if(flag)
      return 1; 
  }
  if( (j+1<n) && (statusMatrix[i][j+1]!=1) && (matrix[i][j+1] == a[k]) ) { //right
    printf("j+1\n");
    flag = recFunc(statusMatrix,matrix,a,k+1,i,j+1,n);
    time_eval += 4;
    if(flag)
      return 1;
  }
  if( (j-1>=0) && (statusMatrix[i][j-1]!=1) && (matrix[i][j-1] == a[k]) ) {  //left
    printf("j-1\n");
    flag = recFunc(statusMatrix,matrix,a,k+1,i,j-1,n);
    time_eval += 4;
    if(flag)
      return 1;
  }
  statusMatrix[i][j] = 0;
  time_eval += 1;
  return 0;
}

// Creates necessary elements for the recursive function.
int isTraversable(int **matrix,int n) {
  int least,i,j,k,count;
  int *least_row = (int *)malloc((n*n + 1)*sizeof(int));
  int *least_col = (int *)malloc((n*n + 1)*sizeof(int));
  int *a = (int *)malloc(n*n*sizeof(int)); 
  int **statusMatrix = (int **)malloc(n*sizeof(int *)); // Status matrix keeps track of the visisted elements.
  
  for(i = 0;i<n;i++) {
    time_eval += 4;
    statusMatrix[i] = (int *)malloc(n*(sizeof(int)));
    for(j = 0;j<n;j++) {
      time_eval += 4;
      statusMatrix[i][j] = 0;
    }
  }
  count  = 0;
  least_row[count] = 0;  // Stores the row index of the least number in the matrix.
  least_col[count] = 0;  // Stores the col index of the least number in the matrix.
  least = 11;     // Val of the least element in the matrix.
  k = 0;
  time_eval += 4;
  for(i = 0;i<n;i++) {
    time_eval += 3;
    for(j = 0;j<n;j++) {
      time_eval += 4;
      a[k] = matrix[i][j];  // Store every entry in an array.
      if(matrix[i][j] < least) {
        count = 0;
        least_row[count] = i;
        least_col[count] = j;
        least = matrix[i][j];
        time_eval += 5;
      }
      else if(matrix[i][j] == least) {
        count ++; //maintaining count o
        least_row[count] = i;
        least_col[count] = j;
        time_eval += 4; 
      }
      k++;
    }
  } // The position of the least element is obtained.

  sortArray(a,n*n);    // Sorts the array
  if(a[0] == a[n*n-1]) 
    return 1;   

  if(count > 1) {
    time_eval += 1;
    for(i = 0;i<=count;i++) {
      time_eval += 4;
      return recFunc(statusMatrix,matrix,a,1,least_row[count],least_col[count],n);
    }
  }

  return recFunc(statusMatrix,matrix,a,1,least_row[0],least_col[0],n);  // return the result returned by the recursive function.
}

void passMatrix(int **matrix,int n,int k) {
  int i,j;
  int **a = (int **)malloc(k*sizeof(int *));
  for(i = 0;i<k;i++) 
    a[i] = (int *)malloc(k*sizeof(int));
  for(i = 0;i<=n-k;i++) {
    time_eval += 3;
    for(j = 0;j<=n-k;j++) { 
      time_eval += 3;
      // Push into a.
      int id_row = i;
      int id_col = j;
      int m_i,m_j,a_i,a_j;
      for(m_i = id_row,a_i=0;m_i<id_row+3;m_i++,a_i++) {
        time_eval += 5;
        for(m_j = id_col,a_j = 0;m_j<id_col+3;m_j++,a_j++) {
          time_eval += 5;
          a[a_i][a_j] = matrix[m_i][m_j];
        }
      }
      // end of block.
      // Print the passed matrix 
      // printf("\n");
      // for(a_i = 0;a_i<k;a_i++) {
      //   time_eval += 3;
      //   for(a_j = 0;a_j<k;a_j++) {
      //     time_eval += 3; 
      //     printf("%d ",a[a_i][a_j]);
      //   }
      //   printf("\n");
      // }
      // End of block
      int res = isTraversable(a,k); 
      time_eval += 1;
      // printf("%d\n",res);
      if(res) {
        printf("Topleft element of the travesable matrix (%d,%d)\n",i,j);
      }
      // end of for loop
    }
  } 
}

int main(int argc, char const *argv[]) {
  int **matrix;
  int n,i,j;
  scanf("%d",&n);
  // matrix = createMatrix(n);
  // Custom input
  matrix = (int **)malloc(n*sizeof(int *));
  for(i = 0;i<n;i++) {
    matrix[i] = (int *)malloc(n*sizeof(int));
    for(j = 0;j<n;j++) 
      scanf("%d",&matrix[i][j]);
  } 
  // End Of block
  // Best CAse 
  // matrix = (int **)malloc(n*sizeof(int *));
  // for(i = 0;i<n;i++) {
  //   matrix[i] = (int *)malloc(n*sizeof(int));
  //   for(j = 0;j<n;j++) 
  //     matrix[i][j] = 5;
  // }
  // End of block
  printMatrix(matrix,n);
  passMatrix(matrix,n,3); // To-Do : Add a subMatrix generator fucntion 
  time_eval = time_eval/(float)100000;
  printf("\nThe time taken for computation is %f\n",time_eval);
  return 0;
}