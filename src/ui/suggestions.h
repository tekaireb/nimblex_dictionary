#ifndef SUGGESTIONS_H
#define SUGGESTIONS_H

#include "window.h"

class Suggestions : protected Window {
    int height = 0;
    int width = 0;
    int start_x = 0;
    int start_y = 0;

   public:
    Suggestions();
    ~Suggestions();

    void render();
    void handle_keypress(char key);
};

#endif  // SUGGESTIONS_H