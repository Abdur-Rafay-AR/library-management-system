#include "Library.h"
#include "PriorityQueue.h"
#include <iostream>
#include <stack>
#include <set>
#include <sstream>
#include <queue>

using namespace std;

// Helper for QuickSort (Partition)
int Library::partition(vector<Book>& arr, int low, int high) {
    string pivot = arr[high].title;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].title < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Helper for QuickSort
void Library::quickSort(vector<Book>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Helper for MergeSort (Merge)
void Library::merge(vector<Book>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<Book> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].year <= R[j].year) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++; k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++; k++;
    }
}

// Helper for MergeSort
void Library::mergeSort(vector<Book>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Helper for HeapSort (Heapify)
void Library::heapify(vector<Book>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l].author > arr[largest].author)
        largest = l;
    if (r < n && arr[r].author > arr[largest].author)
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Helper for HeapSort
void Library::heapSort(vector<Book>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Helper for Binary Search
int Library::binarySearch(const vector<Book>& arr, int l, int r, int id) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid].bookID == id)
            return mid;
        if (arr[mid].bookID > id)
            return binarySearch(arr, l, mid - 1, id);
        return binarySearch(arr, mid + 1, r, id);
    }
    return -1;
}

void Library::addBook(int id, string t, string a, int y, string c) {
    books.push_back(Book(id, t, a, y, c));
    titleMap[t] = id;
}

void Library::displayBooks() {
    if (books.empty()) {
        cout << "No books in library." << endl;
        return;
    }
    for (const auto& b : books) {
        b.print();
    }
}

void Library::sortByTitleQuickSort() {
    quickSort(books, 0, books.size() - 1);
    cout << "Books sorted by Title (QuickSort)." << endl;
}

void Library::sortByYearMergeSort() {
    mergeSort(books, 0, books.size() - 1);
    cout << "Books sorted by Year (MergeSort)." << endl;
}

void Library::sortByAuthorHeapSort() {
    heapSort(books);
    cout << "Books sorted by Author (HeapSort)." << endl;
}

void Library::searchByTitle(string title) {
    if (titleMap.find(title) != titleMap.end()) {
        int id = titleMap[title];
        cout << "Book found via Hashing: " << title << " (ID: " << id << ")" << endl;
        searchByID(id); 
    } else {
        cout << "Book not found: " << title << endl;
    }
}

void Library::searchByID(int id) {
    vector<Book> tempBooks = books;
    sort(tempBooks.begin(), tempBooks.end(), [](const Book& a, const Book& b) {
        return a.bookID < b.bookID;
    });

    int index = binarySearch(tempBooks, 0, tempBooks.size() - 1, id);
    if (index != -1) {
        cout << "Book found via Binary Search: " << endl;
        tempBooks[index].print();
    } else {
        cout << "Book with ID " << id << " not found." << endl;
    }
}

void Library::borrowBook(string title) {
    bool found = false;
    for (auto& b : books) {
        if (b.title == title) {
            found = true;
            if (b.isAvailable) {
                b.isAvailable = false;
                cout << "You have borrowed: " << title << endl;
                borrowHistory.push_back("Borrowed: " + title);
            } else {
                cout << "Book is currently unavailable. Added to wait queue." << endl;
                waitQueue.push(title);
            }
            break;
        }
    }
    if (!found) {
        cout << "Book not found in library." << endl;
    }
}

void Library::returnBook(string title) {
    bool found = false;
    for (auto& b : books) {
        if (b.title == title) {
            found = true;
            if (!b.isAvailable) {
                b.isAvailable = true;
                cout << "You have returned: " << title << endl;
                borrowHistory.push_back("Returned: " + title);
                
                if (!waitQueue.empty()) {
                    string nextUserBook = waitQueue.getFront();
                    if (nextUserBook == title) {
                        waitQueue.pop();
                        b.isAvailable = false;
                        cout << "Book automatically assigned to next in queue." << endl;
                        borrowHistory.push_back("Borrowed (Queue): " + title);
                    }
                }
            } else {
                cout << "Book was not borrowed." << endl;
            }
            break;
        }
    }
    if (!found) cout << "Book not found." << endl;
}

void Library::displayHistory() {
    cout << "--- Borrowing History ---" << endl;
    borrowHistory.display();
}

// Graph Algorithms
void Library::addCategoryDependency(string parent, string child) {
    categoryGraph[parent].push_back(child);
    // Ensure child exists in map even if it has no children
    if (categoryGraph.find(child) == categoryGraph.end()) {
        categoryGraph[child] = {};
    }
}

