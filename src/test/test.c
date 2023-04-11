/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include "utest.h"
#include <imprint/linear_allocator.h>
#include <bit-array/bit_array.h>

UTEST(BitArray, verifyChunkComplete)
{
    BitArray array;

    ImprintLinearAllocator linearAllocator;
    uint8_t mem[1024];

    imprintLinearAllocatorInit(&linearAllocator, mem, 1024, "all memory");

    bitArrayInit(&array, &linearAllocator.info, 42);

    BitArrayBit bitBefore = bitArrayGet(&array, 3);
    ASSERT_FALSE(bitBefore);
    printf("received before %d\n", bitBefore);
    ASSERT_EQ(bitArrayFirstUnset(&array), 0);
    bitArraySet(&array, 3);

    ASSERT_EQ(bitArrayFirstUnset(&array), 0);
    bitArraySet(&array, 0);
    ASSERT_EQ(bitArrayFirstUnset(&array), 1);
    BitArrayBit bit = bitArrayGet(&array, 3);
    ASSERT_TRUE(bit);

    BitArrayBit bit2 = bitArrayGet(&array, 41);
    ASSERT_FALSE(bit2);
}

UTEST(BitArray, firstUnset)
{
    BitArray array;

    ImprintLinearAllocator linearAllocator;
    uint8_t mem[1024];

    imprintLinearAllocatorInit(&linearAllocator, mem, 1024, "all memory");

    bitArrayInit(&array, &linearAllocator.info, 15);
    for (size_t i = 0; i < 15; ++i)
    {
        bitArraySet(&array, i);
    }

    ASSERT_EQ(bitArrayFirstUnset(&array), 15);
}
