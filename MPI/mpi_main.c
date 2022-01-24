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
      int num_procs,my_rank;    
             double start = 0.0, stop = 0.0; //variable for recording time
             long long per_procs = 0.0; //Record the sum of each process
             long long result = 0.0; //Matrix determinant result
      MPI_Init(&argc, &argv);  
      MPI_Comm_size(MPI_COMM_WORLD, &num_procs);  
      MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);  
      if (my_rank == 0)
	   {//Thread No. 0 creates matrix
        create(); 
                 print(); //Print the created matrix
       }  
           start = MPI_Wtime(); //Start calculating time
 
             MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD); //Broadcast the matrix size to all processes  
      for (int i = 0; i <N; i++)
	  {  
      MPI_Bcast(p[i],N, MPI_INT, 0, MPI_COMM_WORLD);  
             } // Broadcast the matrix to all processes  
   
             for (int i = my_rank; i <N; i += num_procs){ //Each thread processes different rows and columns 
            long long sum_i=0;
		    int pp[100][100];
			 for(int j=1,j1=0;j<N;j++)//Remove the first line
			{
		    	for(int k=0,k1=0;k<N;k++)
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
                sum_i=(-1)*p[0][i]*mydet(pp,N-1);
      else
		sum_i=p[0][i]*mydet(pp,N-1);
                 per_procs += sum_i; //Record the sum of each process
    }  
         MPI_Reduce(&per_procs, &result, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);//Sum in process 0  
    if (my_rank == 0){  
        printf("the sum of mpi is %lld .\n",result) ; 
                 stop = MPI_Wtime(); //End calculation time
        printf("the time of mpi is %f s\n", stop - start);  
        fflush(stdout);  
    }  
    MPI_Finalize();
    return 0;  
}  
