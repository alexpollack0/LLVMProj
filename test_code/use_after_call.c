#include "pop_direct_branch.c"
#include <stdio.h>



int pbar(int b){
    return b + b * b;
}

int pfoo(int x){
    return x + pbar(x);
}

int main(){
    int l = 0;
    int k;
    k = pfoo(5) + 7;
    printf("%d\n", k); 
    return k;
}