#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string find_str, text_str;
    cin >> find_str >> text_str;

    transform(find_str.begin(), find_str.end(), find_str.begin(), ::tolower);
    transform(text_str.begin(), text_str.end(), text_str.begin(), ::tolower);

    int find_len = find_str.length();
    int text_len = text_str.length();

    int num = 0;
    int t = -1;

    for (int i = 0; i <= text_len - find_len; ++i) {
        if (text_str.substr(i, find_len) == find_str) {
            if ((i == 0 || text_str[i - 1] == ' ') && (i + find_len == text_len || text_str[i + find_len] == ' ')) {
                if (num == 0) t = i;
                ++num;
            }
        }
    }

    if (num > 0) {
        cout << num << " " << t << endl;
    } else {
        cout << "-1" << endl;
    }

    return 0;
}
