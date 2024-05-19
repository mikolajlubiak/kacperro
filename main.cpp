#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

bool can_make_word_out_of_letters(const std::string &word,
                                  const std::string &letters) {
  std::map<char, int> letterCounts;

  for (char letter : letters) {
    letterCounts[letter]++;
  }

  for (char letter : word) {
    if (--letterCounts[letter] < 0) {
      return false;
    }
  }

  return true;
}

int main() {
  std::string word, letters;
  std::ifstream wordlist("wordlist.txt");
  std::vector<std::string> words;
  words.reserve(8192);

  std::cout << "Letters: ";
  std::cin >> letters;

  if (wordlist.is_open()) {
    while (getline(wordlist, word)) {
      if (can_make_word_out_of_letters(word, letters) && word.length() >= 3) {
        words.emplace_back(word);
      }
    }
    wordlist.close();
  }

  std::sort(words.begin(), words.end(),
            [](const std::string &a, const std::string &b) {
              return a.size() < b.size();
            });

  for (std::string word : words) {
    std::cout << word << '\n';
  }

  return EXIT_SUCCESS;
}
