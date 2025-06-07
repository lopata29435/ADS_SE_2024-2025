#include <iostream>
#include <sstream>
#include <algorithm>

std::string KaratsubAdd(std::string& a, std::string& b) {
    std::string result;
    int carry = 0;  
    int i = a.size() - 1;
    int j = b.size() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;

        if (i >= 0) {
            sum += a[i] - '0';
            i--;
        }

        if (j >= 0) {
            sum += b[j] - '0';
            j--;
        }

        result += (sum % 10) + '0';
        carry = sum / 10;
    }

    std::reverse(result.begin(), result.end());

    return result;
}

std::string KaratsubSub(const std::string& a, const std::string& b) {
    std::string result;
    int carry = 0;

    std::string n1 = std::string(a.rbegin(), a.rend());
    std::string n2 = std::string(b.rbegin(), b.rend());

    int maxLength = n1.size();
    int minLength = n2.size();

    for (int i = 0; i < maxLength; ++i) {
        int digit1 = n1[i] - '0';
        int digit2 = (i < minLength) ? (n2[i] - '0') : 0;
        int difference = digit1 - digit2 - carry;

        if (difference < 0) {
            difference += 10;
            carry = 1;
        } else {
            carry = 0;
        }

        result += (difference + '0');
    }

    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }

    std::reverse(result.begin(), result.end());
    return result;
}

std::string Karatsuba(std::string a, std::string b) {
    if (a.size() <= 8 && b.size() <= 8) {
        unsigned long long res = std::stoll(a) * std::stoll(b);
        return std::to_string(res);
    }

    while (a.size() < b.size()) {
        a = '0' + a;
    }
    while (b.size() < a.size()) {
        b = '0' + b;
    }    

    int n = a.size();
    int half = n / 2;

    std::string a0 = a.substr(n - half);
    std::string a1 = a.substr(0, n - half);
    std::string b0 = b.substr(n - half);
    std::string b1 = b.substr(0, n - half);

    std::string z0 = Karatsuba(a0, b0);
    std::string z2 = Karatsuba(a1, b1);

    std::string aSum = KaratsubAdd(a1, a0);
    std::string bSum = KaratsubAdd(b1, b0);

    std::string z1 = Karatsuba(aSum, bSum);
    
    std::string part1 = z2 + std::string(2 * half, '0');
    std::string temp = KaratsubSub(z1, z2);
    temp = KaratsubSub(temp, z0);
    std::string part2 = temp + std::string(half, '0');

    std::string result = KaratsubAdd(part1, part2);
    result = KaratsubAdd(result, z0);

    while (result.size() > 1 && result[0] == '0') {
        result.erase(result.begin());
    }

    return result;
}

int main() {
    std::string a, b;
    std::cin >> a >> b;
    std::cout << Karatsuba(a, b) << '\n';
    return 0;
}
