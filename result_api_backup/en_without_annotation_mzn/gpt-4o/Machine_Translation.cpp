#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    int M, N;
    cin >> M >> N;
    vector<int> words(N);
    for(int i = 0; i < N; ++i)
        cin >> words[i];

    vector<int> memory(M, -1);
    int seek_count = 0;

    for(int i = 0; i < N; ++i) {
        bool hit = false;
        for(int j = 0; j < M; ++j) {
            if(memory[j] == words[i]) {
                hit = true;
                break;
            }
        }
        if(!hit) {
            ++seek_count;
            for(int j = 0; j < M-1; ++j)
                memory[j] = memory[j+1];
            memory[M-1] = words[i];
        }
    }

    cout << seek_count << endl;

    return 0;
}