#include <iostream>
using namespace std;

int countOccurrences(int n, int x) {
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        int number = i;
        while (number > 0) {
            if (number % 10 == x)
                count++;
            number /= 10;
        }
    }
    return count;
}

int main() {
    int n, x;
    cin >> n >> x;
    cout << countOccurrences(n, x) << endl;
    return 0;
}