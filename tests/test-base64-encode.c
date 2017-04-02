#include <stdio.h>
#include <criterion/criterion.h>
#include "../src/baseencode.h"


Test(encode_test, test_20chars) {
    const char *k1 = "";
    const char *k1_enc = "";
    size_t len_k1 = strlen(k1) + 1;

    const char *k2 = "";
    const char *k2_enc = "";
    size_t len_k2 = len_k1;

    char *ek1 = base64_encode(k1, len_k1);
    char *ek2 = base64_encode(k2, len_k2);

    cr_expect(strcmp(ek1, k1_enc) == 0, "Expected %s to be equal to %s", k1_enc, ek1);
    cr_expect(strcmp(ek2, k2_enc) == 0, "Expected %s to be equal to %s", k2_enc, ek2);

    free(ek1);
    free(ek2);
}


Test(encode_test, test_1char) {
    const char *k = "";
    const char *k_enc = "";
    size_t len_k = strlen(k) + 1;

    char *ek = base64_encode(k, len_k);
    cr_expect(strcmp(ek, k_enc) == 0, "Expected %s to be equal to %s", k_enc, ek);

    free(ek);
}


Test(encode_test, test_3chars) {
    const char *k = "";
    const char *k_enc = "";
    size_t len_k = strlen(k) + 1;

    char *ek = base64_encode(k, len_k);
    cr_expect(strcmp(ek, k_enc) == 0, "Expected %s to be equal to %s", k_enc, ek);

    free(ek);
}
