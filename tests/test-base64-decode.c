#include <stdio.h>
#include <criterion/criterion.h>
#include "../src/baseencode.h"
#include "../src/common.h"


Test(b64_decode_test, b64_all_chars) {
    const char *k = "QURGRzQxMyHCoyQlJiYoKC8/XsOnw6kqW10jKS0uLHw8Pis=";
    const char *k_dec = "ADFG413!£$%&&((/?^çé*[]#)-.,|<>+";

    char *dk = base64_decode(k, strlen(k)+1);

    cr_expect(strcmp(dk, k_dec) == 0, "Expected %s to be equal to %s", dk, k_dec);

    free(dk);
}


Test(b64_decode_test, b64_all_chars_noplusone) {
    const char *k = "QURGRzQxMyHCoyQlJiYoKC8/XsOnw6kqW10jKS0uLHw8Pis=";
    const char *k_dec = "ADFG413!£$%&&((/?^çé*[]#)-.,|<>+";

    char *dk = base64_decode(k, strlen(k));

    cr_expect(strcmp(dk, k_dec) == 0, "Expected %s to be equal to %s", dk, k_dec);

    free(dk);
}



Test(b64_decode_test, b64_rfc4648) {
    const char *k[] = {"", "Zg==" ,"Zm8=", "Zm9v", "Zm9vYg==" ,"Zm9vYmE=", "Zm9vYmFy"};
    const char *k_dec[] = {"", "f", "fo", "foo", "foob", "fooba", "foobar"};

    for (int i = 0; i < 7; i++) {
        char *dk = base64_decode(k[i], strlen(k[i])+1);
        cr_expect(strcmp(dk, k_dec[i]) == 0, "Expected %s to be equal to %s", dk, k_dec[i]);
        free(dk);
    }
}


Test(b64_decode_test, b64_rfc4648_noplusone) {
    const char *k[] = {"", "Zg==" ,"Zm8=", "Zm9v", "Zm9vYg==" ,"Zm9vYmE=", "Zm9vYmFy"};
    const char *k_dec[] = {"", "f", "fo", "foo", "foob", "fooba", "foobar"};

    for (int i = 0; i < 7; i++) {
        char *dk = base64_decode(k[i], strlen(k[i]));
        cr_expect(strcmp(dk, k_dec[i]) == 0, "Expected %s to be equal to %s", dk, k_dec[i]);
        free(dk);
    }
}


Test(b64_decode_test, b64_invalid_input) {
    const char *k = "£&/(&/";
    size_t len = strlen(k);

    unsigned char *dk = base64_decode(k, len);

    cr_expect_null(dk, "%s");
}


Test(b64_decode_test, b64_decode_input_exceeded) {
    const char *k = "ASDF";
    size_t len = MAX_DECODE_BASE64_INPUT_LEN + 1;

    unsigned char *dk = base64_decode(k, len);

    cr_expect_null(dk, "%s");
}