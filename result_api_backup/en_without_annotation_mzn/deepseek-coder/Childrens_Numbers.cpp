#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, p;
    cin >> n >> p;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> character(n);
    vector<int> score(n);

    int current_max = a[0];
    int current_sum = a[0];
    character[0] = a[0];
    score[0] = a[0];

    for (int i = 1; i < n; ++i) {
        current_sum = max(a[i], current_sum + a[i]);
        current_max = max(current_max, current_sum);
        character[i] = current_max;
        score[i] = max(character[i], score[i-1] + character[i]);
    }

    int ans = *max_element(score.begin(), score.end()) % p;
    cout << ans << endl;

    return 0;
}