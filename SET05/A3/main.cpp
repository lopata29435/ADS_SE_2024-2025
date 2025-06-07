#include <iostream>
#include <vector>

std::vector<std::string> findNeutralElements(int p) {
    std::vector<std::string> neutralPairs;
    std::string charset = "abcdefghijklmnopqrstuvwxyz0123456789";

    for (char s1 : charset) {
        int value1 = (s1 - 'a' + 1);
        if (value1 % p == 0) { 
            char s2 = 'a' - 1 - (value1 / p);
            if (charset.find(s2) != std::string::npos) {  
                neutralPairs.emplace_back(std::string() + s1 + s2);
            }
        }
    }
    return neutralPairs;
}

int main() {
    for (int p = 1; p <= 31; ++p) {
        std::vector<std::string> neutralElements = findNeutralElements(p);
        std::cout << "p = " << p << ": ";
        if (neutralElements.empty()) {
            std::cout << "NO";
        } else {
            for (const std::string &pair : neutralElements) {
                std::cout << pair << " ";
            }
        }
        std::cout << std::endl;
    }
    return 0;
}