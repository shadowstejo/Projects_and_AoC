/*	Stephan Jokiel
 	Maxine Rahlfes 
 */


/*
Die funktion “f” aus 3a) liest eine Zahl “i”, printed “called f” und gibt, für den Fall, dass “i” kleiner als 0 ist, die Zahl negiert zurück.
Für den Fall, dass “i” 0 oder größer ist, gibt sie 3*i zurück.
*/
#include <stdio.h>

int f(int i) {
	printf("called f\n");
	if (i < 0) {
		return -i;
	}
	else {
		return 3 * i;
	}
}

int main(void) {
	f(15);
	printf("%d", f(-5));
	return 0;
}
