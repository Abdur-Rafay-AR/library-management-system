#include <iostream>
#include "Library.h"

using namespace std;

void printMenu() {
    cout << "\n=== University Library Management System ===" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Display All Books" << endl;
    cout << "3. Search Book" << endl;
    cout << "4. Borrow Book" << endl;
    cout << "5. Return Book" << endl;
    cout << "6. View Borrowing History" << endl;
    cout << "7. Sort Books" << endl;
    cout << "8. Category Analysis (Graph BFS/DFS)" << endl;
    cout << "9. Compress History (Huffman)" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

int main_console() {
    Library lib;
    
    // Pre-populate with some data
    lib.addBook(101, "The C++ Programming Language", "Bjarne Stroustrup", 2013, "Programming");
    lib.addBook(105, "Introduction to Algorithms", "Cormen", 2009, "Algorithms");
    lib.addBook(102, "Clean Code", "Robert C. Martin", 2008, "Software Engineering");
    lib.addBook(104, "Design Patterns", "Erich Gamma", 1994, "Software Engineering");
    lib.addBook(103, "The Pragmatic Programmer", "Andrew Hunt", 1999, "Software Engineering");

    // Pre-populate Graph
    lib.addCategoryDependency("Programming", "Algorithms");
    lib.addCategoryDependency("Programming", "Software Engineering");
    lib.addCategoryDependency("Software Engineering", "Design Patterns");

    int choice;
    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, year;
                string title, author, category;
                cout << "Enter ID: "; cin >> id;
                cin.ignore(); // clear buffer
                cout << "Enter Title: "; getline(cin, title);
                cout << "Enter Author: "; getline(cin, author);
                cout << "Enter Year: "; cin >> year;
                cin.ignore();
                cout << "Enter Category: "; getline(cin, category);
                lib.addBook(id, title, author, year, category);
                break;
            }
            case 2:
                lib.displayBooks();
                break;
            case 3: {
                int searchType;
                cout << "1. Search by Title (Hashing)\n2. Search by ID (Binary Search)\nChoice: ";
                cin >> searchType;
                if (searchType == 1) {
                    string t;
                    cout << "Enter Title: ";
                    cin.ignore();
                    getline(cin, t);
                    lib.searchByTitle(t);
                } else {
                    int id;
                    cout << "Enter ID: ";
                    cin >> id;
                    lib.searchByID(id);
                }
                break;
            }
            case 4: {
                string t;
                cout << "Enter Book Title to Borrow: ";
                cin.ignore();
                getline(cin, t);
                lib.borrowBook(t);
                break;
            }
            case 5: {
                string t;
                cout << "Enter Book Title to Return: ";
                cin.ignore();
                getline(cin, t);
                lib.returnBook(t);
                break;
            }
            case 6:
                lib.displayHistory();
                break;
            case 7: {
                int sortType;
                cout << "1. Sort by Title (QuickSort)\n2. Sort by Year (MergeSort)\n3. Sort by Author (HeapSort)\nChoice: ";
                cin >> sortType;
                if (sortType == 1) lib.sortByTitleQuickSort();
                else if (sortType == 2) lib.sortByYearMergeSort();
                else if (sortType == 3) lib.sortByAuthorHeapSort();
                break;
            }
            case 8: {
                string startNode;
                cout << "Enter Start Category for Traversal (e.g., Programming): ";
                cin.ignore();
                getline(cin, startNode);
                lib.displayCategoryTraversalBFS(startNode);
                lib.displayCategoryTraversalDFS(startNode);
                break;
            }
            case 9:
                lib.compressHistory();
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}
