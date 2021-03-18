#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <fstream>
#include <iostream>
#include <string>

#include "trie.h"

class Dictionary {
   public:
    Trie t;

    Dictionary();
    void load_from_file(std::string filename);
};

#endif  // DICTIONARY_H