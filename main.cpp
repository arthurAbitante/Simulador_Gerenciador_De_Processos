#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "Process.hpp"
#include "Scheduler.hpp"
#include "Gui.hpp"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Simulador de Escalonamento", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 300, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    std::vector<Process> processes = {
        Process(1, 0, 5, 2),
        Process(2, 1, 3, 1),
        Process(3, 2, 8, 3)
    };

    Scheduler scheduler(processes, 3);
    scheduler.step(); // Simula escalonamento

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        drawTimeline(renderer, scheduler.getTimeline());

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
