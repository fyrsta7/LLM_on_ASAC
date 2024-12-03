#include <iostream>
#include <vector>
#include <unordered_set>

int main() {
    int M, N;
    std::cin >> M >> N;
    std::vector<int> words(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> words[i];
    }

    std::unordered_set<int> cache;
    int seek_count = 0;

    for (int i = 0; i < N; ++i) {
        if (cache.find(words[i]) == cache.end()) {
            if (cache.size() < M) {
                cache.insert(words[i]);
            } else {
                cache.erase(cache.begin());
                cache.insert(words[i]);
            }
            ++seek_count;
        }
    }

    std::cout << seek_count << std::endl;
    return 0;
}