#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string word, article;
    getline(cin, word);
    getline(cin, article);

    for (char &c : word) c = tolower(c);
    for (char &c : article) c = tolower(c);

    int wordLen = word.length();
    int articleLen = article.length();
    int count = 0;
    int firstPos = -1;

    for (int i = 0; i <= articleLen - wordLen; ++i) {
        if (article.substr(i, wordLen) == word) {
            if ((i == 0 || !isalpha(article[i - 1])) && (i + wordLen == articleLen || !isalpha(article[i + wordLen]))) {
                ++count;
                if (firstPos == -1) {
                    firstPos = i;
                }
            }
        }
    }

    if (count > 0) {
        cout << count << " " << firstPos << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}