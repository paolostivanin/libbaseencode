#include <stdio.h>
#include <criterion/criterion.h>
#include "../src/baseencode.h"
#include "../src/common.h"


Test(b32_decode_test, b32_all_chars) {
    const char *k = "IFCEMRZUGEZSDQVDEQSSMJRIFAXT6XWDU7B2SKS3LURSSLJOFR6DYPRL";
    const char *k_dec = "ADFG413!£$%&&((/?^çé*[]#)-.,|<>+";

    char *dk = base32_decode(k, strlen(k)+1);

    cr_expect(strcmp(dk, k_dec) == 0, "Expected %s to be equal to %s", dk, k_dec);

    free(dk);
}


Test(b32_decode_test, b32_all_chars_noplusone) {
    const char *k = "IFCEMRZUGEZSDQVDEQSSMJRIFAXT6XWDU7B2SKS3LURSSLJOFR6DYPRL";
    const char *k_dec = "ADFG413!£$%&&((/?^çé*[]#)-.,|<>+";

    char *dk = base32_decode(k, strlen(k));

    cr_expect(strcmp(dk, k_dec) == 0, "Expected %s to be equal to %s", dk, k_dec);

    free(dk);
}


Test(b32_decode_test, b32_rfc4648) {
    const char *k[] = {"", "MY======", "MZXQ====", "MZXW6===", "MZXW6YQ=", "MZXW6YTB", "MZXW6YTBOI======"};
    const char *k_dec[] = {"", "f", "fo", "foo", "foob", "fooba", "foobar"};

    for (int i = 0; i < 7; i++) {
        char *dk = base32_decode(k[i], strlen(k[i])+1);
        cr_expect(strcmp(dk, k_dec[i]) == 0, "Expected %s to be equal to %s", dk, k_dec[i]);
        free(dk);
    }
}


Test(b32_decode_test, b32_rfc4648_noplusone) {
    const char *k[] = {"", "MY======", "MZXQ====", "MZXW6===", "MZXW6YQ=", "MZXW6YTB", "MZXW6YTBOI======"};
    const char *k_dec[] = {"", "f", "fo", "foo", "foob", "fooba", "foobar"};

    for (int i = 0; i < 7; i++) {
        char *dk = base32_decode(k[i], strlen(k[i]));
        cr_expect(strcmp(dk, k_dec[i]) == 0, "Expected %s to be equal to %s", dk, k_dec[i]);
        free(dk);
    }
}


Test(b32_decode_test, b32_invalid_input) {
    const char *k = "£&/(&/";
    size_t len = strlen(k);

    unsigned char *dk = base32_decode(k, len);

    cr_expect_null(dk, "%s");
}


Test(b32_decode_test, b32_decode_input_exceeded) {
    const char *k = "ASDF";
    size_t len = MAX_DECODE_BASE32_INPUT_LEN + 1;

    unsigned char *dk = base32_decode(k, len);

    cr_expect_null(dk, "%s");
}


Test(b32_decode_test, b32_decode_input_whitespaces) {
    const char *k = "MZ XW 6Y TB";
    const char *expected = "fooba";

    unsigned char *dk = base32_decode(k, strlen(k));

    cr_expect_str_eq(dk, expected, "%s");
}