#include <stdio.h>
#include<math.h>

int main()
{
	 int k,i;
	 double x;
	scanf("%d",&k);
	scanf("%lf",&x);

	double ans = log(x/(x-1));
	double sum = 0;

	if(x == 1)
	{
		printf("sum is infinity\n");
		printf("actual sum is %lf\n",ans);
	}
	else
	{
		for(i = 1; i <= k; i++)
		{
			sum += (1/(i * pow(x,i)));
		}

		printf("sum is %lf\n",sum);
		printf("actual sum is %lf\n",ans);
	}


	return 0;
	
}


//their code
// #include<stdio.h>
// #include<math.h>
// int main()
// {
// 	int k;
// 	scanf("%d",&k);
// 	double x;
// 	scanf("%lf",&x);
// 	double dom = (x)/(x-1);
// 	double actual = log(dom);
// 	double sum=0;
// 	double inv = 1/(x);
// 	double poly = 1/(x);
// 	for(int i=1;i<=k;i++)
// 	{
// 		double invv = (double)((double)(1)/(double)(i));
// 		sum  = sum + invv*poly;
// 		poly = poly*inv;
// 		if(i!=k)
// 			printf("1/(%d*x^%d) + ",i,i);
// 		else
// 			printf("1/(%d*x^%d) \n",i,i);
// 	}
// 	printf("%lf %lf",sum,actual);
// }