#ifndef UI_H
#define UI_H

#include <ncurses.h>

#include <queue>
#include <string>

#include "../dictionary.h"

#define PAIR_CYAN COLOR_PAIR(1)
#define PAIR_YELLOW COLOR_PAIR(2)

extern Dictionary d;
extern std::string search_term;
extern std::string previous_search_term;
extern std::vector<std::string> choices;
extern std::priority_queue<isp, std::vector<isp>, std::greater<isp>> pq;

#endif  // UI_H