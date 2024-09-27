#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    int M, N;
    cin >> M >> N;
    vector<int> words(N);
    for (int i = 0; i < N; ++i) {
        cin >> words[i];
    }

    unordered_set<int> cache;
    int seek_count = 0;

    for (int i = 0; i < N; ++i) {
        if (cache.find(words[i]) == cache.end()) {
            if (cache.size() == M) {
                cache.erase(cache.begin());
            }
            cache.insert(words[i]);
            ++seek_count;
        }
    }

    cout << seek_count << endl;
    return 0;
}