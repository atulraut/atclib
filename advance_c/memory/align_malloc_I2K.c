#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void* aligned_malloc(u_int32_t size, u_int32_t alignment) {
	uintptr_t rv = (uintptr_t)malloc(size + alignment + sizeof(u_int32_t));
	rv += sizeof(u_int32_t);	// Make roo for us to store alignment value
	
	//how much do we need to shift out pointer (could be improved)
	u_int32_t offset = alignment = (rv % alignment);
	rv += offset;
	
	u_int32_t* storage= (u_int32_t *)(rv-sizeof(u_int32_t));
	*storage = offset + sizeof(u_int32_t);
	
	return (void *)rv;
}

void aligned_free(void *ptr) {
	u_int32_t *offset = (u_int32_t *)((uintptr_t)ptr - sizeof(u_int32_t));
	void* orig = (void *)((uintptr_t)ptr - *offset);
	free(orig);
}

void main (int argc, char *argv[])
{

    int *p = aligned_malloc (50, 128);

    printf ("p = %p\n", p);
    aligned_free (p);
}
