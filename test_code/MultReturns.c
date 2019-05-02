#include <stdio.h>
#include "pop_direct_branch.c"

int pow2(int a){
	if(a > 0){
		return a * a;
	}
	else{
		return -1;
	}
}

int main(){
	int b = 6;
	int c = pow2(b);
	printf("pow2 of 6: %d\n", c);
	int d = -4;
	int e = pow2(d);
	printf("pow2 of -4: %d\n", e);
}
