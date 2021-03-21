#ifndef DEFINITION_H
#define DEFINITION_H

#include <ncurses.h>

#include <string>
#include <vector>

#include "window.h"

class Definition : public Window {
    int height,
        width,
        start_x,
        start_y;
    WINDOW* w_padding;

   public:
    Definition();
    ~Definition();

    void render();
    void handle_keypress(int key);
};

#endif  // DEFINITION_H