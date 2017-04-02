#include <stdio.h>
#include <criterion/criterion.h>
#include "../src/baseencode.h"


Test(encode_test, test_20chars) {
    const char *k1 = "12345678901234567890";
    const char *k1_enc = "GEZDGNBVGY3TQOJQGEZDGNBVGY3TQOJQ";
    size_t len_k1 = strlen(k1) + 1;

    const char *k2 = "3r;';f3f;qd,.,d+@*$T";
    const char *k2_enc = "GNZDWJZ3MYZWMO3RMQWC4LDEFNACUJCU";
    size_t len_k2 = len_k1;

    char *ek1 = base32_encode(k1, len_k1);
    char *ek2 = base32_encode(k2, len_k2);

    cr_expect(strcmp(ek1, k1_enc) == 0, "Expected %s to be equal to %s", k1_enc, ek1);
    cr_expect(strcmp(ek2, k2_enc) == 0, "Expected %s to be equal to %s", k2_enc, ek2);

    free(ek1);
    free(ek2);
}


Test(encode_test, test_1char) {
    const char *k = "F";
    const char *k_enc = "IY======";
    size_t len_k = strlen(k) + 1;

    char *ek = base32_encode(k, len_k);
    cr_expect(strcmp(ek, k_enc) == 0, "Expected %s to be equal to %s", k_enc, ek);

    free(ek);
}


Test(encode_test, test_3chars) {
    const char *k = "cia";
    const char *k_enc = "MNUWC===";
    size_t len_k = strlen(k) + 1;

    char *ek = base32_encode(k, len_k);
    cr_expect(strcmp(ek, k_enc) == 0, "Expected %s to be equal to %s", k_enc, ek);

    free(ek);
}
