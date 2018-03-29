#include<stdio.h>
#include<stdlib.h>

int binary_search(int A[], int beg, int end, int value)
{
	int mid;

	mid = (beg + end) / 2;
	if (beg > end && A[mid] != value) {
		return 0;
	} 
    else if (A[mid] == value) {
		return mid;
	} 
    else if (A[mid] > value) {
		return binary_search(A, beg, (mid - 1), value);
	} 
    else {
		return binary_search(A, (mid + 1), end, value);
	}

}

void merge_arr(int A[], int p, int q, int r)
{ 
	int L[1000];
	int R[1000];
	int nL; 
	int nR;
	int i;
	int j;
	int k;

	nL = q - p + 1;
	nR = r - q;
	i = 0;
	j = 0;

	for (i = p, j = 0; j < nL; i++, j++) {
		L[j] = A[i];
	}
	
	for (i = (q + 1), j = 0; j < nR; i++, j++) {
		R[j] = A[i];
	}

	for (i = 0, j = 0, k = p; (k < r) && (i < nL) && (j < nR); k++) {
		if (L[i] <= R[j]) {
			A[k] = L[i];
			i++;
		} else {
			A[k] = R[j];
			j++;
		}
	} 

	if (i < nL) {
		for (; i < nL; i++, k++) {
			A[k] = L[i];
		}
	} else {
		for (; j < nR; j++, k++) {
			A[k] = R[j];
		}
	}
}

void merge_sort(int A[], int p, int r)
{
	int q;

	if (p < r) {
		q = ((p + r) / 2);
		merge_sort(A, p, q);
		merge_sort(A, (q + 1), r);
		merge_arr(A, p, q, r);
	}
}

void union_and_int(int *small_arr,int *large_arr, int size_small, int size_large) {

    int *union_arr = (int *)malloc( (size_small+size_large)*sizeof(int) );
    int *intersection_arr = (int *)malloc( (size_small)*sizeof(int) );
    int res,i;
    int union_count, intersection_count;

    for( i = 0; i < size_small; i++ ) 
        printf("%d ",small_arr[i]);
    printf("\n");

    for( i = 0; i < size_large; i++ ) 
        printf("%d ",large_arr[i]);
    printf("\n");
    

    for (i = 0; i<size_large; i++) {
       res = binary_search(small_arr, 0, size_small-1, large_arr[i]);
       printf("%d \n",res);
       if(res) {
           intersection_arr[intersection_count] = large_arr[i];
           intersection_count++;
       } 
       else {
           union_arr[union_count] = large_arr[i];
           union_count++;
       }
    }
    // for(i = 0; i < size_small; i++) {
    //     union_arr[union_count] = small_arr[i];
    // } 

    // Printing union 
    // for(i = 0; i < union_count; i++) {
    //     printf("%d ",union_arr[i]);
    // }

    // // Printing intersection
    // for(i = 0; i < intersection_count; i++) {
    //     printf("%d ", intersection_arr[i]);
    // }
}


int main() {
    int i,j,n,m;
    
    scanf("%d", &n);
    int *a1 = (int *)malloc(n*sizeof(int));
    for (i = 0; i < n; i++) {
        scanf("%d", &a1[i]);
    }

    scanf("%d", &m);
    int *a2 = (int *)malloc(m*sizeof(int));
    for (i = 0; i < m; i++) {
        scanf("%d", &a2[i]);
    }
 
    if(n < m) { // If a1 is smaller.
        merge_sort(a1, 0, n-1);
        union_and_int(a1, a2, n, m);    
    }

    else { // If a2 is smaller.
        merge_sort(a2, 0, m-1);
        union_and_int(a2, a1, m, n);
    }

}