#include <iostream>
#include <unordered_set>
#include <queue>

int main() {
    int M, N;
    std::cin >> M >> N;
    std::unordered_set<int> memory;
    std::queue<int> order;
    int dictionary_lookups = 0;

    for (int i = 0; i < N; ++i) {
        int word;
        std::cin >> word;

        if (memory.find(word) == memory.end()) {
            dictionary_lookups++;
            if (memory.size() == M) {
                int old_word = order.front();
                order.pop();
                memory.erase(old_word);
            }
            memory.insert(word);
            order.push(word);
        }
    }

    std::cout << dictionary_lookups << std::endl;
    return 0;
}