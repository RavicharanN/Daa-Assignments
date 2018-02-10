#include<stdio.h>
#include<stdlib.h>
#include<time.h>
float time_eval = 0;  // Time eval computes the total time spent on computation
int rowArray[111][111];
int diagonalArray[111][111];

// A function to generate a random matrix.
int **createMatrix(int n) {
  srand(time(0)); // Seed random number generator.
  int  **a = (int **)malloc(n * sizeof(int*)) ; // Dynamic allocation
  int i,j;
  for(i = 0;i < n;i++){
    time_eval += 3;
    a[i] = (int *)malloc(n*sizeof(int));   // Allocate random integers to the spaces in the array
    for(j = 0;j < n;j++) {
       a[i][j] = rand()%100;
       time_eval += 3;
    }  
  }
  time_eval += 1;
  return a; 
}

// A funtion to print te matrix after creation
void printMatrix(int ** matrix,int n) {
  int i,j;
  printf("\n");
  for(i = 0;i < n;i++) {
    for(j = 0;j < n;j++) {
      time_eval += 3;
      printf("%2d ",matrix[i][j]);  // %2d is used to keep the rows aligned
    }
    printf("\n");
  }
  return;
}

// This function find the longest sorted sequence in an array.
// Todo : Add Algorithm 
void findPartition(int *a,int n,int num,int flag) {
  // num is the row number
  // Flag = 1 if rowArray is to be written.
  int ka = 0,kd =0;
  int *indexDescendSort_first = (int *)malloc((n)*sizeof(int)) ;
  int *indexAscendSort_first = (int *)malloc((n)*sizeof(int)) ;
  int n_aSort = 1, n_dSort = 1;
  int tempFirst,tempSize;
  int i,j;
  if(n == 1) {
    time_eval += 1;
    printf("None\n");
    return;
  }
  // Sorted in ascending order
  n_aSort = 1;
  ka = 0;
  tempSize = 1;
  tempFirst = 0; 
  time_eval += 4; 
  for(i = 1;i < n;i++) {
    time_eval += 3;
    if(a[i] >= a[i-1]) { // If in AO, increment the size.
      time_eval+=2;
      tempSize++;
    } 
    else {             // Else check cases.
      if(tempSize > n_aSort) {  
        ka = 0;        // Reset the counter to zero.
        n_aSort = tempSize;
        indexAscendSort_first[ka] = tempFirst;
        time_eval += 4;
      }
      else if(tempSize == n_aSort) {   
        ka++;         // Store in an array - Incrememnt the pointer.
        indexAscendSort_first[ka] = tempFirst;
        time_eval += 3;
      }
      tempSize = 1;   // Reset if AO is broken.
      tempFirst = i;  // Reset is AO is broken.
      time_eval  += 3;
    }
  }
  if(tempSize > n_aSort) {  // Store the indices if the loop never goes into the else statement.
    ka = 0;
    n_aSort = tempSize;
    indexAscendSort_first[ka] = tempFirst;
    time_eval += 4;
  }
  else if(tempSize == n_aSort) {
    ka++;
    indexAscendSort_first[ka] = tempFirst;
    time_eval += 3;
  }

  // Sorted in descending order
  n_dSort = 1;
  kd= 0;
  tempSize = 1;
  tempFirst = 0; 
  time_eval += 4;
  for(i = 1;i < n;i++) {
    time_eval += 3;
    if(a[i] <= a[i-1]) { // If in DO, increment the size.
      tempSize++;
      time_eval += 2;
    } 
    else {             // Else check cases.
      if(tempSize > n_dSort) {
        kd = 0;        // Reset the counter to zero.
        n_dSort = tempSize;
        indexDescendSort_first[kd] = tempFirst;
        time_eval += 4;
      }
      else if(tempSize == n_dSort) {
        kd++;         // Increment the counter.
        indexDescendSort_first[kd] = tempFirst;
        time_eval += 3;
      }
      tempSize = 1;   // Reset if DO is broken.
      tempFirst = i;  // Reset is DO is broken.
      time_eval += 2;
    }
  }
  if(tempSize > n_dSort) { // Store the indices if the loop never goes into the else statement.
    kd = 0;
    n_dSort = tempSize;
    indexDescendSort_first[kd] = tempFirst;
    time_eval += 4;
  }
  else if(tempSize == n_dSort) {
    kd++;
    indexDescendSort_first[kd] = tempFirst;
    time_eval += 3;
  }  
  // Printing the longest sorted array.
  if(n_aSort >= n_dSort) {  
    time_eval += 1; 
    for(j = 0;j<=ka;j++) {
      time_eval += 3;
      for(i = indexAscendSort_first[j];i < indexAscendSort_first[j]+n_aSort;i++) {
        time_eval += 4;
        if(flag == 1) {
          rowArray[num][i] = a[i];
        }
        else {
          // (i == indexAscendSort_first[j]+n_aSort-1) ? (printf("%d",a[i])) : (printf("%d,",a[i])); // Conditional_Statement - If i is on the last index do not print the ','.
          if(num==1) {
            diagonalArray[i][i] = a[i];
          }
          else {
            diagonalArray[i][n-i-1] = a[i];
          }
        }
          
      }   
      // printf(" -A.O \n");
    }
  }
  if (n_dSort >= n_aSort) {
    time_eval += 1;
    for(j = 0;j <= kd;j++) {
      time_eval += 3;
      for( i = indexDescendSort_first[j];i < indexDescendSort_first[j]+n_dSort;i++) {
        time_eval += 3; 
        if(flag == 1) {
          rowArray[num][i] = a[i];
        }
        else {
          if(num==1) {
            diagonalArray[i][i] = a[i];
          }
          else {
            diagonalArray[n-i-1][n-i-1] = a[i];
          }
        }
          // (i == indexDescendSort_first[j]+n_dSort-1) ? (printf("%d",a[i])) : (printf("%d,",a[i])); // Conditional_Statement - If i is on the last index do not print the ','.
      }
      // printf(" -D.O \n");
    }
  }
  return;
}

