#include <iostream>
#include <string>
#include <stack>


int main() {
    std::string s;
     std::getline(std::cin, s); 

    std::stack<std::string> strStack;
    std::stack<int> numStack;
    std::string ans;
    int num = 0;
    
    for (char c : s) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        } else if (c == '[') {
            numStack.push(num);
            strStack.push(ans);
            num = 0;
            ans = "";
        } else if (c == ']') {
            std::string temp = ans;
            ans = strStack.top();
            strStack.pop();
            int repeatTimes = numStack.top();
            numStack.pop();
            
            for (int i = 0; i < repeatTimes; ++i) {
                ans += temp;
            }
        } else {
            ans += c;
        }
    }

    std::cout << ans;
    return 0;
}