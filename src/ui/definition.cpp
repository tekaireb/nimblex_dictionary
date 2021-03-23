#include "definition.h"

using namespace std;

Definition::Definition() {
    height = 30, width = 90, start_x = 31, start_y = 0;
    pad_height = height - 2, pad_width = width - 4;
    scroll_pos = 0;
    w = newwin(height, width, start_y, start_x);

    keypad(w, TRUE);
    box(w, 0, 0);  // Default characters for vertical/horizontal lines;
    wrefresh(w);   // Show

    w_padding = newwin(pad_height, pad_width, start_y + 1, start_x + 2);
    scrollok(w_padding, TRUE);
}

Definition::~Definition() {
    wborder(w, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');  // Remove border
    wrefresh(w);                                         // Overwrite border
    delwin(w);                                           // Delete window
    delwin(w_padding);
}

void Definition::render() {
    wattron(w, PAIR_CYAN);
    box(w, 0, 0);
    wattroff(w, PAIR_CYAN);
    werase(w_padding);

    // Show hint if there is no word
    if (!search_term.size()) {
        // Print ASCII Art
        mvwprintw(w_padding, 2, 14, "         d8b               888      888                   ");
        mvwprintw(w_padding, 3, 14, "         Y8P               888      888                   ");
        mvwprintw(w_padding, 4, 14, "                           888      888                   ");
        mvwprintw(w_padding, 5, 14, "88888b.  888 88888b.d88b.  88888b.  888  .d88b.  888  888 ");
        mvwprintw(w_padding, 6, 14, "888 \"88b 888 888 \"888 \"88b 888 \"88b 888 d8P  Y8b `Y8bd8P' ");
        mvwprintw(w_padding, 7, 14, "888  888 888 888  888  888 888  888 888 88888888   X88K   ");
        mvwprintw(w_padding, 8, 14, "888  888 888 888  888  888 888 d88P 888 Y8b.     .d8\"\"8b. ");
        mvwprintw(w_padding, 9, 14, "888  888 888 888  888  888 88888P\"  888  \"Y8888  888  888 ");

        // Print tagline
        string tagline = "[A lightweight lexicon for a more civilized age]";
        mvwprintw(w_padding, 12, (pad_width / 2 - (tagline.size() / 2)), "%s", tagline.c_str());

        // Print instructions
        mvwprintw(w_padding, 15, 21, "Commands:");
        mvwprintw(w_padding, 16, 26, "Up/Down:  navigate suggestions");
        mvwprintw(w_padding, 17, 26, "Enter:    select highlighted suggestion");
        mvwprintw(w_padding, 18, 26, "Tab:      select first suggestion");
        mvwprintw(w_padding, 19, 26, "Esc:      clear input");

        // Credits
        string credit_text = "Created by Tyler Ekaireb";
        mvwprintw(w_padding, 25, (pad_width / 2 - (credit_text.size() / 2)), "%s", credit_text.c_str());

        wrefresh(w);
        wrefresh(w_padding);
        return;
    }

    // Render text
    Node* n = d.t.search(search_term);
    if (n) {
        // Display word as header
        if (n->word.size()) {
            wattron(w, PAIR_YELLOW);
            mvwprintw(w, 0, ((width - 4) / 2 - (n->word.size() / 2)), "[%s]", n->word.c_str());
            wattroff(w, PAIR_YELLOW);
        }

        // Display definition
        formatted_definition.clear();
        int start = 0;
        int end = pad_width;
        string& raw_def = n->definition;

        // Format line breaks
        while (end < raw_def.size()) {
            // Decrement from max width until space or hyphen is found
            while (raw_def.at(end) != ' ' && raw_def.at(end) != '-')
                end--;
            // Add new line to formatted definition
            formatted_definition.push_back(raw_def.substr(start, end - start));
            // Insert hyphen if necessary
            if (raw_def.at(end) == '-') formatted_definition.back() += '-';

            start = end + 1;
            end += pad_width;  // Jump to max width
        }
        formatted_definition.push_back(raw_def.substr(start, raw_def.size() - start));  // Add last line

        // Print formatted definition line-by-line
        if (formatted_definition.size() <= pad_height)  // Entire definition fits in window
            for (int i = 0; i < formatted_definition.size(); i++)
                mvwprintw(w_padding, i, 0, "%s", formatted_definition[i].c_str());
        else  // Definition is too long; only print section (determined by scroll position)
            for (int i = scroll_pos; i < scroll_pos + pad_height; i++)
                mvwprintw(w_padding, i - scroll_pos, 0, "%s", formatted_definition[i].c_str());
    }

    wrefresh(w);
    wrefresh(w_padding);
}

void Definition::handle_keypress(int key) {
    switch (key) {
        case KEY_UP:
            if (scroll_pos > 0)
                scroll_pos--;
            break;
        case KEY_DOWN:
            if (scroll_pos + pad_height < formatted_definition.size())
                scroll_pos++;
            break;
    }
}