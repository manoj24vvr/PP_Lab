#include <stdio.h>
#include <omp.h>

void selection_sort(int arr[], int n) {
    int i, j, min_idx;
    #pragma omp parallel for private(i, j, min_idx) shared(arr, n)
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        #pragma omp critical
        {
            if (min_idx != i){
            	int temp = arr[i];
            	arr[i] = arr[min_idx];
            	arr[min_idx] = temp;
			}
        }
    }
}

int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr)/sizeof(arr[0]);

    selection_sort(arr, n);
	int i,j;
    printf("Sorted array: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
