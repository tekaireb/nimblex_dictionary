#include "searchbar.h"

using namespace std;

Searchbar::Searchbar() {
    height = 3, width = 30, start_x = 0, start_y = 0;

    w = newwin(height, width, start_y, start_x);
    keypad(w, TRUE);
    box(w, 0, 0);  // Default characters for vertical/horizontal lines;
    wrefresh(w);   // Show
}

Searchbar::~Searchbar() {
    wborder(w, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');  // Remove border
    wrefresh(w);                                         // Overwrite border
    delwin(w);                                           // Delete window
}

void Searchbar::render() {
    werase(w);
    wattron(w, PAIR_CYAN);
    box(w, 0, 0);
    wattroff(w, PAIR_CYAN);

    // Render text
    if (search_term.size())
        mvwprintw(w, 1, 2, "%s", search_term.c_str());
    else
        mvwprintw(w, 1, 2, "Start typing...");  // Show hint if there is no word

    wrefresh(w);
}

void Searchbar::handle_keypress(int key) {
    if (isalpha(key) || key == '-' || key == ' ')
        search_term += (char)key;
    if (key == 127)  // DELETE (remove last character)
        search_term.pop_back();
    if (key == 27)  // ESC (delete word)
        search_term = "";
    if (key == 9) {  // TAB (select top suggestion)
        if (choices.size() != 0)
            search_term = choices[0];
    }
}