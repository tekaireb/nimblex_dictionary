#include "main.h"

using namespace std;

int main() {
    cout << "Loading words from file..." << endl;

    // d.load_from_file("datasets/dataset.txt");
    d.load_from_file("datasets/dictionary.json");

    cout << "Words loaded" << endl;

    // vector<string> v = d.t.prefix_search("min");
    // for (string s : v)
    //     cout << s << endl;

    // Node* word = d.t.search("hermit");
    // if (word)
    //     cout << "Defition of 'hermit': " << d.t.search("hermit")->definition << endl;
    // else
    //     cout << "Definition not found" << endl;

    // priority_queue<isp> fuzzy = d.t.fuzzy_search("minimum", 3);

    // ncurses initialization
    initscr();
    clear();
    noecho();
    // cbreak();

    int key;
    vector<Window*> windows = {new Suggestions, new Searchbar, new Definition};

    for (Window* w : windows) w->render();  // Initial render

    while (1) {
        key = wgetch(windows[0]->w);                        // Get user input
        for (Window* w : windows) w->handle_keypress(key);  // Handle input
    }
}