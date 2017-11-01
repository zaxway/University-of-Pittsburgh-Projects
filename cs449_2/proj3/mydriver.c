#include <stdio.h>
#include <unistd.h>

#include "mymalloc.h"

int main()
{
	// start of professor code
	int* a = my_malloc(sizeof(int) * 10);
	int* b = my_malloc(sizeof(int) * 10);

	// Now put some code here that fills both the a and b arrays.

	my_free(b);
	my_free(a);

	// end of professor code
	void* heap_at_start = sbrk(0);

	void* block = my_malloc(100);
	my_free(block);

	void* heap_at_end = sbrk(0);
	unsigned int heap_size_diff = (unsigned int)(heap_at_end - heap_at_start);

	if(heap_size_diff)
		printf("Hmm, the heap got bigger by %u (0x%X) bytes...\n", heap_size_diff, heap_size_diff);

	return 0;
}
