#include <stdio.h>
#include <stdlib.h>

int isMaxHeap(int *arr, int i, int n);
int isMinHeap(int *arr, int i, int n);

float timeEval = 0;

int main()
{
	int z;
	FILE * fp;
	fp = fopen("time.txt","w");

	for( z = 3;z<=70;z = z+2)  // Add to time.txt
	{
		int n,*arr,i;

		// scanf("%d",&n); // scan number of elements in the input	
		n = z;
		arr = (int *)malloc(n * sizeof(int));

		fprintf(fp,"%d ",n);

		// for (i = 0;i < n; ++i)
		// {
		// 	scanf("%d",&arr[i]);
		// 	timeEval += 3;
		// }

		for (i = 0;i<n;i++) {
			arr[i] = i;
		}

		if(isMaxHeap(arr,0,n))
		{
			printf("The given sequence of numbers form a max heap.\n");
		}
		else if(isMinHeap(arr,0,n))
		{
			printf("The given sequence of numbers form a min heap.\n");
		}
		else
		{
			printf("The given sequence of numbers doesn't form a heap.\n");
		}

		timeEval = timeEval/(float)100000;
		printf("The time taken for computation is %f\n",timeEval);

		fprintf(fp,"%f\n",timeEval);
		
	}

	fclose(fp);

	return 0;
}

int isMaxHeap(int *arr, int i, int n)
{
	if(i >= (n-2)/2)
	{
		timeEval += 1;
		return 1;		//if i is a leaf node, return true.
	}
	else
	{
		if(arr[i] >= arr[2*i + 1] && arr[i] >= arr[2*i + 2] && isMaxHeap(arr,2*i + 1,n) && isMaxHeap(arr,2*i + 2, n))
		{
			timeEval += 4;
			return 1;
		}
	}

	return 0;
}

int isMinHeap(int *arr, int i, int n)
{
	if(i >= (n-2)/2)
	{
		timeEval += 1;
		return 1;		//if i is a leaf node, return true.
	}
	else
	{
		if(arr[i] <= arr[2*i + 1] && arr[i] <= arr[2*i + 2] && isMinHeap(arr,2*i + 1,n) && isMinHeap(arr,2*i + 2, n))
		{
			timeEval += 4;
			return 1;
		}
	}

	return 0;
}