#include "test_trie.h"

using namespace std;

void test_trie() {
    cout << "\n==[TESTING TRIE]==" << endl;

    test_insert();
    test_search();
    test_prefix_search();
    test_fuzzy_search();
}

void test_insert() {
    cout << "  Testing Trie::insert()" << endl;

    Trie t;
    t.insert("a", "A_def");
    t.insert("b", "B_def");
    t.insert("c", "C_def");
    t.insert("d", "D_def");

    test(t.root->child('a')->letter, 'a', "Test insert function 1", 4);
    test(t.root->child('b')->letter, 'b', "Test insert function 2", 4);
    test(t.root->child('c')->letter, 'c', "Test insert function 3", 4);
    test(t.root->child('d')->letter, 'd', "Test insert function 4", 4);
    test(t.root->child('e'), (Node *)nullptr, "Test insert function 5", 4);
}

void test_search() {
    cout << "  Testing Trie::search()" << endl;

    Trie t;
    t.insert("a", "A_def");
    t.insert("b", "B_def");
    t.insert("c", "C_def");
    t.insert("d", "D_def");

    test(t.search("a")->letter, 'a', "Test search function 1", 4);
    test(t.search("b")->letter, 'b', "Test search function 2", 4);
    test(t.search("c")->letter, 'c', "Test search function 3", 4);
    test(t.search("d")->letter, 'd', "Test search function 4", 4);
    test(t.search("e"), (Node *)nullptr, "Test search function 5", 4);
}

void test_prefix_search() {
    cout << "  Testing Trie::prefix_search()" << endl;

    Trie t;

    t.insert("a", "");
    t.insert("app", "");
    t.insert("apple", "");
    t.insert("application", "");
    t.insert("potato", "");

    vector<string> v = t.prefix_search("app");
    test((int)v.size(), 2, "Test children search function 1", 4);
    test(v[0], (string) "apple", "Test children search function 1", 4);
    test(v[1], (string) "application", "Test children search function 1", 4);
}

void test_fuzzy_search() {
    cout << "  Testing Trie::fuzzy_search()" << endl;

    Trie t;

    t.insert("example", "");
    t.insert("examplea", "");  // Distance = 1
    t.insert("efample", "");   // Distance = 1
    t.insert("eeample", "");   // Distance = 1
    t.insert("eeemple", "");   // Distance = 2
    t.insert("ffample", "");   // Distance = 2
    t.insert("fffmple", "");   // Distance = 3

    test((int)t.fuzzy_search("example", 0).size(), 1, "Test fuzzy search function 1", 4);
    test((int)t.fuzzy_search("example", 1).size(), 4, "Test fuzzy search function 2", 4);
    test((int)t.fuzzy_search("example", 2).size(), 6, "Test fuzzy search function 3", 4);
    test((int)t.fuzzy_search("example", 3).size(), 7, "Test fuzzy search function 4", 4);
}