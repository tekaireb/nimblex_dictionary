#include "test.h"

void test_all() {
    test_trie();

    print_test_summary();
}

int main() {
    test_all();
}