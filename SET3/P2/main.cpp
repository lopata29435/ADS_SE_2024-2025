#include <iostream>
#include <vector>

using namespace std;

vector<int>& countingSort(vector<int>& A) {
    int offset = 1000000;
    vector<int> C(2000001, 0);

    for (size_t i = 0; i < A.size(); ++i) {
        C[A[i] + offset]++;
    }

    size_t cur = 0;
    for (int i = 0; i < 2000001; ++i) {
        while (C[i] > 0) {
            A[cur] = i - offset;
            cur++;
            C[i]--;
        }
        if (cur == A.size()) {
            break;
        }
    }

    return A;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    a = countingSort(a);

    for (int i = 0; i < n; ++i) {
        cout << a[i] << ' ';
    }
    return 0;
}
