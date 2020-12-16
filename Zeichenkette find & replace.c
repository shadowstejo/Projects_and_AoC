/*
 *  Stephan Jokiel
 *  Maxine Rahlfes
*/
#include "base.h"

//Aufgabenteil a)
char *next_occurence(char *s, char *find) {
    if (s == NULL || find == NULL) { //kurzer check ob die strings nicht NULl sind
        return NULL;
    }
    char *p = NULL; // general pointer
    char matched; //zum vergleichen ob *s == *find
    int s_len = strlen(s); //strlen dürfen wir ja
    int find_len = strlen(find); // same

    if (find_len > s_len) {
        return NULL; //NULL weil ja find nicht größer als s sein darf/kann.
    }

    p = s; //nach allen ausschlüssen setzen wir s auf p.
    matched = 0;

    while (*p) {
        while (*p && *p != *find) {
            p++;  //erste position wo p = find
        }
        if (*p == '\0') { //wenn wir jetzt schon bei 0 ankommen, breaken.
            break;
        }
        //printf("p %s, f %s\n", p, find);
        int i = 0;
        while (find[i] && p[i]) {//find durchlaufen
            if (p[i] != find[i]) { //wenn irgendwo findpointer nicht passt:
                break;                    //wird abgebrochen
            }
            i++; // i erhöhen.
        }
        if (find[i] == 0) {      //falls find zu Ende ist
            matched = 1;        // sind ja alle getroffen, also ein Treffer
            break;
        } else {
            p++;                //sonst gehen wir durch den string weiter.
        }
    }
    if (matched != 1) { //wenn kein treffer
        p = NULL;       //error
    }
    return p;
}

//Aufgabenteil b)
int count(char *s, char *find) {
    char *p = NULL;
    int anzahl = 0;
    while ((p = next_occurence(s, find)) != NULL) { //wenn next_occurence nicht null ist, ist find ja in s.
        anzahl++;                                 //also anzahl an hits erhöhen.
        s = p + strlen(find);                     //s wird weiter durchgegangen., wenn p != NULL, geht while weiter...
    }
    return anzahl;                                //entweder 0 oder durch while erhöht.
}

//Aufgabenteil c) & d)
char *replace(char *s, char *find, char *replace_by) {
    char *newstring;
    int i = 0;
    int k; //FRAGE: sollte man ints auf '0' initialisieren oder egal? int k; <> int k = 0;
    int anz;
    int replen = strlen(replace_by);
    int finlen = strlen(find);
    int slen = strlen(s);
    anz = count(s, find); //anzahl on occurences
    //xmalloc vom neuen string:
    newstring = (char *) xmalloc(slen + anz * (finlen - replen) * sizeof(char) + 1);
    //neue länge muss ja altes wort + anzahl * (differenz zum neuen Wort) sein. (ggf negativ, dann halt weniger) "+1 für '\0'

    while (*s) { //s-loop
        if (next_occurence(s, find) == s) { //wenn das wort schon passt, dann weiter
            for (k = 0; replace_by[k] != '\0'; k++) { //ich will über replace gehen und das bei newstring[i]
                newstring[i + k] = replace_by[k];
            }
            s += finlen; //s geht weiter
            i += replen; //i geht weiter
        }                               //xmalloc hab ich unten geschrieben, wie das bei uns defined ist.
        else {
            newstring[i++] = *s++; //sonst müssen wir erstmal durchlaufen, bis es passt.
        }
    }
    newstring[i] = '\0'; //last 0 noch und fertig.
    return newstring;
}

void test_next_occurence() {
    test_equal_s(next_occurence("aabbccdd", "aab"), "aabbccdd");
    test_equal_b(next_occurence("abbccddac", "aa") == NULL, true);
    test_equal_b(next_occurence("d", "aa") == NULL, true);
    test_equal_b(next_occurence("waaarschau", "aab") == NULL, true);
    test_equal_s(next_occurence("waarschau", "a"), "aarschau");
    test_equal_b(next_occurence("blubluegrau", "blubb") == NULL, true);
    test_equal_s(next_occurence("abbccabcdda", "abc"), "abcdda");
    test_equal_s(next_occurence("bccdda", "a"), "a");
    test_equal_s(next_occurence("hello, hello world", "hello"), "hello, hello world");
    test_equal_s(next_occurence("ello, hello world", "hello"), "hello world");
    test_equal_s(next_occurence("llo, hello world", "rld"), "rld");
    test_equal_b(next_occurence("hello, hello world", "bye") == NULL, true);
    test_equal_s(next_occurence("asdfbfblue, redblue blue blueblue white", "blue"),
                 "blue, redblue blue blueblue white");
}

void test_count() {
    test_equal_i(count("aabbccdd", "aa"), 1);
    test_equal_i(count("abbccdda", "aa"), 0);
    test_equal_i(count("aabbaadd", "aa"), 2);
    test_equal_i(count("aabbccdd", "a"), 2);
    test_equal_i(count("aabbccdd", "abbc"), 1);
    test_equal_i(count("Die Uhrzeit ist 3:10", "Uhrzeit"), 1);
    test_equal_i(count("hello, hello world", "hello"), 2);
    test_equal_i(count("hello, hello world", "llo"), 2);
    test_equal_i(count("fblue, redblue blue blueblue white blub", "blue"), 5);
}

void test_replace() {
    test_equal_s(replace("aabbccdd", "a", "d"), "ddbbccdd");
    test_equal_s(replace("aaabbccdd", "aa", "d"), "dabbccdd");
    test_equal_s(replace("aabbccdd", "aa", "d"), "dbbccdd");
    test_equal_s(replace("aabbccdd", "b", "olo"), "aaolooloccdd");
    test_equal_s(replace("aabbccdd", "c", ""), "aabbdd");
    test_equal_s(replace("hello, hello world", "hello", "bye"), "bye, bye world");
    test_equal_s(replace("aabbccdd", "dd", "eee"), "aabbcceee");
    test_equal_s(replace("crewblacrewblacrewblacrewblacrew", "bl", "_._"),
                 "crew_._acrew_._acrew_._acrew_._acrew");
    test_equal_s(replace("for(int x = X; x < X * 3; x++){printiln(x);}", "X", "90"),
                 "for(int x = 90; x < 90 * 3; x++){printiln(x);}");
}

int main(void) {
    test_next_occurence();
    test_count();
    test_replace();
    return 0;
}