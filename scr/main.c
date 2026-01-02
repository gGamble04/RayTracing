#include "raytracing.h"

int main() 
{
    // Initialize SDL 
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { 
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError()); // Log SDL initialization error
        return 1;
    }
    SDL_Window *windowPtr = SDL_CreateWindow("Ray Tracing Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if (!windowPtr) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError()); // Log window creation error
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *rendererPtr = SDL_CreateRenderer(windowPtr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!rendererPtr) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError()); // Log renderer creation error
        SDL_DestroyWindow(windowPtr);
        SDL_Quit();
        return 1;
    }

    // Define circle and objects
    Circle circle = {
        .center = (Vect2D){WIDTH / 2, HEIGHT / 2},
        .radius = 40
    };
    Circle obstacle = {
        .center = (Vect2D){300, 200},
        .radius = 70
    };
    SDL_Rect clear_rect = {
        .x = 0,
        .y = 0,
        .w = WIDTH,
        .h = HEIGHT
    };
    
    // Event loop
    bool app_running = true;
    bool needs_redrawn = true; // Flag to track if redraw is needed
    SDL_Event event;
    while(app_running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    app_running = false;
                    break;

                case SDL_MOUSEMOTION:
                    if(event.button.button == SDL_BUTTON_LEFT)
                    {
                        circle.center = (Vect2D){event.motion.x, event.motion.y}; // Update circle center to mouse position
                        needs_redrawn = true;
                    }

            }
        }
        if(needs_redrawn) // Only redraw if needed, avoid unnecessary rendering
        {
            // Clear screen
            SetRenderDrawColor(rendererPtr, BLACK);
            SDL_RenderFillRect(rendererPtr, &clear_rect);
            // Draw objects
            DrawCircle(rendererPtr, obstacle, BLUE);
            DrawCircle(rendererPtr, circle, YELLOW);
            GenerateRays(rendererPtr, circle, 400, obstacle, LIGHT); 
            SDL_RenderPresent(rendererPtr);
            needs_redrawn = false;
        }
        SDL_Delay(16); // Roughly 60 FPS

    }
    // Cleanup
    SDL_DestroyRenderer(rendererPtr);
    SDL_DestroyWindow(windowPtr);
    SDL_Quit();
    return 0;
}