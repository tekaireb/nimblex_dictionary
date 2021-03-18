#include "main.h"

using namespace std;

int main() {
    Dictionary d;

    cout << "Loading words from file..." << endl;

    // d.load_from_file("datasets/dataset.txt");
    d.load_from_file("datasets/dictionary.json");

    cout << "Words loaded" << endl;

    // vector<string> v = d.t.children_search("min");
    // for (string s : v)
    //     cout << s << endl;

    Node* word = d.t.search("hermit");
    if (word)
        cout << "Defition of 'hermit': " << d.t.search("hermit")->definition << endl;
    else
        cout << "Definition not found" << endl;

    vector<string> fuzzy = d.t.fuzzy_search("minimum", 3);
    for (string s : fuzzy)
        cout << s << endl;
}