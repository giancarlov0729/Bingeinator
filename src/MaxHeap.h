//
// Created by Giancarlo Vidal on 12/2/24.
//

#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <vector>
#include <stdexcept>
#include "Node.h"

class MaxHeap {
private:
    std::vector<Node> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index].rating <= heap[parent].rating)
                break;
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < heap.size() && heap[left].rating > heap[largest].rating)
            largest = left;
        if (right < heap.size() && heap[right].rating > heap[largest].rating)
            largest = right;

        if (largest != index) {
            std::swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    void insert(const Node& node) {
        heap.push_back(node);
        heapifyUp(heap.size() - 1);
    }

    Node extractMax() {
        if (heap.empty())
            throw std::out_of_range("Heap is empty");
        Node maxNode = heap.front();
        heap.front() = heap.back();
        heap.pop_back();
        if (!heap.empty())
            heapifyDown(0);
        return maxNode;
    }

    const Node& getMax() const {
        if (heap.empty())
            throw std::out_of_range("Heap is empty");
        return heap.front();
    }

    bool isEmpty() const {
        return heap.empty();
    }

    int size() const {
        return heap.size();
    }
};

#endif // MAX_HEAP_H