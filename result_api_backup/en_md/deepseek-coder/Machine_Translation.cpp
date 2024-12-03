#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    int M, N;
    cin >> M >> N;
    vector<int> words(N);
    for (int i = 0; i < N; ++i) {
        cin >> words[i];
    }

    unordered_map<int, int> memory;
    int dictionaryLookups = 0;
    vector<int> memoryQueue;

    for (int word : words) {
        if (memory.find(word) == memory.end()) {
            dictionaryLookups++;
            if (memory.size() == M) {
                int oldestWord = memoryQueue.front();
                memoryQueue.erase(memoryQueue.begin());
                memory.erase(oldestWord);
            }
            memory[word] = 1;
            memoryQueue.push_back(word);
        }
    }

    cout << dictionaryLookups << endl;
    return 0;
}
