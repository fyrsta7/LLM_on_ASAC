#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> fingers(N);
    for (int i = 0; i < N; ++i) {
        cin >> fingers[i];
    }
    
    int pos = (M - 1) % N; // find the position to swap
    swap(fingers[pos], fingers[(pos + 1) % N]); // swap with the next finger

    for (int i = 0; i < N; ++i) {
        cout << fingers[i] << (i == N - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}