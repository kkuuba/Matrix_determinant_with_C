#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<omp.h>

#define n_threads 4

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
		    int pp[100][100];
			 for(int j=1,j1=0;j<n;j++)//remove the first line
			{
				for(int k=0,k1=0;k<n;k++)
				{
					 if(k==i)//Remove the same column as the number
						;
					else
					{

				      pp[j1][k1]=p[j][k]; //pp is the algebraic remainder
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
         while(N){ //If the input N>0, continue to calculate
		 create(); //Create matrix
		 print(); //Print the created matrix
		  double start1,finish1;
                                         start1=omp_get_wtime(); //Start calculating time
                    long long sum=0;
                           omp_set_num_threads(n_threads);//Set the number of threads
                       #pragma omp parallel for reduction(+:sum)//Parallelization
       for(int i=0;i<N;i++)
		{
		    int pp[100][100];
			 for(int j=1,j1=0;j<N;j++)//Remove the first line
			{
				for(int k=0,k1=0;k<N;k++)
				{
					 if(k==i)//Remove the same column as i
						;
					else
					{

				      pp[j1][k1]=p[j][k]; //pp is the remainder
					 k1++;
					}
				}
			    j1++;
			}
			if(i%2)
				sum+=(-1)*p[0][i]*mydet(pp,N-1);
			else
				sum+=p[0][i]*mydet(pp,N-1);
		}
                 printf("the sum of omp is %lld .\n",sum);//output result
	     finish1=omp_get_wtime(); //End calculation time
		double   runing_t =finish1-start1;
		 printf("the running time of opm is %f s.",runing_t);//output time
		printf("\n");
		printf("N= ");
		scanf("%d",&N);
	}
	return 0;
	}
