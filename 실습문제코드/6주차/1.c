#include<stdio.h>
#include<stdlib.h>
int n, k;
int *x;
int findElement(int *x, int k);
int rFE(int k, int l, int r);
int main(){
    scanf("%d %d", &n, &k);
    x = (int *)malloc(sizeof(int)*n);
    for(int i = 0; i < n; ++i)
        scanf("%d", &x[i]);
    printf("%d\n", findElement(x, k));
    return 0;
}
int findElement(int *x, int k){
    return rFE(k, 0, n-1);
}
int rFE(int k, int l, int r){
    if(l>r)
        return r;
    if(l == r){
        if(x[l] > k)
            return l-1;
        else if(x[l] < k)
            return l;
    }
    int mid = (l+r)/2;
    if(k == x[mid])
        return mid;
    else if(k < x[mid])
        return rFE(k, l, mid-1);
    else
        return rFE(k, mid+1, r);    
}

/*
rFE(33, 4, 7)
rFE(33, 6, 7)
rFE(33, 7, 7)
rFE(33, 7, 6)
*/