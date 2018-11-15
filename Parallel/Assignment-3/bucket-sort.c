#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define SIZE 20

int minpos(int [], int);
void sort(int [], int);


void main() {
	int rank, size, i, j, arr[SIZE], receive;
    	float ans = 0.0;
    	MPI_Init(NULL, NULL);
    	MPI_Status status;
    	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if(rank == 0){
		for(i=0; i<SIZE; i++) {
			arr[i] = rand() % SIZE;
		}
		int min = arr[0];
	        int max = arr[0];
	       	for(i=0; i < SIZE; i++) {
	                if(arr[i] < min) { min = arr[i]; }

	                if(arr[i] > max) { max = arr[i]; }

	       }
		int element[size];
		for(int d=1; d < size; d++) {
	                element[d] = 0;
	        }
		for(int d=0; d < SIZE; d++) {
	                int inc = max/(size-1);
	                int itr = 1;
	                bool flag2 = false;
	                for(j = inc; j <= max; j = j + inc) {
	                    if(arr[d] <= j) {
	                        element[itr]++;
	                        flag2 = true;
	                        break;
	                    }
	                    itr++;
	                }
	                if (!flag2) {
	                    element[itr-1]++;
	                }
	       }
		for(int i=1; i<size; i++) {
	                MPI_Send(&element[i], 1, MPI_INT, i, 2, MPI_COMM_WORLD);
	            }
		for(int d=0; d < SIZE; d++) {
	                int inc = max/(size-1);
	                int itr = 1;
	                bool flag = false;
	                for ( j = inc; j <= max; j = j + inc) {
	                    if(arr[d] <= j) {
	                        MPI_Send(&arr[d], 1, MPI_INT, itr, 4, MPI_COMM_WORLD);
	                        flag = true;
	                        break;
	                    }
	                    itr++;
	                }
	                if (!flag) {
	                    MPI_Send(&arr[d], 1, MPI_INT, itr-1, 4, MPI_COMM_WORLD);
	                }
	            }
		int lastIndex = 0, ind = 0, last;
	            for(i=1; i < size; i++) {
	                int recvArray[element[i]];
	                MPI_Recv(&recvArray[0], element[i], MPI_INT, i, 5, MPI_COMM_WORLD, &status);
	                if(last == 0) {
	                    last = element[i];
	                }
	                for(int j=0; j<element[i]; j++) {
	                    arr[ind] = recvArray[j];
	                    ind++;
	                }
	            }
			for(int c = 0 ; c < SIZE ; c++)  {
	                	printf("%d ",arr[c]);
	            }
	}
	 else {
	            int newsize; 
	         
	            MPI_Recv(&newsize, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
	            int localArray[newsize]; 
	 	 for(int li = 0; li < newsize; li++) {
	                MPI_Recv(&receive, 1, MPI_INT, 0, 4, MPI_COMM_WORLD, &status);
	                localArray[li] =  receive;
	            }
		sort(localArray,newsize);

		MPI_Send(localArray, newsize, MPI_INT, 0, 5, MPI_COMM_WORLD);
	 }
		
	MPI_Finalize();
}

int minpos(int array[], int size) {
   int i, min = 0;
   for (i=0; i<size; i++)
      min = array[i] > array[min] ? i: min;
   return min;
}

void sort(int arr[],int  size){
   int i, min;
   int tmp;

   for(i= size; i > 1; i--) 
   {
      min = minpos(arr, i);
      tmp = arr[min];
      arr[min] = arr[i-1];
      arr[i-1] = tmp;
   }
}
