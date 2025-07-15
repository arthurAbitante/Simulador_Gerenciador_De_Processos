#ifndef GUI_HPP
#define GUI_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "Process.hpp"

void drawTimeline(SDL_Renderer* renderer, TTF_Font* font,
                  const std::vector<int>& timeline,
                  const std::vector<Process>& processes);

#endif