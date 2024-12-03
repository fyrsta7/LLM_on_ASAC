#include <iostream>
#include <string>
#include <cctype>
#include <sstream>

int main() {
    std::string word, article, token;
    std::getline(std::cin, word);
    std::getline(std::cin, article);

    // Convert the search word to lowercase
    std::string lower_word;
    for (char c : word) {
        lower_word += std::tolower(c);
    }

    int count = 0, first_position = -1;
    std::istringstream stream(article);
    int position = 0;

    // Tokenize the article by spaces
    while (stream >> token) {
        std::string lower_token;
        for (char c : token) {
            lower_token += std::tolower(c);
        }

        // Check for exact word match
        if (lower_token == lower_word) {
            count++;
            if (first_position == -1) {
                first_position = position;
            }
        }
        position += token.length() + 1; // Move position for the next token
    }

    if (count > 0) {
        std::cout << count << " " << first_position << std::endl;
    } else {
        std::cout << -1 << std::endl;
    }

    return 0;
}