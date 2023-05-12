#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

#define N 500

int NUM_THREADS=4;

struct compare{
	int index;
	int val;
};

//#pragma omp declare reduction(minimum: struct compare: omp_out = omp_in.val < omp_out.val? omp_in : omp_out)
//reduction(minimum:min)
int swap(int *a,int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void selection_sort(int *arr){
	for(int i=0;i<N-1;i++){
		struct compare min;
		min.val = arr[i];
		min.index = i;
		#pragma omp parallel for default(none) shared(arr,i,min) num_threads(NUM_THREADS)
		for(int j=i+1;j<N;j++){
			if(arr[j] < min.val){
				#pragma omp flush(min)
				min.val = arr[j];
				min.index = j;
				#pragma omp flush(min)
			}
		}
		swap(&arr[i],&arr[min.index]);
	}
}

int main(){
	int i,j,min;
	int arr[N],arr2[N];
	time_t st,end;
	double tseq=0,tpar=0,speedup,eff;
//	printf("Enter the array(size-%d): ",N);
	srand(time(NULL));
	for(i=0;i<N;i++){
		arr[i] = rand() % 10;
		arr2[i] = arr[i];
//		scanf("%d",&arr[i]);
	}
	
	printf("The Input array: \n");
	for(i=0;i<N;i++){
		printf("%d\t",arr2[i]);
	}
	// Sequential Execution
	st = time(NULL);
	for(i=0;i<N;i++){
		struct compare min;
		min.val = arr2[i];
		min.index = i;
		for(j=i+1;j<N;j++){
			if(arr2[j]<min.val){
				min.val = arr2[j];
				min.index = j;
			}
		}
		swap(&arr2[i],&arr2[min.index]);
	}
	end = time(NULL);
	printf("Start- %li\t End- %li\n",(long int)st,(long int)end);
	tseq = (long int)(end - st);
	
	printf("\nThe Sequentially sorted array: \n");
	for(i=0;i<N;i++){
		printf("%d\t",arr2[i]);
	}
	
	printf("\nParallel starting....\n");
	// Parallel Execution
	st = time(NULL);
	selection_sort(arr);
	end = time(NULL);
	
	printf("The Parallely sorted array: \n");
	for(i=0;i<N;i++){
		printf("%d\t",arr[i]);
	}

	tpar = (long int)(end - st);
	speedup = tseq/tpar;
	eff = speedup/NUM_THREADS;
	printf("\nSequential Execution Time: %.5f s\n",tseq);
	printf("Parallel Execution Time: %.5f s\n",tpar);
	printf("SpeedUp: %.2f\n",speedup);
	printf("Efficiency: %.2f\n",eff);
	return 0;
}
