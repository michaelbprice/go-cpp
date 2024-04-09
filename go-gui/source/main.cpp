#include "SDL2/SDL.h"


namespace /* private */ {

struct MyInit
{
    MyInit (const MyInit &) = delete;
    MyInit & operator= (const MyInit &) = delete;
    MyInit (MyInit &&) = delete;
    MyInit & operator= (MyInit &&) = delete;
    
    SDL_Window* window = nullptr;
    bool init_error = false;

    MyInit ()
    {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        {
            init_error = true;
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init: %s", SDL_GetError());
            return;
        }

        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        window = SDL_CreateWindow("Dear ImGui SDL2 example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);

        if (window == nullptr)
        {
            init_error = true;
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error: SDL_CreateWindow(): %s\n", SDL_GetError());
            return;
        }
    }

    ~MyInit ()
    {
        if (window)
        {
            window = nullptr;
        }
    }
};

}

int main(int argc, char* argv[]) {
    MyInit init;
    if (init.init_error) { return -1;}  

    bool keepRunning = true;
    while (keepRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event) > 0)
        {
            switch (event.type)
            {
             case SDL_QUIT:
                keepRunning = false;
                break;

             case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(init.window))
                {
                    keepRunning = false;
                }
                break;

             default:
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Unhandled Event: %d", event.type);
            }
        }
    }
}