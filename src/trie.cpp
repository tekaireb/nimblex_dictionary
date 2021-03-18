#include "trie.h"

using namespace std;

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
            current->child(c)->letter = c;
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
        if (!current) break;
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
vector<string> Trie::children_search(string word) {
    vector<string> result;
    Node* current = search(word);
    if (current) children_search(current, word, result, "");
    return result;
}

void Trie::children_search(Node* current, string prefix, vector<string>& v, string suffix) {
    if (current->end_of_word && suffix.size())
        v.push_back(prefix + suffix);
    for (Node* n : current->children) {
        string temp = suffix;
        if (n) {
            temp += n->letter;
            children_search(n, prefix, v, temp);
        }
    }
}

vector<string> Trie::fuzzy_search(string word, int max_dif) {
    vector<string> results;
    vector<int> current_row(word.size() + 1);
    iota(begin(current_row), end(current_row), 0);  // Populate with 0, 1, ..., LEN_WORD

    for (Node* n : root->children)
        if (n)
            fuzzy_search_recursive(n, word, current_row, max_dif, results);

    return results;
}

void Trie::fuzzy_search_recursive(Node* n, string word, vector<int>& previous_row, int max_dif, vector<string>& results) {
    int columns = word.size();
    vector<int> current_row;
    current_row.push_back(previous_row[0] + 1);

    for (int column = 0; column < columns; column++) {
        int insert_dif = current_row[column] + 1;
        int delete_dif = previous_row[column + 1] + 1;

        int replace_dif = previous_row[column];
        if (word[column] != n->letter) replace_dif++;

        current_row.push_back(min3(insert_dif, delete_dif, replace_dif));
    }

    if (current_row.back() <= max_dif && n->end_of_word)
        results.push_back(n->word);

    if (*min_element(begin(current_row), end(current_row)) < max_dif)
        for (Node* m : n->children)
            if (m)
                fuzzy_search_recursive(m, word, current_row, max_dif, results);
}