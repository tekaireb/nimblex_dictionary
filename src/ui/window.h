#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>

#include "ui.h"

class Window {
   public:
    WINDOW* w;

    Window() {}
    virtual ~Window() {}

    virtual void render() = 0;
    virtual void handle_keypress(int key) = 0;
};

#endif  // WINDOW_H