# Week 7 Tute

### 1. On a machine with 16-bit ints, the C expression `(30000 + 30000)` yields a negative result.
### Why the negative result? How can you make it produce the correct result?

16 bits: -2^15 to 2^15 - 1

2^15 ~~ 30,000

1000 0000 0000 0000


unsigned 16 bits: 0 to 2^16 - 1
___
## Twos-complement
16

1st bit: indicates if it's positive or negative

positive: represented normally in binary

negative: if first bit is one, then flip the bits, add 1
-1 * (~positive value + 1)
___
### 2. Assume that the following hexadecimal values are 16-bit twos-complement. Convert each to the corresponding decimal value.

| part | hexadecimal | binary | calculation | decimal |
|:---:|:---:|:---:|:---:|:---:|
| i | 0x0013 | 
| ii | 0x0444 |
| iii | 0x1234 | 0001 0010 0011 0100 | 2^2 + 2^4 + 2^5 + 2^9 + 2^12 | 4660 |
| iv | 0xffff | 1111 1111 1111 1111 | -1 * (0x0000 + 1) = -1 * 1 | -1 |
| v | 0x8000 | 1000 0000 0000 0000 | -1 * (0x7FFF + 1) = -1 * 0x8000 | -32768

___
### 3. Give a representation for each of the following decimal values in 16-bit twos-complement bit-strings. Show the value in binary, octal and hexadecimal.
| part | decimal | calculation | binary | octal | hexadecimal |
|:---:|:---:|:---:|:---:|:---:|:---:|
| i | 1 | 
| ii | 100 | 2^6 + 2^5 + 2^2 | 0000 0000 0110 0100 | 0000144 | 0x0064
| iii | 1000 | 2^9 + 2^8 + 2^7 + 2^6 + 2^5 + 2^3 | 0000 0011 1110 1000 | 0001750 | 0x03E8 |
| iv | 10000 | 2^13 + 2^10 + 2^9 + 2^8 + 2^4 | 0010 0111 0001 0000 | 0023420 | 0x2710 |
| v | 100000 | too big to fit into 16 bits |
| vi | -5 | 0000 0000 0000 0101 => flip => 1111 1111 1111 1010 => add 1 => 1111 1111 1111 1011 | 1111 1111 1111 1011 | 0177773 | 0xFFFB |
| vii | -100 | 0000 0000 0110 0100 => flip => 1111 1111 1001 1011 => add 1 => 1111 1111 1001 1100 | 1111 1111 1001 1100 | 0177634 | 0xFF9C |

___
## Floating Point Representation

32 bit floats:

sign: 1 bit: 0 -> positive, 1 -> negative

exponent: 8 bits: 1000 0000: exponent - 127

fraction: 23 bits: 1 + negative powers of 2

___
### 4. What decimal numbers do the following single-precision IEEE 754-encoded bit-strings represent?
### Each of the following are a single 32-bit bit-string, but partitioned to show the sign, exponent and fraction parts.
| part | string | calculation | decimal |
|:---:|:---:|:---:|:---:|
| a | 0 00000000 00000000000000000000000 | (-1)^0 * 2^(0 - 127) * (1 + 0) | 2^-127 |
| d | 0 01111110 00000000000000000000000 | (-1)^0 * 2^(126-127) * (1 + 0) | 2^-1 or 0.5 |
| e | 0 01111110 11111111111111111111111 | (-1)^0 * 2^(126-127) * (1 + 0.99999999) | 2^-1 * 1.99999999
| f | 0 10000000 01100000000000000000000 | (-1)^0 * 2^(128 - 127) * (1 + 2^-2 + 2^-3) = 1 * 2 * 1.375 = 2.75
| g | 0 10010100 10000000000000000000000 | (-1)^0 * 2^(148 - 127) * (1 + 2^-1) | 2^21 * 1.5

___
### 5. Convert the following decimal numbers into IEEE 754-encoded bit-strings:
| part | decimal | calculation | string |
|:---:|:---:|:---:|:---:|
| a | 2.5 | sign: +, exponent: want 2^1 -> 127 + 1 = 128, fraction: 2^-2 | 0 10000000 01000000000000000000000 |
| b | 0.375 | sign: +, exponent: want 2^-2 -> 127 - 2 = 125, fraction: 2^-1 | 0 01111101 10000000000000000000000 |
| c | 27.0 | sign: +, exponent: want 2^4 -> 127 + 4 = 131, fraction: 2^-1 + 2^-3 + 2^-4 | 0 10000011 10110000000000000000000 |
| d | 100.0 | sign: +, exponent: want 2^6 -> 127 + 6 = 133, fraction: 2^-1 + 2^-4 | 0 10000101 10010000000000000000000 |

___
### 6. Write a C function, `six_middle_bits`, which, given a `uint32_t`, extracts and returns the middle six bits.

```C
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
```
