/*	Stephan Jokiel
 	Maxine Rahlfes 
 */

#include "../prog1lib/lib/base.h"

/* in this function a random number is given and the user is supposed to guess the number
when guessed correctly the prgramm ends
*/

int main(void){
	int upper = 101;
	int random = i_rnd (upper);
	bool finish = false;
	printf("Rate meine Zahl. Sie liegt im Intervall [0, %d].\n", upper - 1);
	
	while (!finish){
		int num = i_input();
		if (num == random) {
			printf( "Zahl korrekt"); 
			finish = true;
		} else if ( num > random ) {
			printsln ("Zahl zu gross");
		} else {
			printsln("Zahl zu klein");
		}
	}		
	return 0;
}
