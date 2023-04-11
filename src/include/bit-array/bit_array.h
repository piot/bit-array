/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct ImprintAllocator;

typedef int BitArrayBit;
typedef uint32_t BitArrayAtom;

#define BIT_ARRAY_BITS_IN_ATOM (sizeof(BitArrayAtom) * 8)

typedef struct BitArray {
    BitArrayAtom* array;
    size_t atomCount;
    size_t bitCount;
    size_t numberOfBitsSet;
    struct ImprintMemory* memory;
} BitArray;

void bitArrayInit(BitArray* self, struct ImprintAllocator* memory, size_t bitCount);
void bitArrayDestroy(BitArray* self);
void bitArrayReset(BitArray* self);
void bitArraySet(BitArray* self, size_t index);
bool bitArrayAreAllSet(const BitArray* self);
size_t bitArrayFirstUnset(const BitArray* self);
BitArrayAtom bitArrayGetAtomFrom(const BitArray* self, size_t fromIndex);
BitArrayBit bitArrayGet(const BitArray* self, size_t index);
const char* bitArrayToString(const BitArray* self, char* buf, size_t maxBuf);

#endif
