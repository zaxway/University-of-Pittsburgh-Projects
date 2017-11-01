/* Mohit Jain, MOJ10 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mymalloc.h"

// The smallest allocation possible is this many bytes.
// Any allocations <= this size will b put in bin 0.
#define MINIMUM_ALLOCATION  16

// Every bin holds blocks whose sizes are a multiple of this number.
#define SIZE_MULTIPLE       8

// The biggest bin holds blocks of this size. Anything bigger will go in the overflow bin.
#define BIGGEST_BINNED_SIZE 512

// How many bins there are. There's an "underflow" bin (bin 0) and an overflow bin (the last bin).
// That's where the '2' comes from in this formula.
#define NUM_BINS            (2 + ((BIGGEST_BINNED_SIZE - MINIMUM_ALLOCATION) / SIZE_MULTIPLE))

// The index of the overflow bin.
#define OVERFLOW_BIN        (NUM_BINS - 1)

// How many bytes the block header is, in a USED block.
// NEVER USE sizeof(BlockHeader) in your calculations! Use this instead.
#define BLOCK_HEADER_SIZE   offsetof(BlockHeader, prev_free)

// The smallest number of bytes a block (including header and data) can be.
#define MINIMUM_BLOCK_SIZE  (MINIMUM_ALLOCATION + BLOCK_HEADER_SIZE)



// think of this as a node class
typedef struct BlockHeader
{
	unsigned int size; // The byte size of the data area of this block.
	int in_use;        // 1 if allocated, 0 if free.

	// Doubly-linked list pointers for the previous and next *physical* blocks of memory.
	// All blocks, allocated or free, must keep track of this for coalescing purposes.
	struct BlockHeader* prev_phys; // previous node (1st linked list)
	struct BlockHeader* next_phys; // next node (1st linked list)

	// These next two members are only valid if the block is not in use (on a free list).
	// If the block is in use, the user-allocated data starts here instead!
	struct BlockHeader* prev_free; // previous node (2nd linked list)
	struct BlockHeader* next_free; // next node (2nd linked list)
} BlockHeader;





// Your array of bins.
BlockHeader* bins[NUM_BINS] = {};

// The LAST allocated block on the heap.
// This is used to keep track of when you should contract the heap.
BlockHeader* heaptail = NULL;

// =================================================================================================
// Math helpers
// =================================================================================================

// Given a pointer and a number of bytes, gives a new pointer that points to the original address
// plus or minus the offset. The offset can be negative.
// Since this returns a void*, you have to cast the result to another pointer type to use it.
void* ptr_add_bytes(void* ptr, int byte_offs)
{
	return (void*)(((char*)ptr) + byte_offs);
}

// Gives the number of bytes between the two pointers. first must be <= second.
unsigned int bytes_between_ptrs(void* first, void* second)
{
	return (unsigned int)(((char*)second) - ((char*)first));
}

// Given a pointer to a block header, gives the pointer to its data (such as what you'd return
// from my_malloc).
void* block_to_data(BlockHeader* block)
{
	return (void*)ptr_add_bytes(block, BLOCK_HEADER_SIZE);
}

// Given a data pointer (such as passed to my_free()), gives the pointer to the block that
// contains it.
BlockHeader* data_to_block(void* data)
{
	return (BlockHeader*)ptr_add_bytes(data, -BLOCK_HEADER_SIZE);
}

// Given a data size, gives how many bytes you'd need to allocate for a block to hold it.
unsigned int data_size_to_block_size(unsigned int data_size)
{
	return data_size + BLOCK_HEADER_SIZE;
}

// Rounds up a data size to an appropriate size for putting into a bin.
unsigned int round_up_size(unsigned int data_size)
{
	if(data_size == 0)
		return 0;
	else if(data_size < MINIMUM_ALLOCATION)
		return MINIMUM_ALLOCATION;
	else
		return (data_size + (SIZE_MULTIPLE - 1)) & ~(SIZE_MULTIPLE - 1);
}

// Given a data size in bytes, gives the correct bin index to put it in.
unsigned int size_to_bin(unsigned int data_size)
{
	unsigned int bin = (round_up_size(data_size) - MINIMUM_ALLOCATION) / SIZE_MULTIPLE;

	if(bin > OVERFLOW_BIN)
		return OVERFLOW_BIN;
	else
		return bin;
}

// =================================================================================================
// Your functions!
// =================================================================================================

// Put any of your code here.

// =================================================================================================
// Public functions
// =================================================================================================

void* my_malloc(unsigned int size)
{
	if(size == 0)
		return NULL;

	size = round_up_size(size);

	// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	// Any allocation code goes here!

	BlockHeader* newblock = sbrk(size + BLOCK_HEADER_SIZE);
	newblock-> in_use = 1;
	newblock-> size = size;
	// expanding the heap
	newblock-> prev_phys = heaptail;
	newblock-> next_phys = NULL;
	heaptail = newblock;
	if (heaptail != NULL) {
		heaptail-> next_phys = newblock;
	}

	return block_to_data(newblock);

	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}

void my_free(void* ptr)
{
	if(ptr == NULL)
		return;

	BlockHeader* block_to_free = data_to_block(ptr);
	// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	// Any deallocation code goes here!
	brk(ptr);
	// contracting the heap
	if(heaptail != NULL) {
		heaptail-> next_phys = block_to_free;
	}
	if(block_to_free == heaptail) {
		heaptail = block_to_free-> prev_phys;
		brk(heaptail);
	}
	// if last block on heap, then break
	if(block_to_free == heaptail) {
		brk(block_to_free);
	}
	//otherwise, set in use to 0 and link to as the head of the free list
	else {
		block_to_free = 0;
		block_to_free = bins[OVERFLOW_BIN];
	}

	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}
