# C_DataStructures
Data Structures made in C

## Purpose
To provide pure C data structure libraries, aimed to simplify the development of future projects.

## Structures included

### Doubly Linked List
This structure is a Doubly Linked List which allows you to traverse through the structure from head to tail and vice-versa.
It allows searching with positive and negative indexing, similarly to what Python allows with its native lists.
When searching, deleting, and adding, it prevents accessing memory outside the bounds of the list by truncating the index to the head and tail of the list.

The data stored in the list can be of any type and the list does not have to have the same data type stored in each node. It is the developers responsibility to keep track of which type they are accessing. The list only stores the size of the type, therefore it is the responsibility of the developer to be aware of which size corresponds to which type, and in the event of having types of equal sizes, which type are they expecting from it.

### Stack
A regular stack that stores data of any type. Additionaly, the data stored in the stack can be of any type. The developer must keep track of which type they have stored and which one they are accessing. 

### Queue
A regular queue that stores any data of any type. The developer must keep track of which type they have stored.

Additional implementation to retrieve the data size at a node is needed.

### Sequential Binary Tree
This data structure is a binary tree stored in an array. This means that the location of all the pointers to the data will be allocated in a linear section of the memory. This does not mean that the data of each node will be stored in the same memory location. 

The nodes in the tree can be accessed with an index, in which the root is at index 1. The children of each node will be found at index (i \* 2) and (i \* 2) + 1. The parent of each node will be found at address (i / 2).

Insertion of a node in the middle of the tree will only happen if the node at said index has an empty child.

Deletion of a node that has children will cause its children to be shifted up. The default node to be shifted up is the right child. This will be iteratively done until a leaf is reached.

A function to print the tree is available. It will print if it is a left or right child, its index, the number of bytes it holds, and the location at which the node points to for the data.

### Heap
This structure involves a sequential binary tree with some more special functions. First, the structure takes in a comparison function. The contents of this function will dictate if the heap will be a Max-Heap or a Min-Heap. If the function has the form of "param1 <= param2" it will be a Min-Heap.

Whenever a value is inserted or deleted from the heap, it will rebalance itself, making sure that the value added meets the requirements of the Min-Heap or Max-Heap.
Deletion from the heap only happens from the root, which consequentially causes the structure to return the maximum or minimum value.

The structure also allows you to "heapify" an array.


## Future modifications

 - Graph
 - Hash Map
 - **Callback Functions for the remove/delete functions of all data structures**