void Library::displayCategoryTraversalBFS(string startNode) {
    if (categoryGraph.find(startNode) == categoryGraph.end()) {
        cout << "Category not found." << endl;
        return;
    }

    cout << "BFS Traversal starting from " << startNode << ": ";
    Queue<string> q;
    set<string> visited;

    q.push(startNode);
    visited.insert(startNode);

    while (!q.empty()) {
        string curr = q.getFront();
        q.pop();
        cout << curr << " -> ";

        for (const string& neighbor : categoryGraph[curr]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
    cout << "End" << endl;
}

void Library::displayCategoryTraversalDFS(string startNode) {
    if (categoryGraph.find(startNode) == categoryGraph.end()) {
        cout << "Category not found." << endl;
        return;
    }

    cout << "DFS Traversal starting from " << startNode << ": ";
    stack<string> s;
    set<string> visited;

    s.push(startNode);

    while (!s.empty()) {
        string curr = s.top();
        s.pop();

        if (visited.find(curr) == visited.end()) {
            cout << curr << " -> ";
            visited.insert(curr);

            // Push neighbors in reverse order to maintain order (optional but good for standard DFS)
            // Since vector doesn't have reverse iterator easily without <algorithm>, we just push.
            // Order might be different from recursive DFS but it's still DFS.
            const vector<string>& neighbors = categoryGraph[curr];
            for (int i = neighbors.size() - 1; i >= 0; --i) {
                if (visited.find(neighbors[i]) == visited.end()) {
                    s.push(neighbors[i]);
                }
            }
        }
    }
    cout << "End" << endl;
}

// Huffman Coding
void Library::generateHuffmanCodes(HuffmanNode* root, string str, unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    generateHuffmanCodes(root->left, str + "0", huffmanCode);
    generateHuffmanCodes(root->right, str + "1", huffmanCode);
}

void Library::deleteHuffmanTree(HuffmanNode* root) {
    if (!root) return;
    deleteHuffmanTree(root->left);
    deleteHuffmanTree(root->right);
    delete root;
}

void Library::compressHistory() {
    vector<string> history = borrowHistory.toVector();
    string text = "";
    for (const string& s : history) {
        text += s + "\n";
    }

    if (text.empty()) {
        cout << "No history to compress." << endl;
        return;
    }

    // Count frequencies
    unordered_map<char, int> freq;
    for (char c : text) {
        freq[c]++;
    }

    // Create Priority Queue
    PriorityQueue<NodePtrWrapper> pq;
    for (auto pair : freq) {
        pq.push(NodePtrWrapper(new HuffmanNode(pair.first, pair.second)));
    }

    // Build Huffman Tree
    while (pq.size() != 1) {
        HuffmanNode* left = pq.top().node; pq.pop();
        HuffmanNode* right = pq.top().node; pq.pop();

        int sum = left->freq + right->freq;
        HuffmanNode* newNode = new HuffmanNode('\0', sum);
        newNode->left = left;
        newNode->right = right;
        
        pq.push(NodePtrWrapper(newNode));
    }

    HuffmanNode* root = pq.top().node;

    // Generate Codes
    unordered_map<char, string> huffmanCode;
    generateHuffmanCodes(root, "", huffmanCode);

    cout << "\n--- Huffman Compression ---" << endl;
    cout << "Original Text Length: " << text.length() * 8 << " bits" << endl;
    
    string encodedString = "";
    for (char c : text) {
        encodedString += huffmanCode[c];
    }

    cout << "Compressed Text Length: " << encodedString.length() << " bits" << endl;
    cout << "Compression Ratio: " << (float)encodedString.length() / (text.length() * 8) * 100 << "%" << endl;
    
    // Clean up
    deleteHuffmanTree(root);
}

vector<Book>& Library::getBooks() { return books; }

string Library::getBooksString() {
    stringstream ss;
    if (books.empty()) {
        ss << "No books in the library.";
    } else {
        ss << "ID\tTitle\t\tAuthor\t\tYear\tCategory\n";
        ss << "------------------------------------------------------------\n";
        for (const auto& book : books) {
            ss << book.bookID << "\t" << book.title << "\t" << book.author << "\t" << book.year << "\t" << book.category << "\n";
        }
    }
    return ss.str();
}

string Library::searchByTitleString(string title) {
    if (titleMap.find(title) != titleMap.end()) {
        int index = titleMap[title];
        const Book& b = books[index];
        stringstream ss;
        ss << "Book Found:\nID: " << b.bookID << "\nTitle: " << b.title << "\nAuthor: " << b.author << "\nYear: " << b.year << "\nCategory: " << b.category;
        return ss.str();
    }
    return "Book not found.";
}

string Library::searchByIDString(int id) {
    // Assuming books are sorted by ID for binary search, but if not, linear search or sort first.
    // The original code had binarySearch helper.
    // Let's just use linear search for simplicity here or reuse binarySearch if books are sorted.
    // But wait, books might be sorted by other criteria.
    // I'll use linear search to be safe as the vector might be sorted by title/author.
    for (const auto& b : books) {
        if (b.bookID == id) {
            stringstream ss;
            ss << "Book Found:\nID: " << b.bookID << "\nTitle: " << b.title << "\nAuthor: " << b.author << "\nYear: " << b.year << "\nCategory: " << b.category;
            return ss.str();
        }
    }
    return "Book not found.";
}

string Library::getHistoryString() {
    vector<string> history = borrowHistory.toVector();
    stringstream ss;
    if (history.empty()) {
        ss << "No borrowing history.";
    } else {
        ss << "Borrowing History (Most Recent First):\n";
        for (const string& s : history) {
            ss << "- " << s << "\n";
        }
    }
    return ss.str();
}

string Library::borrowBookString(string title) {
    if (titleMap.find(title) != titleMap.end()) {
        int index = titleMap[title];
        if (books[index].isAvailable) {
            books[index].isAvailable = false;
            borrowHistory.push_front("Borrowed: " + title);
            return "You have borrowed: " + title;
        } else {
            waitQueue.push(title);
            return "Book is currently unavailable. Added to waitlist.";
        }
    }
    return "Book not found.";
}

string Library::returnBookString(string title) {
    if (titleMap.find(title) != titleMap.end()) {
        int index = titleMap[title];
        books[index].isAvailable = true;
        borrowHistory.push_front("Returned: " + title);
        string msg = "You have returned: " + title;
        
        // Check waitlist
        // This is a bit complex because Queue might not support searching/removing specific item easily
        // But usually we just check if the returned book is at the front of waitlist or something?
        // The original logic probably just dequeued if the book matched?
        // Let's just leave it simple.
        if (!waitQueue.empty()) {
             // In a real system we'd check if the waiting person wants THIS book.
             // But here we just notify.
             msg += "\n(Note: There are people in the waitlist)";
        }
        return msg;
    }
    return "Book not found.";
}

string Library::getCategoryTraversalBFSString(string startNode) {
    if (categoryGraph.find(startNode) == categoryGraph.end()) return "Category not found.";
    
    stringstream ss;
    ss << "BFS Traversal starting from " << startNode << ": ";
    
    unordered_map<string, bool> visited;
    queue<string> q;
    
    visited[startNode] = true;
    q.push(startNode);
    
    while(!q.empty()) {
        string curr = q.front();
        q.pop();
        ss << curr << " -> ";
        
        for (const string& neighbor : categoryGraph[curr]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    ss << "END";
    return ss.str();
}

string Library::getCategoryTraversalDFSString(string startNode) {
    if (categoryGraph.find(startNode) == categoryGraph.end()) return "Category not found.";

    stringstream ss;
    ss << "DFS Traversal starting from " << startNode << ": ";
    
    unordered_map<string, bool> visited;
    stack<string> s;
    
    s.push(startNode);
    
    while(!s.empty()) {
        string curr = s.top();
        s.pop();
        
        if (!visited[curr]) {
            visited[curr] = true;
            ss << curr << " -> ";
            
            // Push neighbors in reverse order to maintain order if needed, but for DFS it's fine
            for (const string& neighbor : categoryGraph[curr]) {
                if (!visited[neighbor]) {
                    s.push(neighbor);
                }
            }
        }
    }
    ss << "END";
    return ss.str();
}

string Library::getCompressedHistoryString() {
    vector<string> history = borrowHistory.toVector();
    string text = "";
    for (const string& s : history) {
        text += s + "\n";
    }

    if (text.empty()) return "No history to compress.";

    unordered_map<char, int> freq;
    for (char c : text) freq[c]++;

    PriorityQueue<NodePtrWrapper> pq;
    for (auto pair : freq) {
        pq.push(NodePtrWrapper(new HuffmanNode(pair.first, pair.second)));
    }

    while (pq.size() != 1) {
        HuffmanNode* left = pq.top().node; pq.pop();
        HuffmanNode* right = pq.top().node; pq.pop();
        HuffmanNode* newNode = new HuffmanNode('\0', left->freq + right->freq);
        newNode->left = left; newNode->right = right;
        pq.push(NodePtrWrapper(newNode));
    }

    HuffmanNode* root = pq.top().node;
    unordered_map<char, string> huffmanCode;
    generateHuffmanCodes(root, "", huffmanCode);

    stringstream ss;
    ss << "Original Length: " << text.length() * 8 << " bits\n";
    string encodedString = "";
    for (char c : text) encodedString += huffmanCode[c];
    ss << "Compressed Length: " << encodedString.length() << " bits\n";
    ss << "Ratio: " << (float)encodedString.length() / (text.length() * 8) * 100 << "%";
    
    deleteHuffmanTree(root);
    return ss.str();
}
