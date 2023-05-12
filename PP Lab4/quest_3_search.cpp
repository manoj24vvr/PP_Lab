#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>

#define N 10

int idx=0;

int main(){
	int key,found=0,index[10];
	double st,end,tseq=0,tpar=0,speedup,eff;
//	printf("Enter the array(size-%d): ",N);
	int arr[N];
	srand(time(NULL));
	for(int i=0;i<N;i++){
		arr[i] = rand() % 10;
//		scanf("%d",&arr[i]);
	}
	
	printf("\nThe Input array: \n");
	for(int i=0;i<N;i++){
		printf("%d\t",arr[i]);
	}
	
	printf("\nEnter the search element: ");
	scanf("%d",&key);
	
	#pragma omp parallel for default(none) shared(arr,found,index,idx) firstprivate(key)
	for(int i=0;i<N;i++){
		if(arr[i]==key){
			found=1;
			#pragma omp critical
			{
				index[idx++]=i;
			}
		}
	}
	
	if(found){
		printf("%d found at the following indices: ",key);
		for(int i=0;i<idx;i++)
			printf("%d\t",index[i]);
	}
	else
		printf("%d not found\n",key);
	
	return 0;
}
