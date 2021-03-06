#ifndef TRIE_H
#define TRIE_H

#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

// Calculate minimum of two values
#define min(a, b) (a < b ? a : b)

// Calculate minimum of three values
#define min3(a, b, c) min(a, min(b, c))

// Helper used to access Node's children
// 0...25:  a-z
// 26:      SPACE
// 27:      -
#define child(c) children[(isalpha(c) ? (tolower(c) - 'a') : (c == ' ' ? 26 : 27))]

// Number of children in each node
#define NUM_CHILDREN 29

// Define int-string pair
typedef std::pair<int, std::string> isp;

// Nodes within the Trie
struct Node {
    char letter;                   // Letter stored in node
    bool end_of_word;              // Whether or not node is final character of word
    Node* children[NUM_CHILDREN];  // Pointers to children
    std::string word;              // Word (last char)
    std::string definition;        // Definition of word (last char)

    Node() : end_of_word(false), letter('\0') {
        std::fill_n(children, NUM_CHILDREN, nullptr);  // Clear children
    }

    ~Node() {
        for (int i = 0; i < NUM_CHILDREN; i++)
            delete children[i];
    }
};

// Trie data structure which holds all words
class Trie {
   public:
    Node* root;     // Pointer to root node (no letter of its own, only children)
    int num_words;  // Number of words stored in the Trie

    Trie();
    ~Trie() { delete root; }
    void insert(std::string word, std::string def);
    Node* search(std::string word);
    std::vector<std::string> prefix_search(std::string word);
    std::priority_queue<isp, std::vector<isp>, std::greater<isp>> fuzzy_search(std::string word, int max_dif);

   private:
    void prefix_search_recursive(Node* current, std::string& prefix, std::vector<std::string>& v, std::string suffix = "");
    void fuzzy_search_recursive(Node* n, std::string word, std::vector<int>& previous_row, int max_dif, std::priority_queue<isp, std::vector<isp>, std::greater<isp>>& results);
};

#endif  // TRIE_H