// Sends all the rows one after the other to the find partion function.
void printRowsSorted(int ** matrix,int n) {
  int i,j;
  printf("\n");
  for(i = 0;i < n;i++) {
    time_eval += 3;
    //printf("Sorted Sequences for row %d :\n",i);
    findPartition(matrix[i],n,i,1);
  }

  for(i = 0;i<n;i++) {
    for(j = 0;j<n;j++) {
      if(rowArray[i][j] == '*')
        printf("%c ",rowArray[i][j]);
      else 
        printf("%d ",rowArray[i][j]);
    }
    printf("\n");
  }
  printf("\n\n");
  return;
}

// Sends all the diagonals to the findPartion functions one after the other.
void printDiagonalSorted(int **matrix,int n) {
  int* b = (int *)malloc(n*sizeof(int));  // Dynamic allocation
  int* c = (int *)malloc(n*sizeof(int));  
  int i,j;
  time_eval += 2;
  for(i = 0;i < n;i++) {
    time_eval += 5;
    b[i] = matrix[i][i];      // First diagonal is stored in b. 
    c[i] = matrix[i][n-i-1];  // Second diagonal is sstored in c.
  }
  // printf("First diagonal sorted list:\n");
  findPartition(b,n,1,0);
  // printf("Second diagonal sorted list:\n");
  findPartition(c,n,2,0);
  for(i = 0;i<n;i++) {
    for(j = 0;j<n;j++) {
      if(diagonalArray[i][j] == '*')
        printf("%c ",diagonalArray[i][j]);
      else 
        printf("%d ",diagonalArray[i][j]);
    }
    printf("\n");
  }
  printf("\n\n");
  return;
}

void createRowmatrix(int n) {
  int i,j;
  for(i = 0;i<n;i++)
    for(j = 0;j<n;j++) 
      rowArray[i][j] = '*';
}

void createDiagonalMatrix(int n) {
  int i,j;
  for(i = 0;i<n;i++)
    for(j = 0;j<n;j++) 
      diagonalArray[i][j] = '*';
}

int main(int argc, char const *argv[]) {
  int n,i,j;
  scanf("%d",&n);
  int ** matrix;
  matrix = createMatrix(n);
  createRowmatrix(n);
  createDiagonalMatrix(n);

  // Block for best case
  // matrix = (int **)malloc(n * sizeof(int*)) ;
  // time_eval += 1; 
  // for(int i = 0;i<n;i++) {
  //   time_eval += 3;
  //   matrix[i] = (int *)malloc(n * sizeof(int)) ;
  //   for(j = 0;j<n;j++) {
  //     time_eval += 3;
  //     matrix[i][j] = j + 1;
  //   }
  // }
  // End of block

  // Block for worst case
  // matrix = (int **)malloc(n * sizeof(int*)) ;
  // time_eval += 1; 
  // for(int i = 0;i<n;i++) {
  //   time_eval += 4;
  //   matrix[i] = (int *)malloc(n * sizeof(int)) ;
  //   for(j = 0;j<n;j++) {
  //     time_eval += 4;
  //     matrix[i][j] = j%2 + 1;
  //   }
  // }
  //End of block

  time_eval += 1;
  printMatrix(matrix,n);
  printRowsSorted(matrix,n);
  printDiagonalSorted(matrix,n);
  time_eval = time_eval/(float)10000; 
  printf("Computed time %.4f units\n",time_eval);
  return 0;
}
