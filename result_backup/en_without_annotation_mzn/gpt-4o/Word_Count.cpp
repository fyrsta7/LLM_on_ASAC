#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

bool is_word_boundary(const std::string& text, size_t pos, size_t len) {
    if (pos > 0 && text[pos - 1] != ' ') return false;
    if (pos + len < text.size() && text[pos + len] != ' ') return false;
    return true;
}

int main() {
    std::string find_str, text_str;
    std::getline(std::cin, find_str);
    std::getline(std::cin, text_str);
    
    std::transform(find_str.begin(), find_str.end(), find_str.begin(), ::tolower);
    std::transform(text_str.begin(), text_str.end(), text_str.begin(), ::tolower);
    
    size_t find_len = find_str.length();
    size_t text_len = text_str.length();
    
    std::vector<size_t> positions;
    for (size_t i = 0; i <= text_len - find_len; ++i) {
        if (text_str.substr(i, find_len) == find_str && is_word_boundary(text_str, i, find_len)) {
            positions.push_back(i);
        }
    }
    
    int final_ans = positions.size();
    int t = positions.empty() ? -1 : positions[0];
    
    std::cout << (final_ans > 0 ? final_ans : -1) << t << std::endl;
    
    return 0;
}