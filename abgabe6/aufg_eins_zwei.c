/*
 *  Stephan Jokiel
 *  Maxine Rahlfes
 */

#include "Base.h"

String characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/*
    Die Funktion length_for_base gibt die notwendige Länge an Ziffern zurück, die benötigt werden um die Zahl in ihrer Zielbasis darstellen zu können.
    @param number die Zahl die nun in die neue Zielbasis umgewandelt werden soll
    @param base die Basis in die die Zahl umgewandelt werden sll
    @length the Länge an notwendigen Stellen, um die Zahl in ihrer Zielbasis darstellen zu können
    @returm einen Wert, der die nötige Anzahl an Stellen bei der Umwandlung darstellt
*/
int length_for_base(int number, int base) {
    if (number == 0)
        return 1;
    double needed_chars = log(number) / log(base);
    int length = ceil(needed_chars);
    if (length == (int) (needed_chars)) {
        length++;
    }
    return length;
}

/*
    Gibt einen dynamisch allokierte String zurueck, der so viele Zeichen hat wie noetig sind um die Zahl in der Zielbasis darzustellen.
    @param number Zahl, die in der Zielbasis dargestellt wird.
    @param base Zielbasis, in der die Zahl number dargestellt werden soll.
    @return Eine Zeichenkette mit der noetigen Anzahl an Stellen mit '#' initialisiert.
*/
String get_string_for_number_and_base(int number, int base) {
    int length = length_for_base(number, base);
    String s = xcalloc(sizeof(char), length + 1);
    //printf("length: %d\n", length);
    for (int i = 0; i < length; i++) {
        s[i] = '#';
    }
    return s;
}

/*
    Gibt die Zahl number in der Zielbasis als Zeichenkette zurueck.
    @param number Zahl, die in der Zielbasis dargestellt wird.
    @param base Zielbasis, in der die Zahl number dargestellt werden soll.
    @return String der die Zahl in der Zielbasis enthaelt.
*/
String convert_to_base(int number, int base) {
    String s = "";
    int pos = length_for_base(number, base);
    if (base >= 2 && base <= 36) {
        String s = get_string_for_number_and_base(number, base);
        do {
            char rest = number % base;
            number /= base;
            if (rest >= 0 && rest <= 9) {
                s[pos - 1] = rest + '0';
            } else {
                s[pos - 1] = rest + 'A' - 10;
            }
            pos = pos - 1;
        } while (number != 0);
        return s;
    }
    return s;
}


/*
    Schoen formatierte Ausgabe der Zahl, die zu konvertieren ist, sowie des Ergebnisses.
    @param number Zahl, die in der Zielbasis dargestellt wird.
    @param base Zielbasis, in der die Zahl number dargestellt werden soll.
*/
void print_convert(int number, int base) {
    printf("Convert %4d to base %2d: %s\n", number, base, convert_to_base(number, base));
}

/*
    Testfaelle fuer convert_to_base.
*/
void test_convert_to_base() {
    print_convert(16, -1);
    test_equal_s(convert_to_base(16, -1), "");

    print_convert(10, 1);
    test_equal_s(convert_to_base(10, 1), "");

    print_convert(0, 2);
    test_equal_s(convert_to_base(0, 2), "0");

    print_convert(16, 3);
    test_equal_s(convert_to_base(16, 3), "121");

    print_convert(16, 16);
    test_equal_s(convert_to_base(16, 16), "10");

    print_convert(100, 10);
    test_equal_s(convert_to_base(100, 10), "100");

    print_convert(0, 2);
    test_equal_s(convert_to_base(0, 2), "0");

    print_convert(10, 16);
    test_equal_s(convert_to_base(10, 16), "A");

    print_convert(100, 2);
    test_equal_s(convert_to_base(100, 2), "1100100");

    print_convert(20, 5);
    test_equal_s(convert_to_base(20, 5), "40");

    print_convert(1300300300, 36);
    test_equal_s(convert_to_base(1300300300, 36), "LI5Y4S");
}


void print_bits(int number) {
    String bits = convert_to_base(number, 2);
    printf("0x%4x : %16s\n", number, bits);
}

void bit_operations() {
    printsln("Bitmagic");
    //what does the following?
    printsln("&");
    int a = 0xaf;
    int b = 0xa5;

    int c = a & b;
    print_bits(a);
    print_bits(b);
    print_bits(c); // c beinhaltet, die sowohl in a, als auch in b true sind.

    printsln("|");
    a = 0xb1;
    b = 0x93;
    c = a | b;
    print_bits(a);
    print_bits(b);
    print_bits(c); // c beinhaltet die Bits, die entweder in a, oder in b true sind.

    printsln("^");
    a = 0xb1;
    b = 0x33;
    c = a ^ b;
    print_bits(a);
    print_bits(b);
    print_bits(c); // c beinhaltet die Bits, die NUR in a ODER in b true sind.

    printsln("<< und >>");
    a = 0x30;
    print_bits(a);
    a <<= 2;
    print_bits(a);// "<<" schiebt alle bits eine stelle nach links, rechts werden
    // neue "0"-false generiert. aus "101" würde demnach "1010",
    // die Zahl hinter dem bitoperator "2" gibt die anzahl der stellen, um die geshiftet wird.
    // in diesem Fall 2. demnach wird aus "101" "10100" und bei der Ausgabe kommen quasi 2 nullen hinzu.
    a >>= 3;
    print_bits(a);// ">>" ist der rightshift operator, er discarded quasi den rechtesten Bits,
    // in unserem Fall (nach dem ">>=" operator) um 3 Stellen.
    // also wird aus "101" >>=3 "0" (da die nach rechts über die grenze geschobenen zahlen rausfliegen.


}

