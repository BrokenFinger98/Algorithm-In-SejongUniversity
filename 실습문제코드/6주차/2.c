#include<stdio.h>
#include<stdlib.h>
int n, k;
int *x;
int findElement(int *x, int k);
int main(){
    scanf("%d %d", &n, &k);
    x = (int *)malloc(sizeof(int)*n);
    for(int i = 0; i < n; ++i)
        scanf("%d", &x[i]);
    printf("%d\n", findElement(x, k));
    return 0;
}
int findElement(int *x, int k){
    int l = 0, r = n-1, ret = n;
    while (l<=r){
        int mid = l + (r-l)/2;
        if(x[mid]>=k){
            ret = mid;
            r = mid-1;
        }else
            l = mid+1;
    }
    return ret;
}

