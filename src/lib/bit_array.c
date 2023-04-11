/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <bit-array/bit_array.h>
#include <clog/clog.h>
#include <imprint/tagged_allocator.h>

/// Initializes a bit array
/// @param self
/// @param memory the allocator with no explicit free function.
/// @param bitCount the maximum number of bits in the array
void bitArrayInit(BitArray* self, struct ImprintAllocator* memory, size_t bitCount)
{
    size_t atomCount = ((bitCount + (BIT_ARRAY_BITS_IN_ATOM - 1)) / BIT_ARRAY_BITS_IN_ATOM);

    self->array = IMPRINT_CALLOC_TYPE_COUNT(memory, BitArrayAtom, atomCount);
    self->atomCount = atomCount;
    self->bitCount = bitCount;
    self->numberOfBitsSet = 0;
}

/// Resets the structure to its init state.
/// @param self
void bitArrayDestroy(BitArray* self)
{
    //imprintMemoryFree(self->memory, self->array);
    self->array = 0;
}

void bitArrayReset(BitArray* self)
{
}

/// checks if all bits are set
/// @param self
/// @return true if all bits in the array are set
bool bitArrayAreAllSet(const BitArray* self)
{
    return self->bitCount == self->numberOfBitsSet;
}

/// Finds the first bit that is not set in the array
/// @param self
/// @return
size_t bitArrayFirstUnset(const BitArray* self)
{
    for (size_t i = 0; i < self->atomCount; ++i) {
        if (*(self->array + i) != 0xffffffff) {
            BitArrayAtom accumulator = *(self->array + i);
            for (size_t bit = 0; bit < BIT_ARRAY_BITS_IN_ATOM; ++bit) {
                BitArrayAtom mask = 1 << bit;
                if (!(accumulator & mask)) {
                    return i * BIT_ARRAY_BITS_IN_ATOM + bit;
                }
            }
        }
    }

    return self->bitCount;
}

/// Sets the bit at the given index
/// @param self
/// @param index zero based index
void bitArraySet(BitArray* self, size_t index)
{
    size_t arrayIndex = index / BIT_ARRAY_BITS_IN_ATOM;
    size_t bitIndex = index % BIT_ARRAY_BITS_IN_ATOM;
    if (index >= self->bitCount) {
        CLOG_ERROR("wrong");
    }

    BitArrayAtom* p = self->array + arrayIndex;
    BitArrayAtom mask = (1 << bitIndex);

    if (!(*p & mask)) {
        self->numberOfBitsSet++;
    }

    *p |= mask;
}

/// Returrns the atom value that is located at the specified index.
/// @param self
/// @param fromIndex
/// @return the atom value at the specified index
BitArrayAtom bitArrayGetAtomFrom(const BitArray* self, size_t fromIndex)
{
    BitArrayAtom result = 0;

    for (size_t i = 0; i < BIT_ARRAY_BITS_IN_ATOM; ++i) {
        size_t index = fromIndex + (BIT_ARRAY_BITS_IN_ATOM - 1) - i;
        result <<= 1;
        if (index >= self->bitCount) {
            continue;
        }
        result |= bitArrayGet(self, index);
    }

    return result;
}

/// Returns the bit value at the specified index
/// @param self
/// @param index
/// @return
BitArrayBit bitArrayGet(const BitArray* self, size_t index)
{
    size_t arrayIndex = index / BIT_ARRAY_BITS_IN_ATOM;
    size_t bitIndex = index % BIT_ARRAY_BITS_IN_ATOM;

    if (index >= self->bitCount) {
        CLOG_ERROR("wrong");
    }

    return (*(self->array + arrayIndex) >> bitIndex) & 0x1;
}

/// Returns the internal state of the BitArray. Not Implemented!
/// @param self
/// @param buf target buffer
/// @param maxBuf maximum number of characters in the buf target buffer
/// @return
const char* bitArrayToString(const BitArray* self, char* buf, size_t maxBuf)
{
    buf[0] = 0;
    return buf;
}
