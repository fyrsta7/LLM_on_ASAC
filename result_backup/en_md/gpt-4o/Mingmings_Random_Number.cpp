#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    int N;
    cin >> N;
    
    set<int> uniqueNumbers;
    for (int i = 0; i < N; ++i) {
        int num;
        cin >> num;
        uniqueNumbers.insert(num);
    }
    
    cout << uniqueNumbers.size() << endl;
    for (auto it = uniqueNumbers.begin(); it != uniqueNumbers.end(); ++it) {
        if (it != uniqueNumbers.begin()) cout << " ";
        cout << *it;
    }
    cout << endl;
    
    return 0;
}