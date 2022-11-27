/*  Stephan Jokiel
	Maxine Rahlfes
*/
#include<stdio.h>
//int main(void) {
	//printf("hello, world\n");
	//return 0;
//}
#define hi "hello, %s \n"
#define step "Stephan Jokiel"
#define maxi "Maxine Rahlfes" //erstelle Konstante "step" und "maxi"
int main(void) {
	printf(hi, step); //printf ist eine stdio.h funktion, nimmt alles danach und gibt es aus. %s wird als %string gelesen, der nach dem aktuellen "..." steht und gibt diesen an stelle des %s aus. "\n" in einem String wird als Zeilenumbruch gelsen.
	printf(hi, maxi);
	return 0;
}
