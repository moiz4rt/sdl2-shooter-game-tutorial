#include "draw.h"
#include "common.h"
#include "structs.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void prepareScene(void) {
    SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
    SDL_RenderClear(app.renderer);
}

void presentScene(void) {
    SDL_RenderPresent(app.renderer);
}

SDL_Texture *loadTexture(char *filename) {
    SDL_Texture *texture;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    texture = IMG_LoadTexture(app.renderer, filename);

    return texture;
}

void blit(SDL_Texture *texture, int x, int y, int w, int h) {
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;

    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void renderTextureRotated(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h, double angle) {
    SDL_Rect destRect = {x, y, w, h};

    SDL_RenderCopyEx(renderer, texture, NULL, &destRect, angle, NULL, SDL_FLIP_NONE);
}
