#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <windows.h>

void selectSort(int *x, int n){
    int max_index, tmp;
    for(int i = n - 1; i > 0; --i){
        max_index = i;
        for(int j = 0; j < i; ++j){
            if(x[j] > x[max_index])
                max_index = j;
        }
        tmp = x[max_index];
        x[max_index] = x[i];
        x[i] = tmp;
    }
}
void insertSort(int *x, int n){
    int save, tmp, i, j;
    for(i = 1; i < n; ++i){
        save = x[i];
        j = i-1;
        while ((j>=0) && (x[j] > save)){
            x[j+1] = x[j];
            --j;
        }
        x[j+1] = save;
    }
}
int main(){
    int n;
    int *x, *y;
    LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

    scanf("%d", &n);
    x = (int *)malloc(sizeof(int) * n);
    y = (int *)malloc(sizeof(int) * n);
	srand(time(NULL));
    for(int i = 0; i < n; ++i){
        x[i] = rand()%n+1;
        y[i] = x[i];
    }

    QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	selectSort(x,n);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.12fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

    QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	insertSort(x,n);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.12fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

    free(x);
    return 0;
}