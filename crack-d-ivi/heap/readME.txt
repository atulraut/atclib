
MinHeap using C :

https://algorithmtutor.com/Data-Structures/Tree/Binary-Heaps/
https://www.geeksforgeeks.org/binary-heap/

http://opendatastructures.org/versions/edition-0.1e/ods-java/10_1_BinaryHeap_Implicit_Bi.html#sec:binaryheap

Priority Queue : https://www.geeksforgeeks.org/priority-queue-using-linked-list/

Binary Heap :
A Binary Heap is a Binary Tree with following properties.
1) It’s a complete tree (All levels are completely filled except possibly the
last level and the last level has all keys as left as possible).
This property of Binary Heap makes them suitable to be stored in an array.

2) A Binary Heap is either Min Heap or Max Heap. In a Min Binary Heap,
the key at root must be minimum among all keys present in Binary Heap.
The same property must be recursively true for all nodes in Binary Tree. Max Binary Heap is similar to MinHeap.

Examples of Min Heap:

            10                      10
         /      \               /       \
       20        100          15         30
      /                      /  \        /  \
    30                     40    50    100   40

How is Binary Heap represented?
A Binary Heap is a Complete Binary Tree. A binary heap is typically represented as an array.

    The root element will be at Arr[0].
    Below table shows indexes of other nodes for the ith node, i.e., Arr[i]:
    Arr[(i-1)/2] Returns the parent node
    Arr[(2*i)+1] Returns the left child node
    Arr[(2*i)+2] Returns the right child node

    The traversal method use to achieve Array representation is Level Order

