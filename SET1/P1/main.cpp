#include <iostream>
#include <stdexcept>
// #include "list.h"

// List::List() 
// : _size(0)
// , head()
// , tail()
// {}

// List::List(const List& other) 
// : _size(other._size)
// {
//     head = new Node(other.head->value);
//     Node* current = head;
    
//     Node* tmp = other.head->next;
//     while (tmp) {
//         Node* newNode = new Node(current, nullptr, tmp->value);
//         current->next = newNode;
//         current = newNode;
//         tmp = tmp->next;
//     }

//     tail = current;
// }

// List::List(std::vector<int> array) 
// : _size(array.size())
// , head(nullptr)
// , tail(nullptr)
// {
//     if (_size == 0) return;
    
//     head = new Node(array[0]);
//     Node* current = head;

//     for (size_t i = 1; i < _size; ++i) {
//         Node* newNode = new Node(current, nullptr, array[i]);
//         current->next = newNode;
//         current = newNode;
//     }

//     tail = current;
// }

// List::~List() {
//     Node* current = head;
//     while (current) {
//       Node* tmp = current;
//       current = current->next;
//       delete tmp;  
//     }
// }

// int List::front() {
//     return head->value;
// }


// int List::back() {
//     return tail->value;
// }

// void List::push_back(int value) {
//     Node* pb = new Node(tail, nullptr, value);
//     tail->next = pb;
//     tail = pb;
// }

// void List::push_front(int value) {
//     Node* pf = new Node(nullptr, head, value);
//     head->prev = pf;
//     head = pf;
// }

// void List::insert(Node* pos, int value) {
//     if (!pos) {
//         std::runtime_error("Incorrect position!");
//     }
//     Node* tmp = head;
//     while (tmp) {
//         if(tmp == pos) {
//             Node* ins = new Node(pos, pos->next, value);
//             pos->next = ins;
//             ins->next->prev = ins;
//             return;
//         }
//         tmp = tmp->next;
//     }
//     std::runtime_error("Incorrect position!");
// }

// void List::pop_front() {
//     if (!head->next) {
//         std::runtime_error("Deleting in empty list");
//     }
//     Node* tmp = head;
//     head = head->next;
//     head->prev = nullptr;
//     delete tmp;
// }

// void List::pop_back() {
//     if (!tail->prev) {
//         std::runtime_error("Deleting in empty list");
//     }
//     Node* tmp = tail;
//     tail = tail->prev;
//     tail->next = nullptr;
//     delete tmp;
// }

// void List::erase(Node* pos) {
//     if (!pos) {
//         std::runtime_error("Incorrect position!");
//     }
//     pos->prev->next = pos->next;
//     pos->next->prev = pos->prev;
//     delete pos;
// }

// void List::clear() {
//     Node* current = head;
//     while (current) {
//       Node* tmp = current;
//       current = current->next;
//       delete tmp;  
//     }
//     delete head;
//     delete tail;
//     _size = 0;
// }

// void List::reverse() {
//     Node* current = tail;
//     Node* tmp = head;
//     head = tail;
//     tail = tmp;
//     while (current) {
//         tmp = current;
//         current->next = tmp->prev;
//         current->prev = tmp->next;
//         current = current->next;
//     }
// }

// void List::remove_duplicates() {
//     throw std::runtime_error("Not implemented!");
// }

// void List::replace(int old_value, int new_value) {
//     throw std::runtime_error("Not implemented!");
// }

// void List::merge(const List& other) {
//     throw std::runtime_error("Not implemented!");
// }

// bool List::check_cycle() const {
//     throw std::runtime_error("Not implemented!");
// }

// size_t List::size() const {
//     throw std::runtime_error("Not implemented!");
// }

// bool List::empty() const{
//     throw std::runtime_error("Not implemented!");
// }

// void List::copy(const List& other) {
//     throw std::runtime_error("Not implemented!");
// }


int mod(int dividend, int divisor) {
    // Убедимся, что делитель не равен нулю
    if (divisor == 0) {
        throw std::invalid_argument("Division by zero is undefined.");
    }

    // Начнем с прямого вычитания или прибавления в зависимости от знака делителя
    if (dividend > 0 && divisor > 0) {
        // Оба положительные
        while (dividend >= divisor) {
            dividend -= divisor;
        }
    } else if (dividend < 0 && divisor < 0) {
        // Оба отрицательные
        while (dividend <= divisor) {
            dividend -= divisor;
        }
    } else if (dividend > 0 && divisor < 0) {
        // Делимое положительное, делитель отрицательный
        while (dividend >= -divisor) {
            dividend += divisor; // Прибавляем, так как делитель отрицательный
        }
    } else {
        // Делимое отрицательное, делитель положительный
        while (dividend <= -divisor) {
            dividend += divisor; // Прибавляем делитель, чтобы приближать к нулю
        }
    }

    return dividend;
}

int main() {
    std::cout << 18 / -7 << " " << 18 % -7;

    return 0;
}