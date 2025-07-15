#include "Gui.hpp"

void drawTimeline(SDL_Renderer* renderer, const std::vector<int>& timeline) {
    int x = 50;
    int y = 100;
    int width = 40;
    int height = 40;

    for (size_t i = 0; i < timeline.size(); ++i) {
        int pid = timeline[i];

        if (pid == -1) {
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 50 * pid, 255 - 30 * pid, 100 + 20 * pid, 255);
        }

        SDL_Rect rect = {x + static_cast<int>(i) * width, y, width, height};
        SDL_RenderFillRect(renderer, &rect);
    }
}
