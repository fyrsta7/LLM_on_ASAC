#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::string n;
    int k;
    std::cin >> n >> k;

    // Reduce n to its last k digits
    if (n.size() > k) {
        n = n.substr(n.size() - k);
    }

    // Convert n to integer for easier manipulation
    int base = std::stoi(n);

    int mod = 1;
    for (int i = 0; i < k; ++i) {
        mod *= 10;
    }

    std::unordered_map<int, int> seen;
    int cur = 1;
    int length = 0;

    while (true) {
        if (seen.count(cur)) {
            length = length - seen[cur];
            break;
        }
        seen[cur] = length;
        cur = (cur * base) % mod;
        ++length;
        if (cur == 1) {
            break;
        }
    }
    std::cout << length << std::endl;
    return 0;
}