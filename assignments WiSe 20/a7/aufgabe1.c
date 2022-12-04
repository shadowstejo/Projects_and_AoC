/*
 * Stephan Jokiel
 * Maxine Rahlfes
 */

#include "base.h"


enum FillProperty {
    RANGE,
    SIMPLE,
    PATTERN
} typedef TFillProperty;

struct RangeFill {
    char start;
    char end;
} typedef RangeFill;

struct SimpleFill {
    char c;
} typedef SimpleFill;

struct PatternFill {
    String pattern;
} typedef PatternFill;

struct Fill {
    TFillProperty tag;
    union {
        PatternFill pf;
        SimpleFill sf;
        RangeFill rf;
    };
} typedef Fill;

struct Rect {
    int x, y;
    int width, height;
    Fill fill;
} typedef Rect;

Fill make_range_fill(char lower, char upper) {
    require("within boundries", lower <= upper && lower >= 1 && upper <= 127);
    Fill fill;
    fill.tag = RANGE;
    fill.rf.start = lower;
    fill.rf.end = upper;
    return fill;
}

Fill make_pattern_fill(String s) {
    require("valid input", s_length(s) > 0);
    Fill fill;
    fill.tag = PATTERN;
    fill.pf.pattern = s;
    return fill;
}

Fill make_simple_fill(char c) {
    require("valid sign and range", c >= 1 && c <= 127 && isprint(c));
    Fill fill;
    fill.tag = SIMPLE;
    fill.sf.c = c;
    return fill;
}

Rect make_rect(int x, int y, int width, int height, Fill fill) {
    require("inputs >= 0", x >= 0 && y >= 0 && width >= 0 && height >= 0);
    require("Fill valid", fill.tag == SIMPLE || fill.tag == RANGE || fill.tag == PATTERN);
    Rect rect;
    rect.x = x;
    rect.y = y;
    rect.width = width;
    rect.height = height;
    rect.fill = fill;
    return rect;
}

// Funktionen zur Ausgabe vom Rechteck mit Fülling 

// n-mal wird c ausgegeben
void printcs(char c, int n) {
    for (int i = 0; i < n; i++) printc(c);
}

// die oberste und unterste Reihe werden erstellt mit x-Verschiebung
void print_outer_row_with_offset(int width, int x) {
    printcs(' ', x);                //Verschiebung nach x mit Hilfsfunktion printcs
    printc('+');                       //erste Stelle im Rechteck ist immer ein Pluszeichen
    printcs('-', width - 2);     // es werden width - 2 "-"-Zeichen ausgeben (mit Hilfsfunktion)
    if (width >= 2) {                  //Wenn die width des Rechtecks größer als 1, dann wird ein 2. Pluszeichen ausgeben
        printc('+');
    }
    println();                         // Zeilenumbruch
}

//Funktion zur Ausgabe der Füllung und der Außenstriche (|).
void print_row_with_filling(int width, int x, int row, Fill fill) {
    printcs(' ', x);                             //x-Verschiebung
    printc('|');                                   //zur Beginn einer jeder Zeile wird | gedruckt
    switch (fill.tag) {                            //es gibt drei Fälle: RANGE, SIMPLE, PATTERN
        case RANGE:
            for (int i = 0; i < width - 2; i++) {
                int pos_in_row = i;
                int range = ((fill.rf.end + 1) - fill.rf.start);
                int character = (pos_in_row + (row * (width - 2))) % range;
                character += fill.rf.start;
                printc(character);
            }
            break;
        case SIMPLE:
            printcs(fill.sf.c, width - 2);
            break;
        case PATTERN:
            for (int i = 0; i < width - 2; i++) {
                int pos_in_row = i;
                int pos_string = pos_in_row + row * (width - 2);
                pos_string %= s_length(fill.pf.pattern); // modulo fängt wieder vorne im String an, im Falle, dass der str zu kurz ist
                printc(s_get(fill.pf.pattern, pos_string));
            }
            break;
    }
    printc('|'); //rechtes "|"-Zeichen
    println();
}

void draw_rect(Rect rect) {
    printcs('\n', rect.y);                  // y-Verschiebung durch Zeilenumbrüche
    print_outer_row_with_offset(rect.width, rect.x);        //erste Zeile mit + und - wird ausgegeben
    for (int row = 0; row < rect.height - 2; row++) {       //Die Füllung wird für height-Zeilen - 2 ausgegeben
        print_row_with_filling(rect.width, rect.x, row,
                               rect.fill);     //wichtig ist hier, dass dem Programm immer die Zeilennummer bewusst ist, welche mit den Informationen, width, x und fill and Hilfsfunktion weitergegeben werden
    }
    if (rect.height >= 2) {
        print_outer_row_with_offset(rect.width, rect.x);
    }
}

int main(void) {
    draw_rect(make_rect(0, 0, 1, 1, make_simple_fill('u')));
    draw_rect(make_rect(1, 0, 3, 3, make_simple_fill('o')));
    draw_rect(make_rect(0, 0, 6, 6, make_simple_fill('p')));
    draw_rect(make_rect(2, 0, 15, 3, make_simple_fill('q')));
    draw_rect(make_rect(2, 2, 5, 9, make_range_fill('5', '8')));
    draw_rect(make_rect(15, 0, 15, 10, make_pattern_fill("_^_v")));
    return 0;
}
