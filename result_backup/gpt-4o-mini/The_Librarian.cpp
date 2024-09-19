#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> books(n);
    for (int i = 0; i < n; ++i) {
        cin >> books[i];
    }

    sort(books.begin(), books.end());

    for (int i = 0; i < q; ++i) {
        int len, req_code;
        cin >> len >> req_code;
        string req_str = to_string(req_code);
        int min_book = -1;

        for (int book : books) {
            string book_str = to_string(book);
            if (book_str.size() >= len && book_str.substr(book_str.size() - len) == req_str) {
                if (min_book == -1 || book < min_book) {
                    min_book = book;
                }
            }
        }
        cout << min_book << endl;
    }

    return 0;
}