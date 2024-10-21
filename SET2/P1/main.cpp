#include <iostream>
#include <vector>

struct Interval {
    int left;
    int right;

    size_t length() {
        return std::max(0, right - left + 1);
    }

    Interval overlap(const Interval& other) {
        return {std::max(left, other.left), std::min(right, other.right)};
    }

    bool operator==(const Interval& other) const {
        return left == other.left && right == other.right;
    }

    bool operator< (const Interval &other) const {
        if (left == other.left) {
            return right < other.right;
        }
        return left < other.left;
    }

    bool operator<=(const Interval& other) const {
        return (*this < other) || (*this == other);
    }
};

void MyMerge(std::vector<Interval> &v, int left, int mid, int right) {
    std::vector<Interval> tmp(right - left + 1);
    int l = left;
    int r = mid + 1;
    int i = 0;

    while (l <= mid && r <= right) {
        if (v[l] < v[r]) {
            tmp[i++] = v[l++];
        } else {
            tmp[i++] = v[r++];
        }
    }

    while (l <= mid) {
        tmp[i++] = v[l++];
    }

    while (r <= right) {
        tmp[i++] = v[r++];
    }

    for (int j = 0; j < tmp.size(); j++) {
        v[left + j] = tmp[j];
    }
}

void MyMergeSort(std::vector<Interval> &v, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        MyMergeSort(v, left, mid);
        MyMergeSort(v, mid + 1, right);
        MyMerge(v, left, mid, right);
    }
}

int main() {
    int n, l, r;
    std::cin >> n;
    std::vector<Interval> a;
    for (int i = 0; i < n; ++i) {
        std::cin >> l >> r;
        a.push_back(Interval(l, r));
    }

    MyMergeSort(a, 0, n - 1);

    int cur = 0;
    int ans = 0;
    Interval tmp;
    Interval ansI;
    for (int i = 1; i < n; i++) {
        tmp = a[cur].overlap(a[i]);
        if (ans < tmp.length()) {
            ans = tmp.length();
            ansI = tmp;
        }
        if (a[cur].right < a[i].right) {
            cur = i;
        }
    }
    

    std::cout << ans << '\n';
    if(ans) {
        std::cout << ansI.left << ' ' << ansI.right << '\n';
    }

    return 0;
}

