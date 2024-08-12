#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> numbers(N);
    for (int i = 0; i < N; ++i) {
        cin >> numbers[i];
    }
    sort(numbers.begin(), numbers.end());
    numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());
    int M = numbers.size();
    cout << M << endl;
    for (int i = 0; i < M; ++i) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    return 0;
}