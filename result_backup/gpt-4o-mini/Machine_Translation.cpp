#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

int main() {
    int M, N;
    cin >> M >> N;
    
    unordered_map<int, list<int>::iterator> memory;
    list<int> lru;
    int dictionaryLookups = 0;
    
    for (int i = 0; i < N; ++i) {
        int word;
        cin >> word;
        
        if (memory.find(word) == memory.end()) {
            // Not in memory, look it up in the dictionary
            dictionaryLookups++;
            if (memory.size() == M) {
                // Memory is full, remove the least recently used word
                int lruWord = lru.back();
                lru.pop_back();
                memory.erase(lruWord);
            }
            // Add new word to memory
            lru.push_front(word);
            memory[word] = lru.begin();
        } else {
            // Update the usage order
            lru.erase(memory[word]);
            lru.push_front(word);
            memory[word] = lru.begin();
        }
    }
    
    cout << dictionaryLookups << endl;
    return 0;
}