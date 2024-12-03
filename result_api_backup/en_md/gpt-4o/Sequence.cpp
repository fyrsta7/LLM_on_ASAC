#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int k, N;
    cin >> k >> N;

    vector<int> sequence;
    sequence.push_back(1);
    
    for (int i = 1; i <= 33; ++i) {
        int power = 1;
        for (int j = 0; j < i; ++j) {
            power *= k;
        }
        int size = sequence.size();
        for (int j = 0; j < size; ++j) {
            sequence.push_back(sequence[j] + power);
        }
    }

    sort(sequence.begin(), sequence.end());
    
    // Erase duplicates
    sequence.erase(unique(sequence.begin(), sequence.end()), sequence.end());

    cout << sequence[N - 1] << endl;

    return 0;
}