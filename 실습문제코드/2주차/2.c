#include<stdio.h>
#include<stdlib.h>
void sort(int *x, int n){
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
    int *x;
    scanf("%d", &n);
    x = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; ++i) scanf("%d", x+i);
    sort(x, n);
    for(int i = 0; i < n; ++i) printf(" %d", *(x+i));
    free(x);
    return 0;
}