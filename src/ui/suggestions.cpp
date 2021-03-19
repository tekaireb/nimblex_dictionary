#include "suggestions.h"

Suggestions::Suggestions() {
    w = newwin(height, width, start_y, start_x);
    box(w, 0, 0);  // Default characters for vertical/horizontal lines;
    wrefresh(w);   // Show
}

Suggestions::~Suggestions() {
    wborder(w, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');  // Remove border
    wrefresh(w);                                         // Overwrite border
    delwin(w);                                           // Delete window
}

void Suggestions::render() {
    
    
    wrefresh(w);
}

void Suggestions::handle_keypress(char key) {
}