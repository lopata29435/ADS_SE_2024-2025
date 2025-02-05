#include "bloom_filter.h"

BloomFilter::BloomFilter(size_t hashes, size_t bits)
    : _hashes(hashes), _bits(bits), _filter(bits, false) {}

void BloomFilter::add(const std::string& str) {
    _raw_set.insert(str);
    for (size_t i = 0; i < _hashes; ++i) {
        std::string temp = str + std::to_string(i);
        size_t index = hasher(temp) % _bits;
        _filter[index] = true;
    }
}

bool BloomFilter::verify(const std::string& str) {
    ++cnt;
    for (size_t i = 0; i < _hashes; ++i) {
        std::string temp = str + std::to_string(i);
        size_t index = hasher(temp) % _bits;
        if (!_filter[index])
            return false;
    }
    if (!_raw_set.contains(str))
        ++false_positive_cnt;
    return true;
}

double BloomFilter::getFPRate() const {
    if (cnt == 0) {
        return 0;
    }
    return static_cast<double>(false_positive_cnt) / static_cast<double>(cnt);
}

size_t BloomFilter::numberOfHashFunctions() const {
    return _hashes;
}

size_t BloomFilter::numberOfBits() const {
    return _bits;
}