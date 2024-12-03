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
    int seeks = 0;

    for (int i = 0; i < N; ++i) {
        if (cache.find(words[i]) == cache.end()) {
            seeks++;
            if (cache.size() == M) {
                cache.erase(cache.begin());
            }
            cache.insert(words[i]);
        }
    }

    cout << seeks << endl;
    return 0;
}