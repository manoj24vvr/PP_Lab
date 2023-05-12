#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

#define N 10


void insertion_sort(int *arr,int start,int last){
	for(int i=start+1;i<last;i++){
		int key = arr[i];
		int j = i-1;
		
		while(key <arr[j] &&j>=0){
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = key;
	}	
}

void swap(int *a,int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int *arr,int low, int high){
	int pivot = arr[high];
	int i=(low-1);
	
	for(int j=low;j<high;j++){
		if(arr[j]<pivot)
			swap(&arr[++i],&arr[j]);
	}
	
	swap(&arr[i+1],&arr[high]);
	return (i+1);
}

void quick_sort(int *arr, int start, int end){
	if(start < end){
		int pvt = partition(arr,start,end);
		
		quick_sort(arr,start, pvt-1);
		quick_sort(arr,pvt+1,end);
	}
}

void merge(int *arr,int l, int r){
	int m = N/2;
	int i,j,k;
	int n1 = m, n2= r-m;
	
	int t1[n1], t2[n2];
	
	for(i=0;i<n1;i++)
		t1[i] = arr[l+i];
	for(i=0;i<n2;i++)
		t2[i] = arr[m+i];
		
	i=0;j=0;k=0;
// 4       8       9       6       4       0       6       5       2       9  	
	while(i < n1 && j < n2){
		if(t1[i] <= t2[j]){
			arr[k] = t1[i];
			i++;
		}
		else{
			arr[k] = t2[j];
			j++;
		}
		k++;
	}
	
	while(i<n1){
		arr[k] = t1[i];
		i++;
		k++;
	}
	
	while(j<n2){
		arr[k] = t2[j];
		j++;
		k++;
	}
}

int main(){
	int i,j,min;
	double st,end,tseq=0,tpar=0,speedup,eff;
//	printf("Enter the array(size-%d): ",N);
	int arr[N];
	srand(time(NULL));
	for(i=0;i<N;i++){
		arr[i] = rand() % 10;
//		scanf("%d",&arr[i]);
	}
	
	printf("\nThe Input array: \n");
	for(i=0;i<N;i++){
		printf("%d\t",arr[i]);
	}
	
	#pragma omp parallel sections num_threads(2)
	{
		#pragma omp section
		insertion_sort(arr,0,N/2);
		
		#pragma omp section
		quick_sort(arr,N/2,N);	
	}
	printf("\nMerging...\n");
	printf("\nPartially Sorted array: \n");
	for(i=0;i<N;i++){
		printf("%d\t",arr[i]);
	}
	merge(arr,0,N);
	
	printf("\nThe Sorted array: \n");
	for(i=0;i<N;i++){
		printf("%d\t",arr[i]);
	}
	return 0;
}
