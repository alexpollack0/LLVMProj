#include"pop_direct_branch.c"
#include <stdio.h>

void scan_int(int *x)
{
   scanf("%d", x);
   return;
}

int pSum(int x) {
    if (x <= 0){
        return 0;
    }else{
        return pSum( x - 1 ) + x;
    }
}

int main(){
    int f = 0;
    scan_int(&f);
    int res = pSum(f);
    printf("Result: %d\n", res);

    return 0;
}