#include <cstdint>
#include <stdexcept>

template <class KeyType, class ValueType>
struct Node {
    KeyType key;
    ValueType value;
    Node* next;

    Node(KeyType k, ValueType v) : key(k), value(v), next(nullptr) {}
};

// Хеш-таблица
template <class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
public:
    HashTable() : d_(0.5), capacity_(100), size_(0) {
        table_ = new Node<KeyType, ValueType>*[capacity_]();
    }

    HashTable(Func func) : d_(0.5), capacity_(100), size_(0), hash_f_(func) {
        table_ = new Node<KeyType, ValueType>*[capacity_]();
    }

    HashTable(size_t capacity, double coeff, Func func = std::hash<KeyType>())
        : hash_f_(func), capacity_(capacity > 0 ? capacity : 100), d_(coeff > 0 && coeff <= 1 ? coeff : 0.5), size_(0) {
        table_ = new Node<KeyType, ValueType>*[capacity_]();
    }

    ~HashTable() {
        clear();
        delete[] table_;
    }

    void insert(KeyType key, ValueType value) {
        if (static_cast<double>(size_ + 1) / capacity_ > d_) {
            rehash();
        }

        size_t index = hash_f_(key) % capacity_;
        Node<KeyType, ValueType>* current = table_[index];

        // Поиск существующего элемента с таким ключом
        while (current) {
            if (current->key == key) {
                current->value = value;  // Обновление значения
                return;
            }
            current = current->next;
        }

        // Добавление нового элемента
        Node<KeyType, ValueType>* newNode = new Node<KeyType, ValueType>(key, value);
        newNode->next = table_[index];
        table_[index] = newNode;
        ++size_;
    }

    ValueType* find(KeyType key) {
        size_t index = hash_f_(key) % capacity_;
        Node<KeyType, ValueType>* current = table_[index];
        while (current) {
            if (current->key == key) {
                return &current->value;
            }
            current = current->next;
        }
        return nullptr;
    }

    void erase(KeyType key) {
        size_t index = hash_f_(key) % capacity_;
        Node<KeyType, ValueType>* current = table_[index];
        Node<KeyType, ValueType>* prev = nullptr;

        while (current) {
            if (current->key == key) {
                if (prev) {
                    prev->next = current->next;  // Удаление из цепочки
                } else {
                    table_[index] = current->next;  // Удаление первого элемента
                }
                delete current;
                --size_;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    Node<KeyType, ValueType>& operator[](uint64_t hash_code) {
        if (hash_code >= capacity_) {
            throw std::out_of_range("Hash code out of range");
        }
        if (!table_[hash_code]) {
            throw std::runtime_error("Empty bucket");
        }
        return *table_[hash_code];
    }

    Node<KeyType, ValueType> at(uint64_t hash_code) const {
        if (hash_code >= capacity_) {
            throw std::out_of_range("Hash code out of range");
        }
        if (!table_[hash_code]) {
            throw std::runtime_error("Empty bucket");
        }
        return *table_[hash_code];
    }

    int size() const { return static_cast<int>(size_); }
    int capacity() const { return static_cast<int>(capacity_); }

private:
    double d_;
    size_t capacity_;
    size_t size_;
    Func hash_f_;
    Node<KeyType, ValueType>** table_;

    void rehash() {
        size_t new_capacity = capacity_ * 2;
        Node<KeyType, ValueType>** new_table = new Node<KeyType, ValueType>*[new_capacity]();

        // Перехеширование элементов в новый массив
        for (size_t i = 0; i < capacity_; ++i) {
            Node<KeyType, ValueType>* current = table_[i];
            while (current) {
                Node<KeyType, ValueType>* next = current->next;
                size_t new_index = hash_f_(current->key) % new_capacity;
                current->next = new_table[new_index];
                new_table[new_index] = current;
                current = next;
            }
        }

        // Освобождение старой таблицы
        delete[] table_;
        table_ = new_table;
        capacity_ = new_capacity;
    }

    void clear() {
        // Очистка таблицы
        for (size_t i = 0; i < capacity_; ++i) {
            Node<KeyType, ValueType>* current = table_[i];
            while (current) {
                Node<KeyType, ValueType>* next = current->next;
                delete current;
                current = next;
            }
        }
    }
};