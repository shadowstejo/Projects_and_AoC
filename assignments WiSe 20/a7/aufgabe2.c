/*
 * Stephan Jokiel
 * Maxine Rahlfes
 */

#include "base.h"



const double BITCOIN_USD = 4273.38; // 1 Bitcoin = 4273.38 USD
const double EURO_USD = 1.14; 		// 1 EURO = 1.14 USD
const double DKK_USD = 0.15; 		// 1 Dansk Krone (DKK) = 0.15 USD

enum Currency { BITCOIN, DOLLAR, EURO, DANSK_KRONE }; 
typedef enum Currency Currency;

struct Money { double amount; Currency currency; }; 
typedef struct Money Money;

// double, Currency -> Money
// Initialize a Money structure.
Money make_money(double amount, Currency currency) {
    Money m = { amount, currency };
    return m;
}

// int Money, Money, double -> bool
// Test wheather the actual value of the money is within +/- tolerance of the expected value of the money.
bool test_value(int line, Money a, Money e, double tolerance) {
    bool x = base_test_within_d(__FILE__, line, a.amount, e.amount, tolerance);
    bool u = base_test_equal_i(__FILE__, line, a.currency, e.currency);
    return x && u;
}

void print_money(Money m);

void print_money_test() {
    print_money(make_money(1234, DOLLAR));
    print_money(make_money(1.234, BITCOIN));
    print_money(make_money(1.34, EURO));
    print_money(make_money(27.50, DANSK_KRONE));
}

// Money -> void
// Print the ammount of money.
void print_money(Money m) {
    switch (m.currency) {
        case DOLLAR:
            printf("%.2f $\n", m.amount);
            break;
        case BITCOIN:
            printf("%.8f Bitcoin\n", m.amount);
            break;
        case EURO:
            printf("%.2f Euro\n", m.amount);
            break;
        case DANSK_KRONE:
            printf("%.2f DKK\n", m.amount);
            break;
    }
}

Money to_currency(Money m, Currency currency);

void to_currency_test(void) {
    test_value(__LINE__, to_currency(make_money(1, BITCOIN), DOLLAR), make_money(4273.38, DOLLAR), 1e-3);
    test_value(__LINE__, to_currency(make_money(5, BITCOIN), DOLLAR), make_money(21366.9, DOLLAR), 1e-3);
    test_value(__LINE__, to_currency(make_money(5, BITCOIN), EURO), make_money(18742.894, EURO), 1e-3);
    test_value(__LINE__, to_currency(make_money(100, DANSK_KRONE), DOLLAR), make_money(15, DOLLAR), 1e-3);
    test_value(__LINE__, to_currency(make_money(10, EURO), DOLLAR), make_money(11.4, DOLLAR), 1e-3);
    test_value(__LINE__, to_currency(make_money(15, DOLLAR), DOLLAR), make_money(15, DOLLAR), 1e-3);
    test_value(__LINE__, to_currency(make_money(100, DOLLAR), EURO), make_money(87.72, EURO), 1e-3);
    test_value(__LINE__, to_currency(make_money(1.5, DOLLAR), DANSK_KRONE), make_money(10, DANSK_KRONE), 1e-3);
    test_value(__LINE__, to_currency(make_money(3748.58, EURO), BITCOIN), make_money(1, BITCOIN), 1e-3);
    test_value(__LINE__, to_currency(make_money(3192, DANSK_KRONE), EURO), make_money(420, EURO), 1e-3);
}

