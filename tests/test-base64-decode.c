#include <stdio.h>
#include <criterion/criterion.h>
#include "../src/baseencode.h"


Test(decode_test, all_chars) {
    const char *k = "QURGRzQxMyHCoyQlJiYoKC8/XsOnw6kqW10jKS0uLHw8Pis=";
    const char *k_dec = "ADFG413!£$%&&((/?^çé*[]#)-.,|<>+";

    char *dk = base64_decode(k, strlen(k)+1);

    cr_expect(strcmp(dk, k_dec) == 0, "Expected %s to be equal to %s", dk, k_dec);

    free(dk);
}


Test(decode_test, all_chars_noplusone) {
    const char *k = "QURGRzQxMyHCoyQlJiYoKC8/XsOnw6kqW10jKS0uLHw8Pis=";
    const char *k_dec = "ADFG413!£$%&&((/?^çé*[]#)-.,|<>+";

    char *dk = base64_decode(k, strlen(k));

    cr_expect(strcmp(dk, k_dec) == 0, "Expected %s to be equal to %s", dk, k_dec);

    free(dk);
}



Test(decode_test, rfc4648) {
    const char *k[] = {"", "Zg==" ,"Zm8=", "Zm9v", "Zm9vYg==" ,"Zm9vYmE=", "Zm9vYmFy"};
    const char *k_dec[] = {"", "f", "fo", "foo", "foob", "fooba", "foobar"};

    for (int i = 0; i < 7; i++) {
        char *dk = base64_decode(k[i], strlen(k[i])+1);
        cr_expect(strcmp(dk, k_dec[i]) == 0, "Expected %s to be equal to %s", dk, k_dec[i]);
        free(dk);
    }
}


Test(decode_test, rfc4648_noplusone) {
    const char *k[] = {"", "Zg==" ,"Zm8=", "Zm9v", "Zm9vYg==" ,"Zm9vYmE=", "Zm9vYmFy"};
    const char *k_dec[] = {"", "f", "fo", "foo", "foob", "fooba", "foobar"};

    for (int i = 0; i < 7; i++) {
        char *dk = base64_decode(k[i], strlen(k[i]));
        cr_expect(strcmp(dk, k_dec[i]) == 0, "Expected %s to be equal to %s", dk, k_dec[i]);
        free(dk);
    }
}