/*
    Setzt je nach Wert von (bool) bit (true oder false) value an position index zu 1 oder 0 geändert.
*/
int set_bit(int value, int index, bool bit) {
    if (bit == true) {
        int x = 1;
        x <<= index;
        return (value | x);
    } else {
        int x = 1;
        x <<= index;
        x = ~x;
        value &= ~(1 << index);
        return (value & x);
    }
}
/*
    Wenn position index in value gleich x(1) ist, dann wird true zurückgegeben.
*/
bool get_bit(int value, int index) {
    int x = 1;
    x <<= index;
    return ((value & x) > 0);       //value wird ggü x gestellt und dann geguckt ob das 1 ist oder nicht.

}

//alternativer code
//bool get_bit(int value, int index ) {
//    if ((value & (1 << index )) >> index){
//        return true;
//    }
//    else{
//        return false;
//    }
//}

/*
    Testfaelle fuer get_bit und set_bit
*/
void test_get_set_bit() {
    int a = 0x77;  // hexadezimalzahl für 119 in dez und 01110111 in bin
    //print_bits(a);

    test_equal_b(get_bit(a, 0), true);
    test_equal_b(get_bit(a, 1), true);
    test_equal_b(get_bit(a, 2), true);
    test_equal_b(get_bit(a, 3), false);
    test_equal_b(get_bit(a, 4), true);
    test_equal_b(get_bit(a, 5), true);
    test_equal_b(get_bit(a, 6), true);
    test_equal_b(get_bit(a, 7), false);
    test_equal_b(get_bit(a, 8), false);

    a = set_bit(a, 0, false);
    test_equal_i(a, 0x76); //118
    a = set_bit(a, 0, true);
    test_equal_i(a, 0x77);
    a = set_bit(a, 5, false);
    test_equal_i(a, 0x57);
    a = set_bit(a, 1, true);
    test_equal_i(a, 0x57);
    a = set_bit(a, 3, false);
    test_equal_i(a, 0x57);
}

/*
    Gibt bits 'start' bis 'end' (exklusive 'end') der Zahl 'value' aus.
*/

int extract_bits(int value, int start, int end){
    if(end >= 32){ //Ausschlussfall, falls nicht innerhalb der Bitrange gesucht wird...
        return 0;
    } //möglich hier if-loop auslassen, allerdings muss dann vvvv (end-start) zu (end-1) geändert werden.
    else {
        value = (((value) >> (start)) & ((1 << (end - start)) - 1));
        // der right-shift operator schiebt die bits bis zum start bit nach rechts, und (&-bit operator) nimmt
        // die nächsten (end-start) bits und gibt alle dann als value zurück.
        //     vvvvvv
        return value;
    }
}


/*
    Testfaelle fuer extract_bits.
*/
void test_extract_bits() {
    test_equal_s(convert_to_base(extract_bits(0x1805, 0, 4), 2), "101");
    test_equal_s(convert_to_base(extract_bits(0x1404, 8, 16), 2), "10100");
    test_equal_s(convert_to_base(extract_bits(0x1701, 12, 16), 2), "1");
    test_equal_s(convert_to_base(extract_bits(0x1503, 1, 9), 2), "10000001");
    test_equal_s(convert_to_base(extract_bits(0x1602, 0, 16), 2), "1011000000010");
    test_equal_s(convert_to_base(extract_bits(0xABCD, 16, 0), 2), "0");
    test_equal_s(convert_to_base(extract_bits(0xABCD, -1, 3), 2), "0");
    test_equal_s(convert_to_base(extract_bits(0xABCD, 4, 34), 2), "0");
    test_equal_s(convert_to_base(extract_bits(0x189538, 3, 8), 2), "111");
    test_equal_s(convert_to_base(extract_bits(0x83f3d0, 4, 10), 2), "111101");
    test_equal_s(convert_to_base(extract_bits(0x40d549, 4, 14), 2), "101010100");
    test_equal_s(convert_to_base(extract_bits(0x3505f7, 6, 18), 2), "10000010111");
}

int main(void) {
    printsln("v_v_v_v_v_v_v_v_v_v_v_v_v_v_v_v");
    test_convert_to_base();
    printsln("^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^");
    printsln("------------------------------");
    bit_operations();
    printsln("------------------------------");
    printsln("X_X_X_X_X_VVV_get_set_bit_VVV_X_X_X_X");
    test_get_set_bit();
    printsln("X_X_X_X_X_VVV_extract_bits_VVV_X_X_X_X");
    test_extract_bits();

    return 0;
}