#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define N 3

int main(){
	int A[N][N], B[N][N], C[N][N], D[N][N];
	#pragma omp parallel num_threads(10)
	{
		int *prA,*prB,*prC,*prD;
		int i,j;
		#pragma omp single
		{
			
			for(i=0;i<N;i++){
				printf("Row %d",i+1);
				for(j=0;j<N;j++)
					scanf("%d",&A[i][j]);
				printf("\n");
			}
			for(i=0;i<N;i++){
				for(j=0;j<N;j++)
					scanf("%d",&B[i][j]);
				printf("\n");
			}
		
		}
		#pragma omp sections
		{
			#pragma omp section
		{
//			#pragma omp parallel for private(j) num_threads(N)
			for(int i=0;i<N;i++){
				for(j=0;j<N;j++){
//					#pragma omp critical{
						D[i][j]=A[i][j]+B[i][j];
//					}
				}
			}
		}
		#pragma omp section
		{
			for(int i=0;i<N;i++){
				for(j=0;j<N;j++){
					C[i][j]=0;
					for(int k=0;k<N;k++)
						C[i][j] += A[i][k]*B[k][j];
				}
			}
		}
		}
//		#pragma omp task
//		{
//			#pragma omp parallel for private(j) num_threads(N)
//			for(int i=0;i<N;i++){
//				for(j=0;j<N;j++){
//					#pragma omp critical{
//						prD[i][j]=prA[i][j]+prB[i][j];
//					}
//				}
//			}
//		}
		#pragma omp taskwait
		
		#pragma omp master
		{
			printf("Thread id %d\n",omp_get_thread_num());
			printf("Addition:\n");
			for(i=0;i<N;i++){
				for(j=0;j<N;j++)
					printf("%d\t",D[i][j]);
				printf("\n");
			}
			printf("\nMul:\n");
			for(i=0;i<N;i++){
				for(j=0;j<N;j++)
					printf("%d\t",C[i][j]);
				printf("\n");
			}
		}
	}
	return 0;
}