// Money, Currency -> Money
// Convert an amount of money to the given target currency.
Money to_currency(Money m, Currency target_currency) {
    switch (m.currency) {
        case DOLLAR:
            if (target_currency == DOLLAR){
                return m;
            }
            else if (target_currency == DANSK_KRONE){
                return make_money(m.amount/DKK_USD, DANSK_KRONE);
            }
            else if (target_currency == EURO){
                return make_money(m.amount/EURO_USD, EURO);
            }
            else if (target_currency == BITCOIN){
                return make_money(m.amount/BITCOIN_USD, BITCOIN);
            }
            else{
                return m;
            }
            break;
        case EURO:
            if (target_currency == DOLLAR){
                return make_money(m.amount*EURO_USD, DOLLAR);
                return m;
            }
            else if (target_currency == DANSK_KRONE){
                return make_money((m.amount*EURO_USD)/DKK_USD, DANSK_KRONE);
            }
            else if (target_currency == EURO){
                return m;
            }
            else if (target_currency == BITCOIN){
                return make_money((m.amount*EURO_USD)/BITCOIN_USD, BITCOIN);
            }
            else{
                return m;
            }
        case DANSK_KRONE:
            if (target_currency == DOLLAR){
                return make_money(m.amount*DKK_USD, DOLLAR);
            }
            else if (target_currency == DANSK_KRONE){
                return m;
            }
            else if (target_currency == EURO){
                return make_money((m.amount*DKK_USD)/EURO_USD, EURO);
            }
            else if (target_currency == BITCOIN){
                return make_money((m.amount*DKK_USD)/BITCOIN_USD, BITCOIN);
            }
            else{
                return m;
            }
        case BITCOIN:
            if (target_currency == DOLLAR){
                return make_money(m.amount*BITCOIN_USD, DOLLAR);
            }
            else if (target_currency == DANSK_KRONE){
                return make_money((m.amount*BITCOIN_USD)/DKK_USD, DANSK_KRONE);
            }
            else if (target_currency == EURO){
                return make_money((m.amount*BITCOIN_USD)/EURO_USD, EURO);
            }
            else if (target_currency == BITCOIN){
                return m;
            }
            else{
                return m;
            }
    }

    return make_money(1, EURO);
}

int compare(Money m, Money v);

void compare_test(void) {
	test_equal_i(compare(make_money(1000, DOLLAR), make_money(877.19, EURO)), 0);
    test_equal_i(compare(make_money(1140, DOLLAR), make_money(1000, EURO)), 0);
    test_equal_i(compare(make_money(2000, DOLLAR), make_money(877.19, EURO)), 1);
    test_equal_i(compare(make_money(100, DOLLAR), make_money(2877.19, EURO)), -1);
    test_equal_i(compare(make_money(9000, DOLLAR), make_money(400, DANSK_KRONE)), 1);
    test_equal_i(compare(make_money(20, DOLLAR), make_money(0.00468014, BITCOIN)), 0);
    test_equal_i(compare(make_money(1131, DOLLAR), make_money(1000, EURO)), 0);
    test_equal_i(compare(make_money(1130, DOLLAR), make_money(1000, EURO)), 0);
    test_equal_i(compare(make_money(1128, DOLLAR), make_money(1000, EURO)), -1);

}
    
// Money, Money -> int
// Compares two amounts of money. Returns 0 if the two amount of money are equal, 
// -1 if m is smaller than v and +1 if m is larger than v.
int compare(Money m, Money v) {
    bool t1 = (to_currency(m, v.currency).amount / to_currency(v, v.currency).amount) <= 1.01;//check für if, if abweichung >0.01
    bool t2 = (to_currency(m, v.currency).amount / to_currency(v, v.currency).amount) >= 0.99;//check für if, if abweichung >0.01
    if(t1 && t2) { //test ob das Verhältnis gleich (mit 0.01 margin) ist.
        return 0;
    }
    else if (fabs(to_currency(m, DOLLAR).amount ) < fabs(to_currency(v, DOLLAR).amount)){
        return -1; // test ob m < v ist (hier nach Dollar und nicht nach v.currency) da es ja keinen Unterschied macht.
    }
    else { //wenn m =/= v ist und m nicht < als v ist, dann MUSS m > v sein...
        return 1;
    }
}

int main(void) { //.. main
	printf("%.2f\n", 22.3); //???
    print_money_test(); //test pm
    to_currency_test(); //test tc
    compare_test(); //test compare()
    return 0;
}
