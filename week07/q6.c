#include <stdio.h>
#include <stdint.h>

#define SIX_BIT_MASK 0x3F
#define MIDDLE_BITS_SHIFT 17

uint32_t six_middle_bits(uint32_t num) {
    // 0011 1111 = 0x3F
    // 0000 0000 0000 0000 0111 1110 0000 0000 0000 0000
    // need to shift mask to the left by 17 to get to right position

    // extract the bits: see 1s or 0s and ignore everything else
    // & is more appropriate

    uint32_t result = num >> MIDDLE_BITS_SHIFT;
    result = result & SIX_BIT_MASK;

    return result;
}

uint32_t six_middle_bits_inefficient(uint32_t num) {
    // 0011 1111 = 0x3F
    // 0000 0000 0000 0000 0111 1110 0000 0000 0000 0000
    // need to shift mask to the left by 17 to get to right position

    // extract the bits: see 1s or 0s and ignore everything else
    // & is more appropriate

    uint32_t mask = SIX_BIT_MASK << MIDDLE_BITS_SHIFT;
    uint32_t result = num & mask;
    result = result >> MIDDLE_BITS_SHIFT;

    return result;
}


int main() {

    return 0;
}