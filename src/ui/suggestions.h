#ifndef SUGGESTIONS_H
#define SUGGESTIONS_H

#include <ncurses.h>

#include <string>
#include <vector>

#include "window.h"

class Suggestions : public Window {
    int height,
        width,
        start_x,
        start_y,
        choice;
    std::vector<std::string> choices;
    std::priority_queue<isp, std::vector<isp>, std::greater<isp>> pq;

   public:
    Suggestions();
    ~Suggestions();

    void render();
    void handle_keypress(int key);
};

#endif  // SUGGESTIONS_H