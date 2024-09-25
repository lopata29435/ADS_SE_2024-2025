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
    Node* tmp = head;
    while (tmp) {
        if(tmp == pos) {
            Node* ins = new Node(pos, pos->next, value);
            pos->next = ins;
            ins->next->prev = ins;
            _size++;
            return;
        }
        tmp = tmp->next;
    }
    throw std::runtime_error("Incorrect position!");
}

void List::pop_front() {
    if (!head->next) {
        throw std::runtime_error("Incorrect position!");
    }
    Node* tmp = head;
    head = head->next;
    head->prev = nullptr;
    _size--;
    delete tmp;
}

void List::pop_back() {
    if (!tail->prev) {
        throw std::runtime_error("Incorrect position!");
    }
    Node* tmp = tail;
    tail = tail->prev;
    tail->next = nullptr;
    _size--;
    delete tmp;
}

void List::erase(Node* pos) {
    if (!pos) {
        throw std::runtime_error("Incorrect position!");
    }
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
    _size--;
    delete pos;
}

void List::clear() {
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
            _size--;
            continue;
        }
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
    return _size;
}

void List::copy(const List& other) {
    Node* current = head;
    Node* curCppy = other.head;

    while (curCppy && current) {
        current->value = curCppy->value;
        current = current->next;
        curCppy = curCppy->next;
    }
    
    if (curCppy || current) {
        return;
    }

    if (!curCppy) {
        tail = current->prev;
        _size = other._size;
        while (current) {
            Node* tmp = current;
            current = current->next;
            delete tmp;
        }
    }

    if (!current) {
        current = current->prev;
        while (curCppy) {
            Node* new_node = new Node(current, nullptr, curCppy->value);
            current->next = new_node;
            current = new_node;
            curCppy = curCppy->next;
            _size++;
        }
    }
}
