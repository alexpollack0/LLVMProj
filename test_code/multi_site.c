#include "pop_direct_branch.c"
#include <stdio.h>

int pow2(int x){
    return x * x;
}


int main(){
    int x,y,z;
    scanf("%d", &x);
    y = pow2(x);
    printf("y: %d\n", y);
    z = pow2(x);
    printf("z: %d\n", z);
    return y + z;
}