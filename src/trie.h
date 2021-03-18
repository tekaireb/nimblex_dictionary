#ifndef TRIE_H
#define TRIE_H

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#define min(a, b) \
    ({ typeof (a) _a = (a); \
       typeof (b) _b = (b); \
     _a < _b ? _a : _b; })

#define min3(a, b, c) min(a, min(b, c))

#define child(c) children[c - ' ']

struct Node {
    char letter;             // Letter stored in node
    bool end_of_word;        // Whether or not node is final character of word
    Node* children[97];      // Pointers to children
    std::string word;        // Word (last char)
    std::string definition;  // Definition of word (last char)

    Node() {
        std::fill_n(children, 97, nullptr);  // Clear children
        end_of_word = false;
        letter = '\0';
    }
};

class Trie {
   public:
    Node* root;
    int num_words;

    Trie();
    void insert(std::string word, std::string def);
    Node* search(std::string word);
    std::vector<std::string> children_search(std::string word);
    std::vector<std::string> fuzzy_search(std::string word, int max_dif);

   private:
    void children_search(Node* current, std::string prefix, std::vector<std::string>& v, std::string suffix = "");
    void fuzzy_search_recursive(Node* n, std::string word, std::vector<int>& previous_row, int max_dif, std::vector<std::string>& results);
};

#endif  // TRIE_H