#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
    int a, b, n, k, len;
    char s[100];

    scanf("%d %d %d %s", &a, &b, &n, s);

    for(int i = 0; i < n; ++i){
        int m = (a+b)/2;
        char c = s[i];
        if(c == 'N')
            b = m;
        else if(c == 'Y')
            a = m + 1;
    }
    printf("%d\n", a);
    return 0;
}


