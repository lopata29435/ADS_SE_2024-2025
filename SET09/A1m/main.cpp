#include <bits/stdc++.h>
using namespace std;

int lcp(const string& a, const string& b) {
    int len = min(a.size(), b.size());
    for (int i = 0; i < len; ++i)
        if (a[i] != b[i])
            return i;
    return len;
}

bool lcpCompare(const string& a, const string& b) {
    int l = lcp(a, b);
    int r = lcp(b, a);
    if (l != r)
        return l > r;
    return a < b;
}

void merge(vector<string>& arr, int left, int mid, int right) {
    vector<string> L(arr.begin()+left, arr.begin()+mid+1);
    vector<string> R(arr.begin()+mid+1, arr.begin()+right+1);

    int i = 0, j = 0, k = left;
    while (i < (int)L.size() && j < (int)R.size()) {
        if (lcpCompare(L[i], R[j]))
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < (int)L.size()) arr[k++] = L[i++];
    while (j < (int)R.size()) arr[k++] = R[j++];
}

void mergeSort(vector<string>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> arr(n);
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    mergeSort(arr, 0, n-1);

    for (auto& s : arr)
        cout << s << "\n";

    return 0;
}
