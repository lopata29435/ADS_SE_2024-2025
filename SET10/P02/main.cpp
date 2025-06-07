#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, l, r;
    cin >> n >> l >> r;

    vector<int> result(n);
    int nextValue = 1;
    int left = 0;
    int right = n - 1;

    if ((l - 1) > (n - r)) {
        int count = (l - 1) - (n - r);
        for (int i = 0; i < count; ++i)
            result[left++] = nextValue++;
    } else if ((l - 1) < (n - r)) {
        int count = (n - r) - (l - 1);
        for (int i = 0; i < count; ++i)
            result[right--] = nextValue++;
    }

    while (left < right) {
        result[left++] = nextValue++;
        result[right--] = nextValue++;
    }

    if (left == right) {
        result[left] = nextValue++;
    }

    for (int x : result)
        cout << x << ' ';
    cout << '\n';

    return 0;
}
