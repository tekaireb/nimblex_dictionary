#ifndef TEST_TRIE_H
#define TEST_TRIE_H

#include <iostream>

#include "../src/trie.h"
#include "test_helpers.h"

void test_trie();

void test_insert();
void test_search();
void test_children_search();
void test_fuzzy_search();

#endif  // TEST_TRIE_H