# libbaseencode
<a href="https://scan.coverity.com/projects/paolostivanin-libbaseencode">
  <img alt="Coverity Scan Build Status"
       src="https://scan.coverity.com/projects/12747/badge.svg"/>
</a>

Library written in C for encoding and decoding data using base32 or base64 according to [RFC-4648](https://tools.ietf.org/html/rfc4648)

# Requiremens
- GCC or Clang
- CMake

# Build and Install
```
$ git clone https://github.com/paolostivanin/libbaseencode.git
$ cd libbaseencode
$ mkdir build && cd $_
$ cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr ../
$ make
# make install
```

# How To Use It
```
char *b32_encoded = base32_encode(unsigned char *input, size_t input_length, baseencode_error_t *err);

unsigned char *b32_decoded = base32_decode(char *input, size_t input_length, baseencode_error_t *err);

char *b64_encoded = base64_encode(unsigned char *input, size_t input_length, baseencode_error_t *err);

unsigned char *b64_decoded = base64_decode(char *input, size_t input_length, baseencode_error_t *err);
```
Please note that all the returned value **must be freed** once not needed any more.

## Errors
In case of errors, `NULL` is returned and `err` is set to either one of:
```
INVALID_INPUT, EMPTY_STRING, INPUT_TOO_BIG, INVALID_B32_DATA, INVALID_B64_DATA, MEMORY_ALLOCATION,
```
otherwise, `err` is set to `SUCCESS`

