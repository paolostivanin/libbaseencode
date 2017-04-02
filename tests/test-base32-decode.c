#include <stdio.h>
#include <criterion/criterion.h>
#include "../src/baseencode.h"


Test(decode_test, test_20chars) {
    const char *k1 = "12345678901234567890";
    const char *k1_enc = "GEZDGNBVGY3TQOJQGEZDGNBVGY3TQOJQ";
    size_t len_k1_enc = strlen(k1_enc) + 1;

    const char *k2 = "3r;';f3f;qd,.,d+@*$T";
    const char *k2_enc = "GNZDWJZ3MYZWMO3RMQWC4LDEFNACUJCU";
    size_t len_k2_enc = len_k1_enc;

    char *dk1 = base32_decode(k1_enc, len_k1_enc);
    char *dk2 = base32_decode(k2_enc, len_k2_enc);

    cr_expect(strcmp(dk1, k1) == 0, "Expected %s to be equal to %s", dk1, k1);
    cr_expect(strcmp(dk2, k2) == 0, "Expected %s to be equal to %s", dk2, k2);

    free(dk1);
    free(dk2);
}


Test(decode_test, test_1char) {
    const char *k = "F";
    const char *k_enc = "IY======";
    size_t len_k_enc = strlen(k_enc) + 1;

    char *dk = base32_decode(k_enc, len_k_enc);

    cr_expect(strcmp(dk, k) == 0, "Expected %s to be equal to %s", dk, k);

    free(dk);
}


Test(decode_test, test_3chars) {
    const char *k = "cia";
    const char *k_enc = "MNUWC===";
    size_t len_k_enc = strlen(k_enc) + 1;

    char *dk = base32_decode(k_enc, len_k_enc);

    cr_expect(strcmp(dk, k) == 0, "Expected %s to be equal to %s", dk, k);

    free(dk);
}
