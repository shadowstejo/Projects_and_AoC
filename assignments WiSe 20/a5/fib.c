/*	Stephan Jokiel
 	Maxine Rahlfes 
 */

// calculates the n-th fibonacci number and prints it on the output

#include "../prog1lib/lib/base.h"

void fib(int n){
    int fn_1 = 1; 
    int fn_2 = 1;
    int fn = 1;
    
    if (n <= 0) {
		printsln ("n too small");
	} else if (n <= 2) {
		printiln(fn);
	} else {
		while ( true ) {
			if ( n <= 2) {
				printiln(fn);
				break;
			} 			
			fn = fn_1 + fn_2;
			fn_2 = fn_1;
			fn_1 = fn;
			n--;
		}
	}
}	

int main(void){
	fib(15);
	fib(2);
	fib(20);}	
				
