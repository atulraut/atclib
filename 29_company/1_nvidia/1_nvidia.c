NVIDIA IVI :


Given your recent focus on Linux/kernel, drivers, RDMA, and C, these are the C questions I would practice first:
1. Pointers / memory
   - Difference between int *p, const int *p, int * const p, const int * const p
   - What is a dangling pointer?
   - NULL vs uninitialized pointer
   - Pointer arithmetic
   - void *
   - Function pointers
   - Pointer to pointer
   - Array vs pointer
   - sizeof(array) vs sizeof(pointer)
   - Explain char **argv
   - Implement container_of()
2. Memory management
   - Implement your own aligned_malloc() / aligned_free()
   - malloc() vs calloc() vs realloc()
   - What happens internally during malloc()?
   - Heap fragmentation
   - Memory leak detection
   - Double free
   - Use-after-free
   - Stack vs heap
   - Design a simple memory pool
3. Bit manipulation
   - Set/clear/toggle/test nth bit
   - Count set bits
   - Check power of 2
   - Find odd-occurring number
   - Reverse 32-bit integer bits
   - Swap adjacent bits
   - Extract bits [m:n]
   - Find first set bit
   - Alignment using bit operations
4. C language traps
   - volatile
   - static
   - extern
   - const
   - restrict
   - Structure padding/alignment
   - Endianness
   - Undefined behavior
   - Sequence points/evaluation ordering
   - Macro vs inline function
   - ++*p, *p++, (*p)++, *++p
5. Coding
   - Reverse linked list
   - Detect linked-list cycle
   - Find cycle starting node
   - LRU cache
   - Circular FIFO
   - Thread-safe queue
   - Hash table
   - Binary search
   - Merge intervals
   - Producer/consumer
   - Ring buffer

1. Implement thread-safe circular FIFO
2. Implement producer/consumer queue
3. Implement aligned_malloc/aligned_free
4. Implement memcpy/memmove
5. Implement a fixed-size memory pool
   https://github.com/atulraut/atclib/blob/master/memory/3_fixed-size_memory_pool.c
6. Implement reference counting
   https://github.com/atulraut/atclib/blob/master/array/crack-d-ivi/29_reference_counting.c
7. Reverse a linked list
8. Detect a linked-list cycle
9. Implement LRU cache
    https://github.com/atulraut/atclib/blob/master/linkedlist/leetcode/lRUCacheCreate.c
10. Remove duplicates from sorted/unsorted array
    https://github.com/atulraut/atclib/blob/master/array/crack-d-ivi/1_missing_unsorted_array-hashMap.c
    https://github.com/atulraut/interviewKickstart/blob/dae3991bb795f4513b364cef34a4e308f89b193d/3_arrays/1_coding_arrays_live_arrays_part_1_class_with_Omkar/3_5_Find_the_Duplicate_Number_in_Array/3_removeDuplicates.c#L95
11. Parse command-line/configuration strings safely
    https://github.com/atulraut/atclib/blob/master/strings/crack-d-ivi/18_parse_cndline.c
12. Implement a bitmap allocator
13. Set/clear/extract arbitrary bit fields
14. Reverse bits of uint32_t
15. Convert endianness
16. Implement atomic-ish counter and discuss why ++ isn't atomic
17. Implement reader/writer protected shared structure
18. Write register polling with timeout
19. Write a simple device FIFO read/write interface
20. Debug deliberately broken multithreaded C code
