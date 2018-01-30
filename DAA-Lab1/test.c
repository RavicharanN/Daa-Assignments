
#include<stdio.h>
struct alpha{
int x;
int flag;
}arr[1000];
int n,time;
void fnc()//function for finding length of longest sorted subarray and printing them
{
    int i,max1 = 1,max2=1, len1 = 1, len2 = 1,maxIndex1 = 0,maxIndex2=0;time++;//declaring and initializing variables
    time++;
    for (i=1; i<n; i++)
    {
	time+=3;        
	if (arr[i].x >= arr[i-1].x)//longest increasing subarray
            {
		len1++;time++;
	    }
        else
        {
            time++;
            if (max1 < len1)    
            {
                max1 = len1;time+=2;
                maxIndex1 = i - max1;
            }
 	    len1 = 1;time++;    
        }    
    }
    time++;
    if (max1 < len1)
    { 
        max1 = len1;
        maxIndex1 = n - max1;time+=2;
    }
    time++;
    for (i=1; i<n; i++)
    {
	time+=3;        
	if (arr[i].x <= arr[i-1].x)//longest decreasing subarray
            {
		len2++;
		time++;
	    }
        else
        {
            time++;
            if (max2 < len2)    
            {
                max2 = len2;
                maxIndex2 = i - max2;time+=2;
            }
   	    len2 = 1;time++;    
        }    
    }
    time++;
    if (max2 < len2)
    { 
        max2 = len2;
        maxIndex2 = n - max2;time+=2;
    }
    time++;
    if(max1>=max2)
	{
		printf("Longest sorted partition length = %d nature : increasing ",max1);//length of longest sorted subarray (increasing)		
		printf("Elements are : ");
                time++;		
		for(i=maxIndex1;i<max1+maxIndex1;i++)
			{
				time+=2;				
				if(arr[i].flag==0)
					printf("%c ",arr[i].x);
				else
					printf("%c ",arr[i].x-32);
			}
		printf("\n");
	}
	else
	{
		printf("Longest sorted partition length = %d nature : decreasing ",max2);//length of longest sorted subarray (decreasing)		
		printf("Elements are : ");
		time++;		
		for(i=maxIndex2;i<max2+maxIndex2;i++)
			{
				time+=3;				
				if(arr[i].flag==0)
					printf("%c ",arr[i].x);
				else
					printf("%c ",arr[i].x-32);
			}
		printf("\n");
	}	
}
int main(int c,char *argv[])
{	
	freopen(argv[1],"r",stdin);	
	int t;	
	scanf("%d",&t);
	while(t--)
	{time=0;
	scanf("%d",&n);time++;//Enter n
	int i,j;//Declaration of variables
	struct alpha a[n][n];	
	char c;
	time++;
	for(i=0;i<n;i++)
	{
		time+=3;		
		for(j=0;j<n;j++)
			{
				time+=2;				
				c=getchar();time+=2;//Input elements of matrix
				if((int)c==32||(int)c==10)
				{
					j--;time++;
					continue;
				}
				time++;
				if((int)c<97)
					{
						a[i][j].x=(int)c+32;time+=2;//for uppercase alphabets
						a[i][j].flag=1;time++;
					}
				else								
					{
						a[i][j].x=(int)c;time++;//Store characters as integers
						a[i][j].flag=0;time++;
					}
			}
	}
        printf("ROWS:\n");
	time++;
	for(i=0;i<n;i++)
	{
		time+=3;	
		for(j=0;j<n;j++)
			{
				arr[j]=a[i][j];time+=3;//Array for every row
			}
		printf("row number : %d \n",i+1);
		time++;
		fnc();//Calling function for longest sorted partition of rows
	}
	printf("diagonals:\n");
	printf("Primary diagonal\n");
	time++;
	for(i=0;i<n;i++)
		{
			arr[i]=a[i][i];time+=3;//array for primary daigonal
		}
	fnc();//Calling function for longest sorted partition of primary diagonal
	printf("Secondary diagonal\n");
	time++;
	for(i=0;i<n;i++)
		{
			arr[i]=a[i][n-i-1];time+=3;//array for secondary diagonal
		}
	fnc();//Calling function for longest sorted partition of secondary diagonal
	printf("Total time taken : %d \n",time);
	FILE *fp = fopen(argv[2],"a");
	fprintf(fp,"%d %d \n",n,time);
	}	
	return 0;
}
