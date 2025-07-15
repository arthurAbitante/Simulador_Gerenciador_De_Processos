#include "Gui.hpp"
#include <map>
#include <string>

void drawTimeline(SDL_Renderer* renderer, TTF_Font* font,
                  const std::vector<int>& timeline,
                  const std::vector<Process>& processes) {
    int x = 50, y = 100, width = 40, height = 40;
    std::map<int, Process> pidMap;
    for (const auto& p : processes)
        pidMap.emplace(p.pid, p);

    for (size_t i = 0; i < timeline.size(); ++i) {
        int pid = timeline[i];
        SDL_Color color;

        if (pid == -1) {
            color = {200, 200, 200, 255};
        } else {
            int prio = pidMap[pid].priority;
            switch (prio) {
                case 1: color = {255, 100, 100, 255}; break;
                case 2: color = {100, 200, 255, 255}; break;
                case 3: color = {100, 255, 150, 255}; break;
                default: color = {180, 180, 255, 255}; break;
            }
        }

        SDL_Rect rect = {x + (int)i * width, y, width, height};
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_RenderFillRect(renderer, &rect);

        if (pid != -1) {
            SDL_Color textColor = {0, 0, 0};
            std::string pidStr = "P" + std::to_string(pid);
            SDL_Surface* surf = TTF_RenderText_Blended(font, pidStr.c_str(), textColor);
            SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
            int tw, th;
            SDL_QueryTexture(tex, NULL, NULL, &tw, &th);
            SDL_Rect tr = {rect.x + (width - tw)/2, rect.y + (height - th)/2, tw, th};
            SDL_RenderCopy(renderer, tex, NULL, &tr);
            SDL_FreeSurface(surf);
            SDL_DestroyTexture(tex);
        }
    }
}