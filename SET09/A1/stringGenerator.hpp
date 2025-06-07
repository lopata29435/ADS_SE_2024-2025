#ifndef STRING_GENERATOR_HPP
#define STRING_GENERATOR_HPP

#include <vector>
#include <string>
#include <random>
#include <algorithm>

static const std::string SG_ALPHABET =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789"
    "!@#%:;^&*()-.";

class StringGenerator {
public:
    explicit StringGenerator(unsigned seed = std::random_device{}())
        : rnd_(seed), minLen_(10), maxLen_(200),
          nMax_(0), nearlySwaps_(100) {}

    void generateBase(int nMax, int minLen = 10, int maxLen = 200) {
        nMax_ = nMax;
        minLen_ = minLen;
        maxLen_ = maxLen;
        base_.clear();
        base_.reserve(nMax_);
        std::uniform_int_distribution<int> lenDist(minLen_, maxLen_);
        for (int i = 0; i < nMax_; ++i) {
            int L = lenDist(rnd_);
            std::string s;
            s.reserve(L);
            std::uniform_int_distribution<int> charDist(0, (int)SG_ALPHABET.size() - 1);
            for (int j = 0; j < L; ++j) {
                s.push_back(SG_ALPHABET[charDist(rnd_)]);
            }
            base_.push_back(std::move(s));
        }
    }

    void setNearlySortedSwaps(int swapsCount) {
        nearlySwaps_ = swapsCount;
    }

    // type=0 — случайные
    // type=1 — обратно отсортированные,
    // type=2 — почти отсортированные
    std::vector<std::string> get(int n, int type) const {
        std::vector<std::string> v(base_.begin(), base_.begin() + n);
        if (type == 1) {
            std::sort(v.begin(), v.end());
            std::reverse(v.begin(), v.end());
        } else if (type == 2) {
            std::sort(v.begin(), v.end());
            std::uniform_int_distribution<int> dist(0, n - 1);
            for (int k = 0; k < nearlySwaps_; ++k) {
                int i = dist(rnd_), j = dist(rnd_);
                std::swap(v[i], v[j]);
            }
        }
        return v;
    }

private:
    std::vector<std::string> base_;
    mutable std::mt19937      rnd_;
    int                       minLen_, maxLen_;
    int                       nMax_;
    int                       nearlySwaps_;
};

#endif // STRING_GENERATOR_HPP