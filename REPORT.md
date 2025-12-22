# University Library Management System (ULMS) - Project Report

## 1. Choice of Data Structures
*   **Book Storage**: `std::vector<Book>` was chosen for storing books because it provides dynamic resizing and random access, which is useful for sorting algorithms.
*   **Borrowing Queue**: A custom `Queue` class (implemented using a linked list) is used to manage borrowing requests in a First-In-First-Out (FIFO) manner. This ensures fairness in book allocation.
*   **Borrowing History**: A custom `LinkedList` class is used to store the history of borrowing and returning books. Linked lists are efficient for insertions at the end (O(1) with a tail pointer) and do not require contiguous memory.
*   **Category Relationships**: An `unordered_map<string, vector<string>>` (Adjacency List) is used to represent the graph of book categories. This allows for efficient storage of sparse graphs and quick lookup of neighbors.
*   **Searching**: 
    *   **Hashing**: `std::unordered_map` is used for O(1) average time complexity search by Title.
    *   **Binary Search**: Used for searching by BookID, requiring the list to be sorted, offering O(log n) complexity.

## 2. Complexity Analysis
### Sorting Algorithms
*   **QuickSort**: 
    *   Time Complexity: Average O(n log n), Worst O(n^2).
    *   Space Complexity: O(log n) stack space.
    *   Used for sorting by Title.
*   **MergeSort**: 
    *   Time Complexity: O(n log n) in all cases.
    *   Space Complexity: O(n) for auxiliary arrays.
    *   Used for sorting by Year.
*   **HeapSort**: 
    *   Time Complexity: O(n log n).
    *   Space Complexity: O(1) auxiliary space (in-place).
    *   Used for sorting by Author.

### Searching Algorithms
*   **Binary Search**: 
    *   Time Complexity: O(log n).
    *   Requires sorted array.
*   **Hashing**: 
    *   Time Complexity: Average O(1), Worst O(n).
    *   Space Complexity: O(n) for the hash table.

### Graph Algorithms
*   **BFS (Breadth-First Search)**: 
    *   Time Complexity: O(V + E), where V is vertices (categories) and E is edges (relationships).
    *   Space Complexity: O(V) for the queue and visited set.
*   **DFS (Depth-First Search)**: 
    *   Time Complexity: O(V + E).
    *   Space Complexity: O(V) for the stack (recursion or explicit stack) and visited set.

### Other
*   **Huffman Coding**: 
    *   Time Complexity: O(n log n) where n is the number of unique characters (or total characters depending on implementation details of building the tree). Building the tree takes O(k log k) where k is unique characters.
    *   Space Complexity: O(k) for the tree and codes.
    *   Used to compress the borrowing history text.

## 3. Challenges Faced
*   **Custom Data Structures**: Implementing `Queue` and `LinkedList` from scratch required careful memory management (handling pointers and destructors) to avoid memory leaks.
*   **Integration**: Integrating multiple algorithms (Sorting, Searching, Graph, Huffman) into a single cohesive system required careful planning of the class structure.
*   **Huffman Coding**: Handling the conversion between the linked list history and the string format for compression, and implementing the Min-Heap priority queue for Huffman tree construction.

