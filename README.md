# University Library Management System (ULMS)

A comprehensive Library Management System implemented in C++ with a graphical user interface using SFML. This project demonstrates the practical application of various data structures and algorithms for efficient data handling.

## Features

### Data Structures & Algorithms
*   **Book Storage**: Uses `std::vector` for dynamic storage and random access.
*   **Searching**:
    *   **By Title**: Implemented using Hashing (`std::unordered_map`) for O(1) average complexity.
    *   **By ID**: Implemented using Binary Search for O(log n) complexity.
*   **Sorting**:
    *   **By Title**: QuickSort.
    *   **By Year**: MergeSort.
    *   **By Author**: HeapSort.
*   **Borrowing System**:
    *   **Waitlist**: Uses a custom `Queue` (FIFO) to manage book requests.
    *   **History**: Uses a custom `LinkedList` to track borrowing/returning history.
*   **Category Management**:
    *   Graph representation (Adjacency List) for book categories.
    *   Supports BFS (Breadth-First Search) and DFS (Depth-First Search) traversal.
*   **Data Compression**:
    *   Huffman Coding algorithm used to compress borrowing history text.

### Graphical User Interface (GUI)
*   Built using **SFML** (Simple and Fast Multimedia Library).
*   Interactive menus for adding books, searching, sorting, and viewing history.

## Prerequisites

*   **C++ Compiler**: GCC (MinGW for Windows) or compatible.
*   **SFML**: Included in the `SFML/` directory.

## Build and Run

This project is configured for VS Code.

1.  **Build the Project**:
    *   Open the Command Palette (`Ctrl+Shift+P`).
    *   Select `Tasks: Run Task`.
    *   Choose `build sfml test`.
    *   This will compile the source code and generate `LibrarySystem.exe`.

2.  **Setup Dependencies**:
    *   If this is your first time running, you need to copy the SFML DLLs to the project root.
    *   Run the task `copy dlls` via `Tasks: Run Task`.

3.  **Run**:
    *   Execute the generated file: `LibrarySystem.exe`

## Project Structure

*   `src/`: Contains source code files (`main.cpp`, `Library.cpp`, etc.).
*   `include/`: Contains header files (`Library.h`, `Book.h`, data structure classes).
*   `SFML/`: Contains SFML library headers, libs, and binaries.
*   `REPORT.md`: Detailed report on data structure choices and complexity analysis.

## License

This project uses SFML. See `SFML/license.md` for details.
