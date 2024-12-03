#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string find_str, text_str;
    std::cin >> find_str >> text_str;
    
    std::transform(find_str.begin(), find_str.end(), find_str.begin(), ::tolower);
    std::transform(text_str.begin(), text_str.end(), text_str.begin(), ::tolower);
    
    int find_len = find_str.length();
    int text_len = text_str.length();
    
    int num = 0;
    int t = -1;
    
    for (int i = 0; i <= text_len - find_len; ++i) {
        if (text_str.substr(i, find_len) == find_str) {
            if ((i == 0 || text_str[i - 1] == ' ') && (i + find_len == text_len || text_str[i + find_len] == ' ')) {
                ++num;
                if (t == -1) {
                    t = i;
                }
            }
        }
    }
    
    int final_ans = (num > 0) ? num : -1;
    t = (num > 0) ? t : -1;
    
    std::cout << final_ans << " " << t << std::endl;
    
    return 0;
}