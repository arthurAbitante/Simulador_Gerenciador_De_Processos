#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "Process.hpp"
#include "Scheduler.hpp"
#include "Gui.hpp"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Init error: " << SDL_GetError() << "\n";
        return 1;
    }

    if (TTF_Init() != 0) {
        std::cerr << "TTF Init error: " << TTF_GetError() << "\n";
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("assets/OpenSans-Regular.ttf", 18);
    if (!font) {
        std::cerr << "Font load error: " << TTF_GetError() << "\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Simulador de Escalonamento",
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        1000, 350, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    std::vector<Process> processes = {
        Process(1, 0, 5, 2),
        Process(2, 1, 3, 1),
        Process(3, 2, 8, 3)
    };

    Scheduler scheduler(processes, 3);
    scheduler.step();

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;

            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_1:
                        scheduler.setAlgorithm(Algorithm::RoundRobin);
                        scheduler.step();
                        break;
                    case SDLK_2:
                        scheduler.setAlgorithm(Algorithm::Priority);
                        scheduler.step();
                        break;
                    case SDLK_a:{
                        int pid = (int) processes.size() + 1;
                        Process p(pid, rand() % 5, rand() % 5 + 1, rand() % 3 + 1);
                        processes.push_back(p);
                        scheduler.step();
                        break;
                    }
                    case SDLK_r:
                        processes.clear();
                        processes = {
                            Process(1, 0, 5, 2),
                            Process(2, 1, 3, 1),
                            Process(3, 2, 8, 3)
                        };
                        scheduler.step();
                        break;
                    case SDLK_s: 
                        std::ofstream out("output.txt");
                        auto timeline = scheduler.getTimeline();
                        for(size_t i = 0; i < timeline.size(); i++)
                            out << "Time " << i << ": PID " << timeline[i] << "\\n";                        out.close();
                        std::cout << "Timeline salva em output.txt\\n";
                        break;
                    

                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        drawTimeline(renderer, font, scheduler.getTimeline(), processes);

        SDL_Color textColor = {0, 0, 0, 255};
        std::string legend = "1: RR 2: Prioridade A: Add R: Reset S: Save";
        SDL_Surface* surf = TTF_RenderText_Blended(font, legend.c_str(), textColor);
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
        int tw, th;
        SDL_QueryTexture(tex, NULL, NULL, &tw, &tw);
        SDL_Rect tr = {50, 50, tw, th};
        SDL_RenderCopy(renderer, tex, NULL, &tr);
        SDL_FreeSurface(surf);
        SDL_DestroyTexture(tex);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}