#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    
    vector<int> books(n);
    for (int i = 0; i < n; ++i) {
        cin >> books[i];
    }
    
    sort(books.begin(), books.end());
    
    unordered_map<int, int> minBookCode;
    for (int book : books) {
        int length = to_string(book).length();
        for (int i = 1; i <= length; ++i) {
            int suffix = book % (int)pow(10, i);
            if (minBookCode.find(suffix) == minBookCode.end()) {
                minBookCode[suffix] = book;
            }
        }
    }
    
    for (int i = 0; i < q; ++i) {
        int length, reqCode;
        cin >> length >> reqCode;
        int suffix = reqCode % (int)pow(10, length);
        if (minBookCode.find(suffix) != minBookCode.end()) {
            cout << minBookCode[suffix] << endl;
        } else {
            cout << -1 << endl;
        }
    }
    
    return 0;
}
