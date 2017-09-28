#include <stdio.h>
#include <criterion/criterion.h>
#include <baseencode.h>


Test(b64_decode_test, b64_all_chars) {
    baseencode_error_t err;
    const char *k = "QURGRzQxMyHCoyQlJiYoKC8/XsOnw6kqW10jKS0uLHw8Pis=";
    const char *k_dec = "ADFG413!£$%&&((/?^çé*[]#)-.,|<>+";

    char *dk = base64_decode(k, strlen(k)+1, &err);

    cr_expect(strcmp(dk, k_dec) == 0, "Expected %s to be equal to %s", dk, k_dec);

    free(dk);
}


Test(b64_decode_test, b64_all_chars_noplusone) {
    baseencode_error_t err;
    const char *k = "QURGRzQxMyHCoyQlJiYoKC8/XsOnw6kqW10jKS0uLHw8Pis=";
    const char *k_dec = "ADFG413!£$%&&((/?^çé*[]#)-.,|<>+";

    char *dk = base64_decode(k, strlen(k), &err);

    cr_expect(strcmp(dk, k_dec) == 0, "Expected %s to be equal to %s", dk, k_dec);

    free(dk);
}



Test(b64_decode_test, b64_rfc4648) {
    baseencode_error_t err;
    const char *k[] = {"", "Zg==" ,"Zm8=", "Zm9v", "Zm9vYg==" ,"Zm9vYmE=", "Zm9vYmFy"};
    const char *k_dec[] = {"", "f", "fo", "foo", "foob", "fooba", "foobar"};

    for (int i = 0; i < 7; i++) {
        char *dk = base64_decode(k[i], strlen(k[i])+1, &err);
        cr_expect(strcmp(dk, k_dec[i]) == 0, "Expected %s to be equal to %s", dk, k_dec[i]);
        free(dk);
    }
}


Test(b64_decode_test, b64_rfc4648_noplusone) {
    baseencode_error_t err;
    const char *k[] = {"", "Zg==" ,"Zm8=", "Zm9v", "Zm9vYg==" ,"Zm9vYmE=", "Zm9vYmFy"};
    const char *k_dec[] = {"", "f", "fo", "foo", "foob", "fooba", "foobar"};

    for (int i = 0; i < 7; i++) {
        char *dk = base64_decode(k[i], strlen(k[i]), &err);
        cr_expect(strcmp(dk, k_dec[i]) == 0, "Expected %s to be equal to %s", dk, k_dec[i]);
        free(dk);
    }
}


Test(b64_decode_test, b64_invalid_input) {
    baseencode_error_t err;
    const char *k = "£&/(&/";
    size_t len = strlen(k);

    unsigned char *dk = base64_decode(k, len, &err);

    cr_expect_null(dk, "%s");
    cr_expect_eq(err, INVALID_B64_DATA);
}


Test(b64_decode_test, b64_decode_input_exceeded) {
    baseencode_error_t err;
    const char *k = "ASDF";
    size_t len = 128*1024*1024;

    unsigned char *dk = base64_decode(k, len, &err);

    cr_expect_null(dk, "%s");
    cr_expect_eq(err, INPUT_TOO_BIG);
}


Test(b64_decode_test, b64_decode_input_whitespaces) {
    baseencode_error_t err;
    const char *k = "Zm 9v Y mFy";
    const char *expected = "foobar";

    unsigned char *dk = base64_decode(k, strlen(k), &err);

    cr_expect_str_eq(dk, expected, "%s");
}