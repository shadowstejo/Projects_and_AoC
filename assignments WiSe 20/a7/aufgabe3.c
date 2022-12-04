/*
 * Stephan Jokiel
 * Maxine Rahlfes
 */

#include "base.h"
#include "string.h"

// a) struct Statistics ...
struct Statistics {
    int Birthyear;
    int Men;
    int Women;
    double M_Height;
    double W_Height;
} typedef Statistics;


// b) ... make_statistics...
Statistics make_statistics(Statistics s) {
    s.Birthyear = 0;
    s.Men = 0;
    s.Women = 0;
    s.M_Height = 0;
    s.W_Height = 0;
    return s;
}

// c) ... print_statistics...
void print_statistics(Statistics s) {
    printf("mean year: \t\t %6d\n", s.Birthyear);
    printf("number males: \t\t %6d\n", s.Men);
    printf("number females:\t\t %6d\n", s.Women);
    printf("mean height males: \t %6.2f m\n", s.M_Height);
    printf("mean height females: \t %6.2f m\n", s.W_Height);
}


// d) ... compute_statistics...
Statistics compute_statistics(String table) {
    Statistics s;
    s = make_statistics(s);
    int i = 0;
    int row = 0;
    int Birthyear_sum = 0;
    double W_Height_sum = 0;
    double M_Height_sum = 0;
    int pos_start_word = 0;
    int word_in_row = 0;
    char last_sex = 0;

    while (table[i] != 0) {
        char c = table[i];
        if (c == '\t' || c == '\n') {
            int pos = i;
            String sub_string = s_sub(table, pos_start_word, pos);
            pos_start_word = i + 1;
            if (row >= 1) {
                switch (word_in_row) {
                    case 0: //Birthyear
                        Birthyear_sum += i_of_s(sub_string);
                        break;
                    case 1: // sex
                        last_sex = s_get(sub_string, 0);
                        if (last_sex == 'm') { //Men
                            s.Men++;
                        } else {                //Women
                            s.Women++;
                        }
                        break;
                    case 2: //Height
                        if (last_sex == 'm') {
                            M_Height_sum += d_of_s(sub_string);
                        } else {
                            W_Height_sum += d_of_s(sub_string);
                        }
                        break;
                }
            }
            word_in_row++;
            if (c == '\n') {
                row++;
                word_in_row = 0;
            }
        }
        i++;
    }

    s.Birthyear = Birthyear_sum / (row - 1);
    s.M_Height = M_Height_sum / s.Men;
    s.W_Height = W_Height_sum / s.Women;
    return s;
}

int main(void) {
    String table = s_read_file("people.txt");
    //printsln(table);
    Statistics s = compute_statistics(table);
    print_statistics(s);
    return 0;
}
