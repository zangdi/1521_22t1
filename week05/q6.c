#include <stdio.h>

// assumed unsigned int is 32 bits
#define BITS_IN_INT 32

typedef unsigned int Word;

// 0000 0001
// 1000 0000

// 0000 0010
// 0100 0000

// BITS_IN_INT - 1 - i

Word reverseBits(Word w) {
    Word new_word = 0;

    for (int i = 0; i < 32; i++) {
        if (w & (1 << i)) {
            new_word |= 1 << (BITS_IN_INT - 1 - i);
        }
    }

    return new_word;
}

int main() {
    Word w = 0x01234567;

    printf(reverseBits(w));

    return 0;
}


// 7
// 0000 0000 0000 0111
// ['0', '0', '0', ..., '1', '1', '1']
