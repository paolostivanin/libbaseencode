#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


static int get_char_index(unsigned char c);

static const unsigned char b64_alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


char *
base64_encode(const unsigned char *input_string, size_t input_length)
{
    size_t output_length = 4 * ((input_length + 2) / 3);
    char *encoded_data = malloc(output_length + 1);

    if (encoded_data == NULL) {
        fprintf(stderr, "Error during memory allocation (encoded_data)\n");
        return NULL;
    }

    uint8_t first_octet, second_octet, third_octet;
    for (int i = 0, j = 0, triple = 0; i < input_length;) {
        first_octet = (uint8_t) (i < input_length ? input_string[i++] : 0);
        second_octet = (uint8_t) (i < input_length ? input_string[i++] : 0);
        third_octet = (uint8_t) (i < input_length ? input_string[i++] : 0);
        triple = (first_octet << 0x10) + (second_octet << 0x08) + third_octet;

        encoded_data[j++] = b64_alphabet[(triple >> 0x12) & 0x3F];
        encoded_data[j++] = b64_alphabet[(triple >> 0x0C) & 0x3F];
        encoded_data[j++] = b64_alphabet[(triple >> 0x06) & 0x3F];
        encoded_data[j++] = b64_alphabet[(triple >> 0x00) & 0x3F];
    }

    uint8_t possible_equals[] = {0, 2, 1};
    for (int i = 0; i < possible_equals[input_length % 3]; i++)
        encoded_data[output_length - 1 - i] = '=';

    return encoded_data;
}


unsigned char *
base64_decode(const char *user_data, size_t data_len)
{
    static const int bits_per_block = 6;
    static const int bits_per_byte = 8;

    //TODO check for valid b64 string (check alphabet)
    size_t user_data_chars = 0;
    for (int z = 0; z < data_len; z++) {
        // As it's not known whether data_len is with or without the +1 for the null byte, a manual check is required.
        if (user_data[z] != '=' && user_data[z] != '\0') {
            user_data_chars += 1;
        }
    }

    size_t output_length = data_len / 4 * 3;
    unsigned char *decoded_data = calloc(output_length + 1, 1);
    if (decoded_data == NULL) {
        fprintf(stderr, "Error during memory allocation (decoded_data)\n");
        return NULL;
    }

    uint8_t mask = 0, current_byte = 0;
    int bits_left = 8;
    for (int i = 0, j = 0; i < user_data_chars; i++) {
        int char_index = get_char_index((unsigned char)user_data[i]);
        if (bits_left > bits_per_block) {
            mask = (uint8_t) char_index << (bits_left - bits_per_block);
            current_byte = (uint8_t) (current_byte | mask);
            bits_left -= bits_per_block;
        } else {
            mask = (uint8_t) char_index >> (bits_per_block - bits_left);
            current_byte = (uint8_t) (current_byte | mask);
            decoded_data[j++] = current_byte;
            current_byte = (uint8_t) (char_index << (bits_per_byte - bits_per_block + bits_left));
            bits_left += bits_per_byte - bits_per_block;
        }
    }
    decoded_data[output_length] = '\0';

    return decoded_data;
}


static int
get_char_index(unsigned char c)
{
    for (int i = 0; i < sizeof(b64_alphabet); i++) {
        if (b64_alphabet[i] == c) {
            return i;
        }
    }
    return -1;
}
