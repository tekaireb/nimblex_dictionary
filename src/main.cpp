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

    start_color();  // Start ncurses color

    // Create color pairs
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    int key;
    vector<Window*> windows = {new Searchbar, new Suggestions, new Definition};

    while (1) {
        for (Window* w : windows) w->render();              // Render windows
        key = wgetch(windows[0]->w);                        // Get user input
        for (Window* w : windows) w->handle_keypress(key);  // Handle input
    }
}