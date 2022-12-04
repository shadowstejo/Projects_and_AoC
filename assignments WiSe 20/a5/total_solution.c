/*	Stephan Jokiel
 	Maxine Rahlfes 
 */

#include "../prog1lib/lib/base.h"

const int schokoriegel = 50;
const int schoko_ab_zehn = 45;
const int schoko_ab_hundert = 40;
const int versandpreis = 500;
const int grenzpreis = 2000;


int anzahl;
int kosten;

//Die Funktion berechnet den Preis für eine bestimmte Menga an Schokoriegeln ggf. inklusive Versandkosten.
int total(int anzahl) {
	if (anzahl <= 0) { //grenzfall negative bzw 0 Riegel.
		kosten = 0;
	}
	else if (anzahl < 10) { //alle fälle für kosten=50
		kosten = versandpreis + schokoriegel * anzahl;
	}
	else if (anzahl < 45) { // 45 * 45 sind das erste mal über versandfrei
			kosten = versandpreis + schoko_ab_zehn * anzahl;
	} 
	else if (anzahl < 100) { //mehr als 2000cent = keine versandkosten
		kosten = schoko_ab_zehn * anzahl;
	}
	else if (anzahl >= 100) { //mehr als 100 riegel => keine versandkosten
		kosten = schoko_ab_hundert * anzahl;
	}
	else { //anzahl nicht definierbar
		kosten = 0;
	}
	return kosten;
	return 0;
}	

int total_test(void) { //Testfunktion
	test_equal_i(total(9), 950);
	test_equal_i(total(-1), 0);
	test_equal_i(total(10), 950);
	test_equal_i(total(200), 8000);
	test_equal_i(total(35), 2075);
	test_equal_i(total(44), 2480);
	test_equal_i(total(45), 2025);
	test_equal_i(total(0), 0);
	return 0;
}
int main (void){
	total_test();
}
