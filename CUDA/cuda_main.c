#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<mpi.h>

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
					if(k==i)
						;
					else
					{

				     pp[j1][k1]=p[j][k];	
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



int main(int argc,char *argv[]){  
	  scanf("%d",&N);
    // [(...) CUDA implementation]
    return 0;  
}  
