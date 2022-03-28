# Week 5 Tute

### 1. When should the types in stdint.h be used:
``` C
#include <stdint.h>

                 // range of values for type
                 //             minimum               maximum
    int8_t   i1; //                 -128                  127
    uint8_t  i2; //                    0                  255
    int16_t  i3; //               -32768                32767
    uint16_t i4; //                    0                65535
    int32_t  i5; //          -2147483648           2147483647
    uint32_t i6; //                    0           4294967295
    int64_t  i7; // -9223372036854775808  9223372036854775807
    uint64_t i8; //                    0 18446744073709551615
```


___
### 2. How can you tell if an integer constant in a C program is decimal (base 10), hexadecimal (base 16), octal (base 8) or binary (base 2)?

```
Hex: 0x (base 16)
Octal: 0 (base 8)
Decimal: start with any other number (base 10)
Binary: no standard notation in C
```

### Sidenote: do you think this is good language design?

### Language trivia: what base is the constant 0 in C?

### Show what the following decimal values look like in 8-bit binary, 3-digit octal, and 2-digit hexadecimal:

| decimal | 0-9 | 10 | 11 | 12 | 13 | 14 | 15 |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| hex | 0-9 | A | B | C | D | E | F |

| part | decimal | working out | binary | octal | hexadecimal |
|:---:|:---:|:---:|:---:|:---:|:---:|
| a | 1 | 
| b | 8 | 
| c | 10 | 10 = 2^3 + 2^1 | 0000 1010 | 012 | 0A |
| d | 15 | 
| e | 16 | 
| f | 100 | 100 = 2^6 + 2^5 + 2^2 | 0110 0100 | 144 | 64 |
| g | 127 | 127 = 2^6 + 2^5 + 2^4 + 2^3 + 2^2 + 2^1 + 2^0 | 0111 1111 | 177 | 7F |
| h | 200 | 200 = 2^7 + 2^6 + 2^3 | 1100 1000 | 310 | C8 |

___
## Bitwise Operations
| symbol | name | what it does |
|:---:|:---:|---|
| & | and | if both bits are 1, it is 1, otherwise 0 |
| \| | or | if either of the bits are 1, it is 1, otherwise 0 |
| ^ | xor | if only one of the bits is 1, it is 1, otherwise 0 |
| ~ | not | flip bit |
| >> | right shift | shifts things down by given bits |
| << | left shift | shifts things up by given bits |

___
### 3. Assume that we have the following 16-bit variables defined and initialised:
``` C
uint16_t a = 0x5555, b = 0xAAAA, c = 0x0001;
// a = 0101 0101 0101 0101
// b = 1010 1010 1010 1010
// c = 0000 0000 0000 0001

//  a = 0101 0101 0101 0101
// ~b = 0101 0101 0101 0101

//      a = 0101 0101 0101 0101
// b << 1 = 0101 0101 0101 0100

//  a = 0101 0101 0101 0101
// ~c = 1111 1111 1111 1110
```
### What are the values of the following expressions:
### Give your answer in hexadecimal, but you might find it easier to convert to binary to work out the solution.

| part | expression | binary | hexadecimal |
|:---:|:---:|:---:|:---:|
| a | a \| b | 1111 1111 1111 1111 | 0xFFFF |
| b | a & b | 0000 0000 0000 0000 | 0x0000 |
| c | a ^ b | 1111 1111 1111 1111 | 0xFFFF |
| d | a & ~b | 0101 0101 0101 0101 | 0x5555 |
| e | c << 6 | 0000 0000 0100 0000 | 0x0040 |
| f | a >> 4 | 0000 0101 0101 0101 | 0x0555 |
| g | a & (b << 1) | 0101 0101 0101 0100 | 0x5554 |
| h | b \| c | 1010 1010 1010 1011 | 0xAAAB |
| i | a & ~c | 0101 0101 0101 0100 | 0x5554 |

### How could I write a C program to answer this question?


___
### 4. 
### Consider a scenario where we have the following flags controlling access to a device.
``` C
#define READING   0x01
#define WRITING   0x02
#define AS_BYTES  0x04
#define AS_BLOCKS 0x08
#define LOCKED    0x10
```
### The flags are contained in an 8-bit register, defined as:
``` C
unsigned char device;
```
### Write C expressions to implement each of the following:
### a. mark the device as locked for reading bytes
`device = READING | LOCKED | AS_BYTES;`

### b. mark the device as locked for writing blocks
`device = WRITING | LOCKED | AS_BLOCKS;`

### c. set the device as locked, leaving other flags unchanged
`device = device | LOCKED;`

`device |= LOCKED;`

### d. remove the lock on a device, leaving other flags unchanged
`device = device & ~LOCKED;`

`device &= ~LOCKED;`

### e. switch a device from reading to writing, leaving other flags unchanged
`device = device & ~READING;`

`device = device | WRITING;`

OR

`device = (device & ~READING) | WRITING;`

### f. swap a device between reading and writing, leaving other flags unchanged
`device = device ^ (READING | WRITING)`

___
### 5. Discuss the starting code for sixteen_out, one of this week's lab exercises. In particular, what does this code (from the provided `main`) do?
``` C
    long l = strtol(argv[arg], NULL, 0);
    assert(l >= INT16_MIN && l <= INT16_MAX);
    int16_t value = l;

    char *bits = sixteen_out(value);
    printf("%s\n", bits);

    free(bits);
```


___
### 6. Given the following type definition
```C
typedef unsigned int Word;
```
### Write a function
```C
Word reverseBits(Word w);
```
### which reverses the order of the bits in the variable w.
### For example: If `w == 0x01234567`, the underlying bit string looks like:
``` C
0000 0001 0010 0011 0100 0101 0110 0111
```
### which, when reversed, looks like:
```C
1110 0110 1010 0010 1100 0100 1000 0000
```
### which is `0xE6A2C480` in hexadecimal.

```C
#include <stdio.h>

// assumed unsigned int is 32 bits
#define BITS_IN_INT 32

typedef unsigned int Word;

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
```