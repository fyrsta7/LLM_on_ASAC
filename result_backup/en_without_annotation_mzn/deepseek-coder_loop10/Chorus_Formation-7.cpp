#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> T(N);
    for (int i = 0; i < N; ++i) {
        cin >> T[i];
    }

    vector<int> sortedT = T;
    sort(sortedT.begin(), sortedT.end());

    int discard_num = 0;
    for (int i = 0; i < N; ++i) {
        if (T[i] != sortedT[i]) {
            ++discard_num;
        }
    }

    cout << discard_num << endl;
    return 0;
}