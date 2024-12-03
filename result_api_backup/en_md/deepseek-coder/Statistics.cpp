#include <iostream>
using namespace std;

int countTwos(int n) {
    int count = 0;
    while (n > 0) {
        if (n % 10 == 2) count++;
        n /= 10;
    }
    return count;
}

int main() {
    int L, R;
    cin >> L >> R;
    int totalCount = 0;
    for (int i = L; i <= R; i++) {
        totalCount += countTwos(i);
    }
    cout << totalCount << endl;
    return 0;
}