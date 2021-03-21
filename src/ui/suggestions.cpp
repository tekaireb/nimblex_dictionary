#include "suggestions.h"

#include <iostream>

using namespace std;

Suggestions::Suggestions() {
    choices = {"Test1", "Test2", "Test3", "Test4", "Test5"};
    height = choices.size() + 2, width = 30, start_x = 0, start_y = 3, choice = -1;

    w = newwin(height, width, start_y, start_x);
    keypad(w, TRUE);
    box(w, 0, 0);  // Default characters for vertical/horizontal lines;
    wrefresh(w);   // Show
}

Suggestions::~Suggestions() {
    wborder(w, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');  // Remove border
    wrefresh(w);                                         // Overwrite border
    delwin(w);                                           // Delete window
}

void Suggestions::render() {
    int x = 2, y = 1;

    werase(w);
    box(w, 0, 0);

    for (int i = 0; i < choices.size(); i++) {
        if (choice == i) {  // Highlight the selected option
            wattron(w, A_REVERSE);
            mvwprintw(w, y, x, "%s", choices[i].c_str());
            wattroff(w, A_REVERSE);
        } else
            mvwprintw(w, y, x, "%s", choices[i].c_str());
        y++;
    }

    wrefresh(w);
}

void Suggestions::handle_keypress(int key) {
    switch (key) {
        case KEY_UP:
            if (choice == -1)
                choice++;
            else if (choice == 0)
                choice = choices.size() - 1;
            else
                choice--;
            break;
        case KEY_DOWN:
            if (choice == -1)
                choice++;
            else if (choice == choices.size() - 1)
                choice = 0;
            else
                choice++;
            break;
        case 10:  // ENTER
            if (choice != -1) {
                search_term = choices[choice];
                choice = -1;
            }
            break;
        default:
            choice = -1;
            break;
    }

    render();
}