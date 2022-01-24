#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<time.h>

int N;

int p[100][100];

void create(){
	int i,j;
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
	
	     {
                       int a=rand()%15;//Generate random numbers and assign them to the array
	       p[i][j]=a;
		 }
	}
}

void print()
{
	int i,j;
	for(i=0;i<N;i++)
    {
		for(j=0;j<N;j++)
			printf("%d ",p[i][j]);
		printf("\n");
	}
}

long long mydet(int  p [100][100],int n){
	 if(n==1) //n=1 returns the unique number of the matrix, stop recursion
		return p[0][0];
	else{
		long long sum=0;
		for(int i=0;i<n;i++)
		{
			     int pp[100][100];//Used to store one-dimensional matrices, which is directly defined as 100×100 for convenience.
			 for(int j=1,j1=0;j<n;j++)//remove the first line
			{
				for(int k=0,k1=0;k<n;k++)
				{
					if(k==i)
						 ;//Remove the corresponding column
					else
					{

				      pp[j1][k1]=p[j][k];//pp is the remainder	
					 k1++;
					}
				}
			    j1++;
			}
			if(i%2)
                sum+=(-1)*p[0][i]*mydet(pp,n-1);
			else
				sum+=p[0][i]*mydet(pp,n-1);
		}
		return sum;
	}
}

int main(){
	printf("N= ");
	scanf("%d",&N);
         while(N){ //If you enter N, you can continue to count. This design is mainly to facilitate the acquisition of time data to calculate the average time
		create();
		print();
		 clock_t start_t=clock(); //Start timing
		 printf("the sum of serial is %lld .\n",mydet(p,N));
	          clock_t end_t=clock(); //End timing
		double   runing_t =(double)(end_t-start_t)/CLOCKS_PER_SEC;
		 printf("the running time of serial is %f s.",runing_t); //output time
		printf("\n");
		printf("N= ");
		scanf("%d",&N);
	}
 
	return 0;
}
