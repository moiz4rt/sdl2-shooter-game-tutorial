#include "init.h"
#include "common.h"
#include "defs.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void initSDL(void) {
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    app.window = SDL_CreateWindow("Shooter 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

    if(!app.window) {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

    if(!app.renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        printf("Failed to initialize IMG: %s\n", IMG_GetError());
        exit(1);
    }
}

void cleanup(void) {
    if(app.renderer) {
        SDL_DestroyRenderer(app.renderer);
        app.renderer = NULL;
    }
    if(app.window) {
        SDL_DestroyWindow(app.window);
        app.window = NULL;
    }

    IMG_Quit();
    SDL_Quit();
}
