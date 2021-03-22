#include "suggestions.h"

#include <iostream>

using namespace std;

Suggestions::Suggestions() {
    height = 27, width = 30, start_x = 0, start_y = 3, choice = -1;

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

    // Show hint if there is no word
    if (!search_term.size()) {
        mvwprintw(w, y, x, "Suggestions...");
        wrefresh(w);
        return;
    }

    // Only compute suggestions when there is a new search term
    if (previous_search_term != search_term) {
        choices = d.t.prefix_search(search_term);
        if (choices.size() > 20)
            choices.resize(25);

        // Use fuzzy search if there are no matching words
        if (!choices.size()) {
            pq = d.t.fuzzy_search(search_term, 3);

            // Add words in priority queue to choices vector
            while (!pq.empty() && choices.size() < 23) {
                choices.push_back(pq.top().second);  // Add word to choices
                pq.pop();                            // Remove word from priority queue
            }
        }
    }

    // Add 'DID YOU MEAN?' text if word does not exist
    if (!d.t.search(search_term)) {
        mvwprintw(w, y, x, "DID YOU MEAN?");
        y += 2;
    }

    for (int i = 0; i < choices.size(); i++) {
        if (choice == i) {  // Highlight the selected option
            wattron(w, A_REVERSE);
            mvwprintw(w, y, x, "%s", choices[i].c_str());
            wattroff(w, A_REVERSE);
        } else
            mvwprintw(w, y, x, "%s", choices[i].c_str());
        y++;
    }

    previous_search_term = search_term;
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
}