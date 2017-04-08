# libbaseencode
Library written in C for encoding and decoding data using base32 or base64 according to [RFC-4648](https://tools.ietf.org/html/rfc4648)

# Requiremens
- GCC/Clang and CMake

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
char *b32_encoded = base32_encode(input, input_length);

unsigned char *b32_decoded = base32_decode(input, input_length);

char *b64_encoded = base64_encode(input, input_length);

unsigned char *b64_decoded = base64_decode(input, input_length);
```

Please note that all the returned value **must be freed** once not needed any more.