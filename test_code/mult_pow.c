#include "pop_direct_branch.c"
#include <stdio.h>

int pow2(int a){
    return pow3(a+6) + 2;
}

int pow3(int b){
    return b + pow4(2);
}

int pow4(int c){
    return c + 6;
}

int main()
{
    int d = pow2(3);
    printf("d: %d\n", d);
    int k = pow2(4);
    printf("k: %d\n", k);
    return 0;
}
