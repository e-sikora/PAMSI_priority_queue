#pragma once
#include <iostream>

template<typename T>
class PriorityQueue { // Class representing a priority queue
    struct Node { // Structure representing a node
        unsigned int Priority; // Priority
        T Word; // Element (word)
        Node* Next; // Pointer to the next node
        Node* Previous; // Pointer to the previous node
        
        Node(unsigned int priority, T word, Node* next, Node* previous) { // Node constructor
            Priority = priority; 
            Word = word;
            Next = next;
            Previous = previous;
        }
        
        ~Node() { // Node destructor
            if (Next != nullptr)
                delete Next;
        }
    };
    unsigned int Size; // Size of the queue (number of elements)
    Node* Head; // First node
    Node* Tail; // Last node

public:
    unsigned int getSize() const { // Method returning the current size of the queue
        return Size;
    }
 
    bool isEmpty() const { // Method checking if the queue is empty
        return Head == nullptr;
    }

    PriorityQueue() { // Queue constructor
        Head = nullptr;
        Tail = nullptr;
        Size = 0;
    }

    void PushFront(unsigned int, T); // Renamed method to start with a capital letter
    void PushSort(unsigned int, T); // Renamed method to start with a capital letter
    PriorityQueue<T> RandomPop(); // Renamed method to start with a capital letter
    PriorityQueue<T> Pop(); // Renamed method to start with a capital letter
    void Display() const; // Renamed method to start with a capital letter
};

template<typename T>
void PriorityQueue<T>::PushFront(unsigned int priority, T word) { // Method copying a node from one list to another list without considering priorities
    Node* added = new Node(priority, word, nullptr, nullptr);

    if (isEmpty()) { // If the list we are inserting into is empty, the added element becomes the first and last element of the list
        Head = added;
        Tail = added;
    } else {
        added->Next = Head;
        Head->Previous = added;
        Head = added;
    }
    Size++; 
}

template<typename T>
void PriorityQueue<T>::PushSort(unsigned int priority, T word) { // Method copying a node from one list to another list in priority order
    Node* newNode = new Node(priority, word, nullptr, nullptr);

    if (isEmpty()) { // If the list we are inserting into is empty, the added element becomes the first and last element of the list
        Head = newNode;
        Tail = newNode;
    } else if (priority < Head->Priority) { // If the priority of the new element is higher than the one at the first position (by higher we mean closer to 1), insert it before the element
        newNode->Next = Head;
        Head->Previous = newNode;
        Head = newNode;
    } else { // If the priority of the new element is lower than the one at the first position, the loop runs until a lower priority is found
        Node* current = Head;
        while (current->Next != nullptr && current->Next->Priority <= priority) {
            current = current->Next;
        }
        newNode->Next = current->Next;
        newNode->Previous = current;
        if (current->Next != nullptr) {
            current->Next->Previous = newNode;
        } else { // If no lower priority is found, the new element becomes the "tail"
            Tail = newNode;
        }
        current->Next = newNode;
    }

    Size++;
}

template<typename T>
PriorityQueue<T> PriorityQueue<T>::RandomPop() { // Method to randomize the queue (selects a random node, copies it to a new list, and removes it from the original)
    PriorityQueue<T> randomized;
    Node* helper = nullptr;
    unsigned int size = Size;

    if (isEmpty()) { // Check if the queue from which we are to remove a node is empty
        throw std::runtime_error("Nie usunąć elementu - kolejka pusta!");
    }

    while (size > 1) {
        helper = Head;
        srand(time(NULL)); // Randomly selects the node to be retrieved and removed
        int min = 0;
        int max = size - 1;
        int randomPosition = rand() % (max - min + 1) + min;

        for (int i = 0; i < randomPosition; i++)
            helper = helper->Next;

        randomized.PushFront(helper->Priority, helper->Word);

        if (helper == Head) { // Implement removal of the copied elements
            Head = helper->Next;
            Head->Previous = nullptr;
        } else if (helper == Tail) {
            Tail = helper->Previous;
            Tail->Next = nullptr;
        } else {
            helper->Previous->Next = helper->Next;
            helper->Next->Previous = helper->Previous;
        }

        helper->Next = nullptr;
        helper->Previous = nullptr;
        delete helper;
        size--;

        if (size == 1) { // Copy the last element of the list
            randomized.PushFront(Head->Priority, Head->Word);
            Head = nullptr;
            Tail = nullptr;
        }
    }
    return randomized;
}


template<typename T>
PriorityQueue<T> PriorityQueue<T>::Pop() { // Method to sequentially retrieve elements from the queue and copy them to another queue in the appropriate order
    PriorityQueue<T> randomized;
    Node* helper = nullptr;
    unsigned int size = Size;

    if (isEmpty()) { // Check if the queue from which we are to remove a node is empty
        throw std::runtime_error("Nie usunąć elementu - kolejka pusta!");
    }

    while (size > 1) {
        helper = Head;

        randomized.PushSort(helper->Priority, helper->Word);

        Head = helper->Next;
        Head->Previous = nullptr;

        helper->Next = nullptr;
        helper->Previous = nullptr;
        delete helper;
        size--;

        if (size == 1) { // Copy the last element of the list
            randomized.PushSort(Head->Priority, Head->Word);
            Head = nullptr;
            Tail = nullptr;
        }
    }
    return randomized;
}

template<typename T>
void PriorityQueue<T>::Display() const { // Method to display all elements of the queue
    Node* tmp = Head;

    while (tmp != nullptr) {
        std::cout << tmp->Word << " ";
        tmp = tmp->Next;
    }
    std::cout << std::endl;
}
