#include <iostream>
#include <vector>
#include <list>
#include <ctime>

#include "list.h"
#include "vector.h"

int main() {
    const int numElements = 10000;
    const int numOperations = 10000;

    // Create instances of LinkedList and VectorList
    LinkedList linkedList;
    VectorList vectorList;

    // Initialize both containers with the same data
    for (int i = 0; i < numElements; ++i) {
        linkedList.insert(i);
        vectorList.insert(i);
    }

    // Measure time for inserting and deleting elements in the middle for linked list
    clock_t start = clock();

    for (int i = 0; i < numOperations; ++i) {
        linkedList.insert(i);
        linkedList.remove(i);
    }

    clock_t end = clock();
    double listTime = double(end - start) / CLOCKS_PER_SEC;

    // Measure time for inserting and deleting elements in the middle for vector list
    start = clock();

    for (int i = 0; i < numOperations; ++i) {
        vectorList.insert(i);
        vectorList.remove(i);
    }

    end = clock();
    double vectorTime = double(end - start) / CLOCKS_PER_SEC;

    std::cout << "Time taken for linked list operations: " << listTime << " seconds" << std::endl;
    std::cout << "Time taken for vector operations: " << vectorTime << " seconds" << std::endl;

    return 0;
}
