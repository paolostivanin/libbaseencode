#pragma once

#define BITS_PER_BYTE 8
#define BITS_PER_B32_BLOCK 5
#define BITS_PER_B64_BLOCK 6

// 64 MB should be more than enough
#define MAX_ENCODE_INPUT_LEN 64*1024*1024
// if 64 MB of data is encoded than it should be also possible to decode it. That's why a bigger input is allowed for decoding
#define MAX_DECODE_BASE32_INPUT_LEN ((MAX_ENCODE_INPUT_LEN * 8 + 4) / 5)
#define MAX_DECODE_BASE64_INPUT_LEN ((MAX_ENCODE_INPUT_LEN * 8 + 4) / 6)
