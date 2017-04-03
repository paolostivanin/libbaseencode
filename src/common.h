#pragma once

#define BITS_PER_BLOCK_B32 5
#define BITS_PER_BLOCK_B64 6
#define BITS_PER_BYTE 8

#define MAX_ENCODE_INPUT_LEN 32*1024*1024  // 32 MB should be more than enough
#define MAX_DECODE_INPUT_LEN (((32*1024*1024)* 8 + 4) / 6)  // if 32 MB of data is encoded than we have also to decode it. That's why a bigger input is allowed for decoding
