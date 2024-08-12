#include <iostream>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    map<int, int> countMap;
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        countMap[num]++;
    }

    for (const auto& pair : countMap) {
        cout << pair.first << " " << pair.second << "\n";
    }

    return 0;
}
