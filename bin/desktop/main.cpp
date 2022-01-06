#include <iostream>
#include <SDL.h>

/**
 * Entry point of the launcher
 * @param argc The number of arguments passed to this process
 * @param argv The list of arguments passed to this process
 * @return the exit code of the process
 */
int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        std::cerr << "Failed to initialize SDL2" << std::endl;
        return 1;
    }

    std::cout << "Hello world!" << std::endl;
    SDL_Window* main_window = SDL_CreateWindow("Hello world", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    bool running = true;
    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }
        }
    }

    SDL_DestroyWindow(main_window);

    SDL_Quit();

    return 0;
}