#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "Book.h"
#include "Queue.h"
#include "LinkedList.h"

using namespace std;

class Library {
private:
    vector<Book> books;
    unordered_map<string, int> titleMap;
    Queue<string> waitQueue; 
    LinkedList<string> borrowHistory; 
    unordered_map<string, vector<string>> categoryGraph;

    // Huffman Node
    struct HuffmanNode {
        char ch;
        int freq;
        HuffmanNode *left, *right;
        HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
        // Comparator for PriorityQueue (Min-Heap)
        bool operator<(const HuffmanNode& other) const {
            return freq < other.freq; // Min-Heap based on frequency
        }
    };
    
    // Wrapper for pointer comparison in PriorityQueue
    struct NodePtrWrapper {
        HuffmanNode* node;
        NodePtrWrapper(HuffmanNode* n) : node(n) {}
        bool operator<(const NodePtrWrapper& other) const {
            return node->freq < other.node->freq; 
        }
    };

    void generateHuffmanCodes(HuffmanNode* root, string str, unordered_map<char, string>& huffmanCode);
    void deleteHuffmanTree(HuffmanNode* root);

    int partition(vector<Book>& arr, int low, int high);
    void quickSort(vector<Book>& arr, int low, int high);
    void merge(vector<Book>& arr, int l, int m, int r);
    void mergeSort(vector<Book>& arr, int l, int r);
    void heapify(vector<Book>& arr, int n, int i);
    void heapSort(vector<Book>& arr);
    int binarySearch(const vector<Book>& arr, int l, int r, int id);

public:
    void addBook(int id, string t, string a, int y, string c);
    void displayBooks();
    void sortByTitleQuickSort();
    void sortByYearMergeSort();
    void sortByAuthorHeapSort();
    void searchByTitle(string title);
    void searchByID(int id);
    void borrowBook(string title);
    void returnBook(string title);
    void displayHistory();
    
    // Graph Algorithms
    void addCategoryDependency(string parent, string child);
    void displayCategoryTraversalBFS(string startNode);
    void displayCategoryTraversalDFS(string startNode);
    string getCategoryTraversalBFSString(string startNode);
    string getCategoryTraversalDFSString(string startNode);

    // Huffman Coding
    void compressHistory();
    string getCompressedHistoryString();

    vector<Book>& getBooks();
    string getBooksString();
    string searchByTitleString(string title);
    string searchByIDString(int id);
    string getHistoryString();
    string borrowBookString(string title);
    string returnBookString(string title);
};

#endif
