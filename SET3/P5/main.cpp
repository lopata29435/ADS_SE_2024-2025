#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <bitset>
#include <random>

using namespace std;

vector<vector<uint8_t>> hexToBinaryMatrix(const vector<string>& hexRow, int n) {
    vector<vector<uint8_t>> matrix(n, vector<uint8_t>(n, 0));
    for (int row = 0; row < n; ++row) {
        string binaryString = "";
        for (char hexChar : hexRow[row]) {
            uint8_t value = (hexChar >= '0' && hexChar <= '9') ? (hexChar - '0') : (hexChar - 'A' + 10);
            binaryString += bitset<4>(value).to_string();
        }
        for (int col = 0; col < n && col < binaryString.size(); ++col) {
            matrix[row][col] = binaryString[col] - '0';
        }
    }
    return matrix;
}


vector<uint8_t> multiplyMatrixVector(const vector<vector<uint8_t>>& A, const vector<uint8_t>& r, int n) {
    vector<uint8_t> result(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i] ^= (A[i][j] & r[j]);
        }
    }
    return result;
}

vector<uint8_t> generateRandomBinaryVector(int n) {
    vector<uint8_t> r(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 1);
    for (int i = 0; i < n; ++i) {
        r[i] = dist(gen);
    }
    return r;
}

bool areVectorsEqual(const vector<uint8_t>& v1, const vector<uint8_t>& v2) {
    for(int i = 0; i < v1.size(); ++i) {
        if(v1[i] != v2[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> hexA(n), hexB(n), hexC(n);
    for (int i = 0; i < n; ++i) cin >> hexA[i];
    for (int i = 0; i < n; ++i) cin >> hexB[i];
    for (int i = 0; i < n; ++i) cin >> hexC[i];

    vector<vector<uint8_t>> A = hexToBinaryMatrix(hexA, n);
    vector<vector<uint8_t>> B = hexToBinaryMatrix(hexB, n);
    vector<vector<uint8_t>> C = hexToBinaryMatrix(hexC, n);

    

    bool ans = 0;
    for(int i = 0; i < 10; ++i) {
        vector<uint8_t> r = generateRandomBinaryVector(n);
        vector<uint8_t> Br = multiplyMatrixVector(B, r, n);
        vector<uint8_t> X = multiplyMatrixVector(A, Br, n);
        vector<uint8_t> Y = multiplyMatrixVector(C, r, n);
        ans = areVectorsEqual(X, Y);
        if(!ans) {
            break;
        }
    }

    if (ans) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}
