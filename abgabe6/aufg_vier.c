/*
 *  Stephan Jokiel
 *  Maxine Rahlfes
 */

#include "base.h"

/* The function decode will decode a secret message by exchanging a letter with the comparing
 * letter in a reversed Alphabet.
*/
String decode(String secret_message) {
    int length = s_length(secret_message);
    String out_message = s_copy(secret_message);
    for (int i = 0; i < length; i++) {
        char c = s_get(secret_message, i);
        if (c <= 'z' && c >= 'a') {
            c = 'a' + 'z' - c;
            s_set(out_message, i, c);
        } else if (c <= 'Z' && c >= 'A') {
            c = 'A' + 'Z' - c;
            s_set(out_message, i, c);
        }
    }
    return out_message;
}


void test_decode() {
    test_equal_s(decode("Kiltiznnrvivm"), "Programmieren");
    test_equal_s(decode("1"), "1");
    test_equal_s(decode("a"), "z");
    test_equal_s(decode("Blau"), "Yozf");
    test_equal_s(decode("FreeWilly"), "UivvDroob");
    test_equal_s(decode("Zgyzhs"), "Atbash");
}

/* The function encode will encode a secret message by exchanging a letter with the comparing
 * letter in a reversed Alphabet. It uses the function decode() to do that.
*/
String encode(String message) {
    return decode(message);
}

void test_encode() {
    test_equal_s(encode("Programmierenz"), "Kiltiznnrvivma");
    test_equal_s(encode("z"), "a");
    test_equal_s(encode("a"), "z");
    test_equal_s(encode("1"), "1");
    test_equal_s(encode("Zgyzhs"), "Atbash");
}

int main(void) {

    String secret_message = "Kiltiznnrvivm 1 nzxsg Hkzhh. Wrvh rhg pvrmv Dviyfmt ufvi vgdzrtv Kilwfpgv zfu wvn Yrow. Grkk: Wrv Olvhfmt ufvi wzh vmxlwrvivm rhg tzma vrmuzxs fmw kzhhg rm vrmv Avrov.";

    printsln(decode(secret_message));
    printsln(encode(decode(secret_message)));
    test_decode();
    test_encode();

    return 0;
}
