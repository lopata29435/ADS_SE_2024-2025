#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

bool compareFractions(pair<int, int>& frac1, pair<int, int>& frac2) {
    return frac1.first * frac2.second <= frac2.first * frac1.second;
}

void merge(vector<pair<int, int>>& fractions, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<pair<int, int>> leftFractions(n1);
    vector<pair<int, int>> rightFractions(n2);

    for (int i = 0; i < n1; i++) leftFractions[i] = fractions[left + i];
    for (int i = 0; i < n2; i++) rightFractions[i] = fractions[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compareFractions(leftFractions[i], rightFractions[j])) {
            fractions[k++] = leftFractions[i++];
        } else {
            fractions[k++] = rightFractions[j++];
        }
    }

    while (i < n1) fractions[k++] = leftFractions[i++];
    while (j < n2) fractions[k++] = rightFractions[j++];
}

void mergeSort(vector<pair<int, int>>& fractions, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(fractions, left, mid);
        mergeSort(fractions, mid + 1, right);

        merge(fractions, left, mid, right);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int, int>> fractions(n);
    char c;
    for (int i = 0; i < n; ++i) {
        cin >> fractions[i].first >> c >> fractions[i].second;
    
    }

    mergeSort(fractions, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << fractions[i].first << "/" << fractions[i].second;
        if (i != n - 1) cout << " ";
    }

    return 0;
}
