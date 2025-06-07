#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include "list.h"

List::List()
: _size(0)
, head(nullptr)
, tail(nullptr)
{}

List::List(const List& other)
: _size(other._size)
, head(nullptr)
, tail(nullptr)
{
    if (!_size) {
        return;
    }

    head = new Node(*other.head);
    Node* current = head;
    Node* tmp = other.head->next;

    while (tmp) {
        Node* newNode = new Node(current, nullptr, tmp->value);
        current->next = newNode;
        current = newNode;
        tmp = tmp->next;
    }

    tail = current;
}

List::List(std::vector<int> array)
: _size(array.size())
, head(nullptr)
, tail(nullptr)
{
    if (_size == 0) {
        return;
    }

    head = new Node(array[0]);
    Node* current = head;

    for (size_t i = 1; i < _size; ++i) {
        Node* newNode = new Node(current, nullptr, array[i]);
        current->next = newNode;
        current = newNode;
    }

    tail = current;
}

List::~List() {
    clear();
}

int List::front() {
    return head->value;
}

int List::back() {
    return tail->value;
}

void List::push_back(int value) {
    Node* pb = new Node(tail, nullptr, value);

    if (tail != nullptr) {
        tail->next = pb;
    } else {
        head = pb;
    }

    tail = pb;
    _size++;
}


void List::push_front(int value) {
    Node* pf = new Node(nullptr, head, value);

    if (head != nullptr) {
        head->prev = pf;
    } else {
        tail = pf;
    }

    head = pf;
    _size++;
}


void List::insert(Node* pos, int value) {
    if (!pos) {
        throw std::runtime_error("Incorrect position!");
    }
    Node* current = head;
    while (current) {
        if(current == pos) {
            Node* ins = new Node(pos, pos->next, value);
            pos->next = ins;
            ins->next->prev = ins;
            _size++;
            return;
        }
        current = current->next;
    }
    throw std::runtime_error("Incorrect position!");
}

void List::pop_front() {
    if (!head) {
        throw std::runtime_error("Deleting in empty list");
    }
    if (head->next) {
        Node* tmp = head;
        head = head->next;
        head->prev = nullptr;
        delete tmp;
    } else {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    _size--;
}

void List::pop_back() {
    if (!tail) {
        throw std::runtime_error("Deleting in empty list");
    }
    if (tail->prev) {
        Node* tmp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete tmp;
    } else {
        delete tail;
        head = nullptr;
        tail = nullptr;
    }
    _size--;
}

void List::erase(Node* pos) {
    if (pos == nullptr) {
        throw std::runtime_error("Incorrect position!");
    }
    Node *current = head;
    while (current != nullptr)
    {
        if (current == pos)
        {
            if (pos->prev == nullptr) {
                pop_front();
                return;
            }
            if (pos->next == nullptr) {
                pop_back();
                return;
            }
            pos->prev->next = pos->next;
            pos->next->prev = pos->prev;
            delete pos;
            _size--;
            return;
        }
        current = current->next;
    }
    throw std::runtime_error("Incorrect position!");
}

void List::clear() {
    Node* slow = head;
    Node* fast = head;
    bool hasCycle = false;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            hasCycle = true;
            break;
        }
    }

    if (hasCycle) {
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        Node* cycleStart = slow;
        Node* prev = nullptr;
        do {
            prev = fast;
            fast = fast->next;
        } while (fast != cycleStart);

        prev->next = nullptr;
    }

    Node* current = head;
    while (current) {
        Node* tmp = current;
        current = current->next;
        delete tmp;
    }
    
    head = nullptr;
    tail = nullptr;
    _size = 0;
}

void List::reverse() {
    Node* current = tail;
    Node* tmp = head;
    head = tail;
    tail = tmp;
    while (current) {
        tmp = current;
        current->next = tmp->prev;
        current->prev = tmp->next;
        current = current->next;
    }
}

void List::remove_duplicates() {
    std::unordered_set<int> uniq;
    Node* current = head;
    while (current) {
        if (uniq.find(current->value) != uniq.end()) {
            Node* tmp = current;
            current = current->next;
            erase(tmp);
            continue;
        }
        uniq.insert(current->value);
        current = current->next;
    }
}

void List::replace(int old_value, int new_value) {
    Node* current = head;
    while (current) {
        if (current->value == old_value) {
            current->value = new_value;
        }
        current = current->next;
    }
}

void List::merge(const List& other) {
    Node* current = tail;
    Node* curCppy = other.head;
    while (curCppy) {
        Node* new_node = new Node(current, nullptr, curCppy->value);
        current->next = new_node;
        current = new_node;
        curCppy = curCppy->next;
    }
    tail = current;
    _size += other._size;
}

bool List::check_cycle() const {
    Node* current = head;
    Node* prev = current->prev;
    while (current) {
        if (current->prev != prev) {
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

size_t List::size() const {
    return _size;
}

bool List::empty() const{
    return !_size;
}

void List::copy(const List& other) {
    clear();
    _size = other._size;
    if (!_size) {
        return;
    }

    head = new Node(*other.head);
    Node* current = head;
    Node* tmp = other.head->next;

    while (tmp) {
        Node* newNode = new Node(current, nullptr, tmp->value);
        current->next = newNode;
        current = newNode;
        tmp = tmp->next;
    }

    tail = current;

}

// int main() {
//     std::vector<int> v = {1, 2, 3};
//     std::vector<int> v1 = {};
//     List a = List(v);
//     List b = List(v1);
//     a.copy(b);
//     for (auto it = a.head; it != nullptr; it = it->next) {
//         std::cout << it->value << " ";
//     }
//     std::cout << "\n" << a.size();
// }        