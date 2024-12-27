#ifndef DRAW_H
#define DRAW_H

#include "common.h"
#include <SDL2/SDL_image.h>

void prepareScene(void);
void presentScene(void);
SDL_Texture *loadTexture(char *filename);
void blit(SDL_Texture *texture, int x, int y, int w, int h);
void renderTextureRotated(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h, double angle);

#endif
