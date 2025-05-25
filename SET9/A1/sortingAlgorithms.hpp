#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cstdint>

extern uint64_t GLOBAL_CHAR_COMPARISONS;

inline bool char_eq(char a, char b) {
    ++GLOBAL_CHAR_COMPARISONS;  // посимвольное сравнение
    return a == b;
}

inline bool char_lt(char a, char b) {
    ++GLOBAL_CHAR_COMPARISONS;  // посимвольное сравнение
    return a < b;
}

inline bool char_gt(char a, char b) {
    ++GLOBAL_CHAR_COMPARISONS;  // посимвольное сравнение
    return a > b;
}

// -----------------------------------------------------------------------------
// 1) STRING MERGESORT на основе LCP
inline int lcp(const std::string& a, const std::string& b) {
    int len = std::min(a.size(), b.size());
    for (int i = 0; i < len; ++i) {
        if (!char_eq(a[i], b[i]))  // посимвольное сравнение
            return i;
    }
    return len;
}

inline bool lcpCompare(const std::string& a, const std::string& b) {
    int la = lcp(a, b);
    int lb = lcp(b, a);
    if (la != lb) 
        return la > lb;
    for (size_t i = 0; i < std::min(a.size(), b.size()); ++i) {
        if (!char_eq(a[i], b[i]))  // посимвольное сравнение
            return char_lt(a[i], b[i]);  // посимвольное сравнение
    }
    return a.size() < b.size();
}

inline void mergeLCP(std::vector<std::string>& arr,
                     int left, int mid, int right)
{
    std::vector<std::string> L(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<std::string> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < (int)L.size() && j < (int)R.size()) {
        if (lcpCompare(L[i], R[j]))  // посимвольные сравнения внутри lcpCompare
            arr[k++] = std::move(L[i++]);
        else
            arr[k++] = std::move(R[j++]);
    }
    while (i < (int)L.size()) arr[k++] = std::move(L[i++]);
    while (j < (int)R.size()) arr[k++] = std::move(R[j++]);
}

inline void mergeSortLCPRec(std::vector<std::string>& arr,
                            int left, int right)
{
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortLCPRec(arr, left, mid);
    mergeSortLCPRec(arr, mid + 1, right);
    mergeLCP(arr, left, mid, right);
}

inline void alg_string_mergesort_lcp(std::vector<std::string>& v) {
    GLOBAL_CHAR_COMPARISONS = 0;  // обнуляем счетчик в начале
    if (!v.empty())
        mergeSortLCPRec(v, 0, int(v.size()) - 1);
}

// -----------------------------------------------------------------------------
// 2) 3-way (MSD) STRING QUICKSORT

inline int charAt(const std::string& s, int d) {
    ++GLOBAL_CHAR_COMPARISONS;  // подсчет доступа к символу
    return d < (int)s.size() ? (unsigned char)s[d] : -1;
}

inline void quick3Rec(std::vector<std::string>& a,
                      int lo, int hi, int d)
{
    if (lo >= hi) return;
    int lt = lo, gt = hi;
    int pivot = charAt(a[lo], d);
    int i = lo + 1;
    while (i <= gt) {
        int c = charAt(a[i], d);
        if (c < pivot) {
            ++GLOBAL_CHAR_COMPARISONS;  // сравнение символов
            std::swap(a[lt++], a[i++]);
        }
        else if (c > pivot) {
            ++GLOBAL_CHAR_COMPARISONS;  // сравнение символов
            std::swap(a[i], a[gt--]);
        }
        else {
            ++GLOBAL_CHAR_COMPARISONS;  // сравнение символов
            ++i;
        }
    }
    quick3Rec(a, lo,    lt - 1, d);
    if (pivot >= 0) quick3Rec(a, lt,    gt,     d + 1);
                   quick3Rec(a, gt + 1, hi,     d);
}

inline void alg_string_quick3way(std::vector<std::string>& v) {
    GLOBAL_CHAR_COMPARISONS = 0;  // обнуляем счетчик в начале
    if (!v.empty())
        quick3Rec(v, 0, int(v.size()) - 1, 0);
}

// -----------------------------------------------------------------------------
// 3) MSD RADIX SORT

inline int charCode(const std::string& s, int d) {
    ++GLOBAL_CHAR_COMPARISONS;  // подсчет доступа к символу
    return d < (int)s.size() ? (unsigned char)s[d] + 1 : 0;
}

inline void msdRadixRec(std::vector<std::string>& a,
                        int lo, int hi, int d,
                        std::vector<std::string>& aux)
{
    if (lo >= hi) return;
    const int R = 256;
    std::vector<int> count(R + 2, 0);

    for (int i = lo; i <= hi; ++i) {
        int c = charCode(a[i], d);  // подсчет доступа к символу
        ++count[c + 1];
    }
    for (int r = 0; r <= R; ++r)
        count[r + 1] += count[r];
    for (int i = lo; i <= hi; ++i) {
        int c = charCode(a[i], d);  // подсчет доступа к символу
        aux[count[c]++] = std::move(a[i]);
    }
    for (int i = lo; i <= hi; ++i)
        a[i] = std::move(aux[i - lo]);
    for (int r = 0; r <= R; ++r) {
        int start = lo + (r == 0 ? 0 : count[r - 1]);
        int end   = lo + count[r] - 1;
        if (start <= end)
            msdRadixRec(a, start, end, d + 1, aux);
    }
}

inline void alg_msd_radix(std::vector<std::string>& v) {
    GLOBAL_CHAR_COMPARISONS = 0;  // обнуляем счетчик в начале
    if (v.empty()) return;
    std::vector<std::string> aux(v.size());
    msdRadixRec(v, 0, int(v.size()) - 1, 0, aux);
}

// -----------------------------------------------------------------------------
// 4) MSD RADIX SORT with threshold → 3-way quicksort

inline void msdRadixSwitchRec(std::vector<std::string>& a,
                              int lo, int hi, int d,
                              std::vector<std::string>& aux)
{
    const int R = 256;
    constexpr int THRESH = 74;
    int len = hi - lo + 1;
    if (len < THRESH) {
        quick3Rec(a, lo, hi, d);
        return;
    }
    std::vector<int> count(R + 2, 0);
    for (int i = lo; i <= hi; ++i) {
        int c = charCode(a[i], d);  // подсчет доступа к символу
        ++count[c + 1];
    }
    for (int r = 0; r <= R; ++r)
        count[r + 1] += count[r];
    for (int i = lo; i <= hi; ++i) {
        int c = charCode(a[i], d);  // подсчет доступа к символу
        aux[count[c]++] = std::move(a[i]);
    }
    for (int i = lo; i <= hi; ++i)
        a[i] = std::move(aux[i - lo]);
    for (int r = 0; r <= R; ++r) {
        int start = lo + (r == 0 ? 0 : count[r - 1]);
        int end   = lo + count[r] - 1;
        if (start <= end)
            msdRadixSwitchRec(a, start, end, d + 1, aux);
    }
}

inline void alg_msd_radix_switch(std::vector<std::string>& v) {
    GLOBAL_CHAR_COMPARISONS = 0;  // обнуляем счетчик в начале
    if (v.empty()) return;
    std::vector<std::string> aux(v.size());
    msdRadixSwitchRec(v, 0, int(v.size()) - 1, 0, aux);
}

#endif // SORTING_ALGORITHMS_HPP
