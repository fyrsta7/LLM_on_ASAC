#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int k, N;
    cin >> k >> N;

    vector<int> powers;
    int power = 1;
    while (power <= 1000000) {
        powers.push_back(power);
        power *= k;
    }

    int size = powers.size();
    vector<int> sequence;
    for (int i = 1; i < (1 << size); ++i) {
        int sum = 0;
        for (int j = 0; j < size; ++j) {
            if (i & (1 << j)) {
                sum += powers[j];
            }
        }
        sequence.push_back(sum);
    }

    sort(sequence.begin(), sequence.end());
    cout << sequence[N - 1] << endl;

    return 0;
}