#include "trie.h"

using namespace std;

// Trie constructor
Trie::Trie() {
    root = new Node;
    num_words = 0;
}

/**
 * Adds a node to the trie
 * 
 * @param word  word to be added to the trie
 * @param def   definition associated with the word
 */
void Trie::insert(string word, string def) {
    Node* current = root;
    for (char c : word) {
        if (!current->child(c)) {
            current->child(c) = new Node;
            current->child(c)->letter = tolower(c);
        }
        current = current->child(c);
    }
    current->end_of_word = true;
    current->word = word;
    current->definition = def;
}

/**
 * Gets the node which holds the last character of a word
 * 
 * @param word  word to be found
 * 
 * @return pointer to the node with the last character of the word
 */
Node* Trie::search(string word) {
    Node* current = root;
    for (char c : word) {
        current = current->child(c) ? current->child(c) : nullptr;
        if (!current) break;  // Word does not exist
    }
    return current;
}

/**
 * Gets a list of all words which begin with a given prefix
 * 
 * @param word  word to be used as prefix
 * 
 * @return list of words which begin with the prefix
 */
vector<string> Trie::prefix_search(string word) {
    vector<string> result;
    Node* current = search(word);
    if (current) prefix_search_recursive(current, word, result, "");
    return result;
}

/**
 * Recursive helper function to search for words by prefix
 * 
 * @param current  pointer to current node in traversal
 * @param prefix   substring with which each word begins
 * @param v        vector which is populated with matching words
 * @param suffix   all characters in word after prefix
 */
void Trie::prefix_search_recursive(Node* current, string& prefix, vector<string>& v, string suffix) {
    if (current->end_of_word && suffix.size())
        v.push_back(prefix + suffix);
    for (Node* n : current->children) {
        string temp = suffix;
        if (n) {
            temp += n->letter;
            prefix_search_recursive(n, prefix, v, temp);
        }
    }
}

/**
 * Searches for words similar to target word within maximum Levenshtein distance
 * 
 * @param word     target word used for comparison
 * @param max_dif  maximum Levenshtein distance allowed
 * 
 * @return vector holding all words with Levenshtein distance of 'max_dif' or less from 'word'
 */
priority_queue<isp, vector<isp>, greater<isp>> Trie::fuzzy_search(string word, int max_dif) {
    priority_queue<isp, vector<isp>, greater<isp>> results;
    vector<int> current_row(word.size() + 1);
    iota(begin(current_row), end(current_row), 0);  // Populate with 0, 1, ..., LEN_WORD

    // Search all nodes recursively
    for (Node* n : root->children)
        if (n)
            fuzzy_search_recursive(n, word, current_row, max_dif, results);

    return results;
}

/**
 * Recursive helper function to search for words by Levenshtein distance from target
 * 
 * @param n             pointer to current node in traversal
 * @param word          target word for comparison
 * @param previous_row  previous row in NxM Levenshtein matrix
 * @param max_dif       maximum distance allowed from target word
 * @param results       vector to be populated with matching words
 * 
 * The matrix is generated incrementally, and multiple children make use of parents'
 * partial computation in order to improve performance.
 * 
 * Example matrix (Flaw vs. Lawn):
 * 
 *         F   L   A   W
 *   +---+---+---+---+---+
 *   | 0 | 1 | 2 | 3 | 4 |
 * L | 1 | 1 | 1 | 2 | 3 |
 * A | 2 | 2 | 2 | 1 | 2 |
 * W | 3 | 3 | 3 | 2 | 1 |
 * N | 4 | 4 | 4 | 3 | 2 |  <-- Distance = 2
 *   +---+---+---+---+---+
 * 
 * Suppose the letter 'n' in 'lawn' has a child 's'. All of the previous computation
 * is valid for the word 'lawns', and the last row ('previous_row') contains all
 * necessary information.
 */
void Trie::fuzzy_search_recursive(Node* n, string word, vector<int>& previous_row, int max_dif, priority_queue<isp, vector<isp>, greater<isp>>& results) {
    int columns = word.size();
    vector<int> current_row;  // Add one new row per letter
    current_row.push_back(previous_row[0] + 1);

    // Construct row, where each column in based on distance from a letter in 'word'
    for (int column = 0; column < columns; column++) {
        int insert_dif = current_row[column] + 1;
        int delete_dif = previous_row[column + 1] + 1;

        int replace_dif = previous_row[column];
        if (word[column] != n->letter) replace_dif++;

        current_row.push_back(min3(insert_dif, delete_dif, replace_dif));
    }

    // Add word to results if reached end of word, last entry (distance) is within bounds (and ignore word itself)
    if (n->end_of_word && current_row.back() <= max_dif && current_row.back() != 0)
        results.push(make_pair(current_row.back(), n->word));

    // Search children if any entries are within bounds
    if (*min_element(begin(current_row), end(current_row)) <= max_dif)
        for (Node* m : n->children)
            if (m)
                fuzzy_search_recursive(m, word, current_row, max_dif, results);
}