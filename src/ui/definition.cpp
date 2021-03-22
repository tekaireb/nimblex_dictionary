#include "definition.h"

using namespace std;

Definition::Definition() {
    height = 30, width = 70, start_x = 31, start_y = 0;

    w = newwin(height, width, start_y, start_x);
    keypad(w, TRUE);
    box(w, 0, 0);  // Default characters for vertical/horizontal lines;
    wrefresh(w);   // Show

    w_padding = newwin(height - 2, width - 4, start_y + 1, start_x + 2);
    scrollok(w_padding, TRUE);
}

Definition::~Definition() {
    wborder(w, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');  // Remove border
    wrefresh(w);                                         // Overwrite border
    delwin(w);                                           // Delete window
    delwin(w_padding);
}

void Definition::render() {
    box(w, 0, 0);
    werase(w_padding);

    // Show hint if there is no word
    if (!search_term.size()) {
        mvwprintw(w_padding, 0, 0, "Definition will appear here...");
        wrefresh(w_padding);
        return;
    }

    // Render text
    Node* n = d.t.search(search_term);
    if (n)
        // mvwprintw(w, 1, 2, "%s", n->definition.c_str(), 5, 5);
        mvwprintw(w_padding, 0, 0, "%s", n->definition.c_str(), 10, 10);

    wrefresh(w_padding);
}

void Definition::handle_keypress(int key) {
}