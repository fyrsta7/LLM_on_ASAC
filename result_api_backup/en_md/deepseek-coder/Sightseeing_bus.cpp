#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1005;
const int MAXM = 10005;
const int MAXK = 100005;

int n, m, k;
int D[MAXN];
int T[MAXM], A[MAXM], B[MAXM];
vector<int> passengers[MAXN];

int main() {
    cin >> n >> m >> k;
    for (int i = 1; i < n; ++i) {
        cin >> D[i];
    }
    for (int i = 1; i <= m; ++i) {
        cin >> T[i] >> A[i] >> B[i];
        passengers[A[i]].push_back(i);
    }

    long long total_time = 0;
    int bus_time = 0;
    for (int i = 1; i <= n; ++i) {
        bus_time += D[i - 1];
        int wait_time = 0;
        for (int p : passengers[i]) {
            wait_time = max(wait_time, T[p]);
        }
        bus_time = max(bus_time, wait_time);
        for (int p : passengers[i]) {
            total_time += bus_time - T[p];
        }
    }

    vector<int> diff(n, 0);
    for (int i = 1; i < n; ++i) {
        diff[i] = D[i] - D[i - 1];
    }
    sort(diff.begin() + 1, diff.end(), greater<int>());

    for (int i = 1; i < n && k > 0; ++i) {
        int reduce = min(k, diff[i]);
        k -= reduce;
        total_time -= reduce * (n - i);
    }

    cout << total_time << endl;
    return 0;
}
