#ifndef GUI_HPP
#define GUI_HPP

#include <SDL2/SDL.h>
#include <vector>

void drawTimeline(SDL_Renderer* renderer, const std::vector<int>& timeline);

#endif
