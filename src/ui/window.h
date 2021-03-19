#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>

class Window {
   protected:
    WINDOW* w;

   public:
    Window();
    ~Window();

    virtual void render() = 0;
    virtual void handle_keypress(char key) = 0;
};

#endif  // WINDOW_H