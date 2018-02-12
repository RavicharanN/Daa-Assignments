#include<stdio.h>
#include<time.h>
#include<stdlib.h>

// Generates a random matrix.
int ** createMatrix(int n) {
  int i,j;
  int **matrix = (int **)malloc(n*sizeof(int*)) ;
  srand(time(0));
  for(i = 0;i<n;i++) {
    matrix[i] = (int *)malloc(n*(sizeof(int)));
    for(j = 0;j<n;j++)
      matrix[i][j] = rand()%10;
  }
  return matrix;
}

// Prints the matrix
void printMatrix(int **matrix,int n) {
  int i,j;
  for(i = 0;i<n;i++) {
    for(j = 0;j<n;j++) {
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
}

// Uses bubble sort.
void sortArray(int *arr,int n) {
  int i, j;
  for (i = 0; i < n-1; i++)        
    for (j = 0; j < n-i-1; j++) 
      if (arr[j] > arr[j+1])
        swap(&arr[j], &arr[j+1]);
}

// Recursive function to check the traversabilty.
int recFunc(int **statusMatrix,int **matrix,int *a,int k,int i, int j,int n) { 
  if(a[k] == a[n*n - 1]) { // OPtimisation for the best case.
    return 1;              // If all the elements in the subMatrix are equal,then return without calling the recursive function
  }
  
  statusMatrix[i][j] = 1;  // If the elements is visited, then mark the corresponding entry in the matrix as 1.
  int flag = 0;
  if(k == 8) 
    return 1;
  if( (i+1<n) && (statusMatrix[i+1][j]!=1) && (matrix[i+1][j] == a[k]) ) { // down
    printf("i+1\n");
    flag = recFunc(statusMatrix,matrix,a,k+1,i+1,j,n);
    if(flag) 
      return 1;
  }
  if( (i-1>=0) && (statusMatrix[i-1][j]!=1) && (matrix[i-1][j] == a[k]) ) { //up
    printf("i-1\n");
    flag = recFunc(statusMatrix,matrix,a,k+1,i-1,j,n);
    if(flag)
      return 1; 
  }
  if( (j+1<n) && (statusMatrix[i][j+1]!=1) && (matrix[i][j+1] == a[k]) ) { //right
    printf("j+1\n");
    flag = recFunc(statusMatrix,matrix,a,k+1,i,j+1,n);
    if(flag)
      return 1;
  }
  if( (j-1>=0) && (statusMatrix[i][j-1]!=1) && (matrix[i][j-1] == a[k]) ) {  //left
    printf("j-1\n");
    flag = recFunc(statusMatrix,matrix,a,k+1,i,j-1,n);
    if(flag)
      return 1;
  }
  statusMatrix[i][j] = 0;
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
    statusMatrix[i] = (int *)malloc(n*(sizeof(int)));
    for(j = 0;j<n;j++) {
      statusMatrix[i][j] = 0;
    }
  }
  count  = 0;
  least_row[count] = 0;  // Stores the row index of the least number in the matrix.
  least_col[count] = 0;  // Stores the col index of the least number in the matrix.
  least = 11;     // Val of the least element in the matrix.
  k = 0;
  for(i = 0;i<n;i++) {
    for(j = 0;j<n;j++) {
      a[k] = matrix[i][j];  // Store every entry in an array.
      if(matrix[i][j] < least) {
        count = 0;
        least_row[count] = i;
        least_col[count] = j;
        least = matrix[i][j];
      }
      else if(matrix[i][j] == least) {
        count ++; //maintaining count o
        least_row[count] = i;
        least_col[count] = j;
      }
      k++;
    }
  } // The position of the least element is obtained.

  sortArray(a,n*n);    // Sorts the array
  if(a[0] == a[n*n-1]) 
    return 1;          
  if(count > 1) {
    for(i = 0;i<=count;i++) 
     return recFunc(statusMatrix,matrix,a,1,least_row[count],least_col[count],n);
  }

  return recFunc(statusMatrix,matrix,a,1,least_row[0],least_col[0],n);  // return the result returned by the recursive function.
}

void passMatrix(int **matrix,int n,int k) {
  int i,j;
  int **a = (int **)malloc(k*sizeof(int *));
  for(i = 0;i<k;i++) 
    a[i] = (int *)malloc(k*sizeof(int));
  for(i = 0;i<=n-k;i++) {
    for(j = 0;j<=n-k;j++) { 
      // Push into a.
      int id_row = i;
      int id_col = j;
      int m_i,m_j,a_i,a_j;
      for(m_i = id_row,a_i=0;m_i<id_row+3;m_i++,a_i++) {
        for(m_j = id_col,a_j = 0;m_j<id_col+3;m_j++,a_j++) {
          a[a_i][a_j] = matrix[m_i][m_j];
        }
      }
      // end of block.
      printf("\n");
      for(a_i = 0;a_i<k;a_i++) {
        for(a_j = 0;a_j<k;a_j++) 
          printf("%d ",a[a_i][a_j]);
        printf("\n");
      }
      int res = isTraversable(a,k);
      printf("%d\n",res);
      if(res) {
        printf("left - %d, right - %d",i,j);
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
  matrix = (int **)malloc(n*sizeof(int *));
  for(i = 0;i<n;i++) {
    matrix[i] = (int *)malloc(n*sizeof(int));
    for(j = 0;j<n;j++) 
      scanf("%d",&matrix[i][j]);
  } 
  printMatrix(matrix,n);
  
  passMatrix(matrix,n,3); // To-Do : Add a subMatrix generator fucntion 
  return 0;
}