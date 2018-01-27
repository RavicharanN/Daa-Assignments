#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"

// A function to generate a random matrix.
int **createMatrix(int n) {
  srand(time(0)); //Seed random number generator.
  int  **a = (int **)malloc(n * sizeof(int*)) ;
  int i,j;
  for(i = 0;i<n;i++){
    a[i] = (int *)malloc(n*sizeof(int));
    for(j = 0;j<n;j++){
      a[i][j] = rand()%100;
    }
  }
  return a;
}

void printMatrix(int ** matrix,int n) {
  int i,j;
  printf("\n");
  for(i = 0;i<n;i++) {
    for(j = 0;j<n;j++)
      printf("%2d ",matrix[i][j]);
    printf("\n");
  }
  return;
}

void findPartition(int *a,int n) {
  int indexAscendSort_first[111],indexAscendSort_second[111];
  int indexDescendSort_first[111],indexDescendSort_second[111];
  int n_aSort = 1, n_dSort = 1;
  int tempFirst,tempSecond,tempSize;
  int ka = 0,kd =0;
  int i,j;
  // Sorted in ascending order
  for(i = 0;i < n-1;i++) {
    tempFirst = i;
    tempSize = 1;
    for(j = i+1;j<n;j++) {
      if( a[j] >= a[j-1]) {
        tempSize++;
        tempSecond = j;
      }
      else
        break;
    }
    if(tempSize > n_aSort) {
      ka = 0;
      indexAscendSort_first[ka] = tempFirst;
      indexAscendSort_second[ka] = tempSecond;
      n_aSort = tempSize;
    }
    else if (tempSize == n_aSort) {
      ka++;
      indexAscendSort_first[ka] = tempFirst;
      indexAscendSort_second[ka] = tempSecond;  
    }
  }
  // Sorted in descending order
  for( i = 0;i<n-1;i++) {
    tempFirst = i;
    tempSize = 1;
    for( j = i+1;j<n;j++) {
      if( a[j] <= a[j-1] ) {
        tempSize++;
        tempSecond = j;
      }
      else
        break;
    }
    if(tempSize > n_dSort) {
      kd = 0;
      indexDescendSort_first[kd] = tempFirst;
      indexDescendSort_second[kd] = tempSecond;
      n_dSort = tempSize;
    }
    else if( tempSize == n_dSort) {
      kd++;
      indexDescendSort_first[kd] = tempFirst;
      indexDescendSort_second[kd] = tempSecond;
    }
  }
  // Print the longest sorted array
  if(n_aSort >= n_dSort) {  
    for(j = 0;j<=ka;j++) {
      for(i = indexAscendSort_first[j];i<=indexAscendSort_second[j];i++)
        printf("%d,",a[i]);
      printf("\n");
    }
  }
  if (n_dSort >= n_aSort) {
    for(j =0;j<=kd;j++) {
      for( i = indexDescendSort_first[j];i<=indexDescendSort_second[j];i++)
        printf("%d,",a[i]);
      printf("\n");
    }
  }
  return;
}

void printRowsSorted(int ** matrix,int n) {
  int i,j;
  printf("\n");
  for(i = 0;i<n;i++) {
    printf(BLU"Sorted Sequences for row %d :\n" RESET,i);
    findPartition(matrix[i],n);
  }
  return;
}

void printDiagonalSorted(int **matrix,int n) {
  int* b = (int *)malloc(n*sizeof(int));
  int* c = (int *)malloc(n*sizeof(int));
  int i,j;
  for(i = 0;i<n;i++) {
    b[i] = matrix[i][i];
    c[i] = matrix[i][n-i-1];
  }
  printf(YEL"First diagonal sorted list:\n"RESET);
  findPartition(b,n);
  printf(YEL"Second diagonal sorted list:\n"RESET);
  findPartition(c,n);
}

int main(int argc, char const *argv[]) {
  int n,i,j;
  scanf("%d",&n);
  int ** matrix;
  matrix = createMatrix(n);
  printMatrix(matrix,n);
  printRowsSorted(matrix,n);
  printDiagonalSorted(matrix,n);
  return 0;
}