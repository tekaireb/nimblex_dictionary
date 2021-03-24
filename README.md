# Nimblex Dictionary
**A fast dictionary that lives in the Terminal.**

## Overview
Nimblex (_nimble lexicon_) is a dictionary built in C++ using the [ncurses](https://invisible-island.net/ncurses/ncurses.html) library for graphics.

### Blazing fast
Nimblex uses the [trie](https://en.wikipedia.org/wiki/Trie) data structure (prefix tree) in order to search large datasets incredibly fast. Suggestions appear instantaneously as the user types.

### Smart
Nimblex provides both autocomplete and fuzzy search. As the user types, autocomplete suggestions appear below the searchbar. If there is no exact match, Nimblex will suggest similar words based on [Levenshtein distance](https://en.wikipedia.org/wiki/Levenshtein_distance). Using [dynamic programming](https://en.wikipedia.org/wiki/Dynamic_programming), computation is reused as the dataset is traversed recursively, delivering quick performance. 

## Usage
Simply clone the repository and run:
```bash
git clone https://github.com/tekaireb/nimblex_dictionary.git
make run
```
Unit tests:
```bash
make test
```
Executables are placed in the ```/build``` folder by default.

To look up a word, simply run Nimblex and start typing! Core keybindings:
- Arrow keys: Navigate suggestions and scroll
- Enter: Select the highlighted suggestion
- Tab: Select the first suggestion
- Esc: Clear the input

The default dataset is [Webster's Unabridged English Dictionary](https://github.com/matthewreagan/WebstersEnglishDictionary). To load a custom dictionary, simply  replace ```dictionary.json``` with a file in the following format:
```javascript
{
    "[WORD #1]": "[ASSOCIATED DEFINITION #1]",
    "[WORD #2]": "[ASSOCIATED DEFINITION #2]",
    ...
}
```
