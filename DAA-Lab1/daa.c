#include<stdio.h>
#include<stdlib.h>
#include<time.h>
float time_eval = 0;  // Time eval computes the total time spent on computation

#define RED   "\x1B[31m"  // Define terminal colors.
#define GRN   "\x1B[32m"  
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"    

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
void findPartition(int *a,int n) {
  int indexAscendSort_first[111],indexAscendSort_second[111];
  int indexDescendSort_first[111],indexDescendSort_second[111];
  int n_aSort = 1, n_dSort = 1;
  int tempFirst,tempSecond,tempSize;
  int ka = 0,kd =0;
  int i,j;
  if(n == 1) {
    time_eval += 1;
    printf("None\n");
    return;
  }
  // Sorted in ascending order
  for(i = 0;i < n;i++) {
    if(n_aSort > n/2) {  // Optmize for best and avg cases.
      time_eval += 1;
      goto jump;
    } 
    tempFirst = i;
    tempSize = 1;
    for(j = i+1;j < n;j++) {
      time_eval += 3;
      if(a[j] >= a[j-1]) {
        tempSize++;
        tempSecond = j;
        time_eval += 3;
      }
      else
        break;
    }
    if(tempSize > n_aSort) {
      ka = 0;
      indexAscendSort_first[ka] = tempFirst;
      indexAscendSort_second[ka] = tempSecond;
      n_aSort = tempSize;
      time_eval += 5;
    }
    else if (tempSize == n_aSort) {
      ka++;
      indexAscendSort_first[ka] = tempFirst;
      time_eval += 1; // To locate the 'ka'th index. 
      indexAscendSort_second[ka] = tempSecond;  
      time_eval += 1; // To locate the 'ka'th index.
      time_eval += 4;
    }
  }
  // Sorted in descending order
  for( i = 0;i < n;i++) {
    time_eval += 3;
    if(n_dSort > n/2) { // Optimize for best case and avg case.
      time_eval += 1;
      goto jump;
    } 
    tempFirst = i;
    tempSize = 1;
    time_eval += 2;
    for( j = i+1;j < n;j++) {
      time_eval += 3;
      if( a[j] <= a[j-1] ) {
        time_eval += 3;
        tempSize++;
        tempSecond = j;
      }
      else
        break;
    }
    if(tempSize > n_dSort) {
      kd = 0;
      indexDescendSort_first[kd] = tempFirst;
      time_eval += 1;
      indexDescendSort_second[kd] = tempSecond;
      time_eval += 1;
      n_dSort = tempSize;
      time_eval += 5;
    }
    else if( tempSize == n_dSort) {
      kd++;
      indexDescendSort_first[kd] = tempFirst;
      time_eval += 1;
      indexDescendSort_second[kd] = tempSecond;
      time_eval += 1;
      time_eval += 4;
    }
  }
  
  jump: // Printing the longest sorted array.
  if(n_aSort >= n_dSort) {  
    time_eval += 1; 
    for(j = 0;j<=ka;j++) {
      time_eval += 3;
      for(i = indexAscendSort_first[j];i <= indexAscendSort_second[j];i++) {
        time_eval += 4;
        (i == indexAscendSort_second[j]) ? (printf("%d",a[i])) : (printf("%d,",a[i])); // Conditional_Statement - If i is on the last index do not print the ','.
      }   
      printf(BLU" -A.O \n"RESET);
    }
  }
  if (n_dSort >= n_aSort) {
    time_eval += 1;
    for(j = 0;j <= kd;j++) {
      time_eval += 3;
      for( i = indexDescendSort_first[j];i <= indexDescendSort_second[j];i++) {
        time_eval += 3; 
        (i == indexDescendSort_second[j]) ? (printf("%d",a[i])) : (printf("%d,",a[i])); // Conditional_Statement - If i is on the last index do not print the ','.
      }
      printf(BLU" -D.O \n"RESET);
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
    printf(GRN"Sorted Sequences for row %d :\n" RESET,i);
    findPartition(matrix[i],n);
  }
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
  time_eval += 1;
  printMatrix(matrix,n);
  printRowsSorted(matrix,n);
  printDiagonalSorted(matrix,n);
  time_eval = time_eval/(float)10000; 
  printf("Computed time %.4f units\n",time_eval);
  return 0;
}