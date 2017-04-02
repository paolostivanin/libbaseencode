#pragma once

char *base32_encode(const unsigned char *user_data, size_t data_len);

unsigned char *base32_decode(const char *user_data, size_t data_len);

char *base64_encode(const unsigned char *input_string, size_t input_length);

unsigned char *base64_decode(const char *input_string, size_t input_length);