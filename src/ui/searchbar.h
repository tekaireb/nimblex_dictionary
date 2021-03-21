#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <ncurses.h>

#include <string>
#include <vector>

#include "window.h"

class Searchbar : public Window {
    int height,
        width,
        start_x,
        start_y;

   public:
    Searchbar();
    ~Searchbar();

    void render();
    void handle_keypress(int key);
};

#endif  // SEARCHBAR_H