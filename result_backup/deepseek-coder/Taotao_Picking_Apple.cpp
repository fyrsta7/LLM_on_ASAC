#include <iostream>
using namespace std;

int main() {
    int apples[10];
    int taotao_reach, bench_height = 30, count = 0;

    for (int i = 0; i < 10; ++i) {
        cin >> apples[i];
    }
    cin >> taotao_reach;

    int total_reach = taotao_reach + bench_height;

    for (int i = 0; i < 10; ++i) {
        if (apples[i] <= total_reach) {
            count++;
        }
    }

    cout << count << endl;
    return 0;
}