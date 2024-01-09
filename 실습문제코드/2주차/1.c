#include<stdio.h>
#include<stdlib.h>

void sort(int *x, int n){
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
int main(){
    int n;
    int *x;
    scanf("%d", &n);
    x = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; ++i) scanf("%d", x+i);
    sort(x, n);
    for(int i = 0; i < n; ++i) printf(" %d", *(x+i));
    free(x);
    return 0;
}