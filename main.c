#include "common.h"
#include "defs.h"
#include "structs.h"
#include "input.h"
#include "init.h"
#include "draw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

App app;
Entity player;
Entity bullet;

int main(int argc, char *argv[]) {

    memset(&app, 0, sizeof(App));
    memset(&player, 0, sizeof(Entity));
    memset(&bullet, 0, sizeof(Entity));

    initSDL();

    atexit(cleanup);

    player.x = 100;
    player.y = 100;
    player.w = 50;
    player.h = 50;
    player.texture = loadTexture("gfx/player.png");

    bullet.texture = loadTexture("gfx/bullet.png");
    bullet.w = BULLET_W;
    bullet.h = BULLET_H;


    while(1) {
        prepareScene();

        doInput();

        if(app.up)
        {
            player.y -= PLAYER_SPEED_Y;
        }

        if(app.down)
        {
            player.y += PLAYER_SPEED_Y;
        }

        if(app.left)
        {
            player.x -= PLAYER_SPEED_X;
        }

        if(app.right)
        {
            player.x += PLAYER_SPEED_X;
        }

        if(player.x < 0) player.x = 0;
        if(player.y < 0) player.y = 0;
        if(player.x + player.w > SCREEN_WIDTH) player.x = SCREEN_WIDTH - player.w;
        if(player.y + player.h > SCREEN_HEIGHT) player.y = SCREEN_HEIGHT - player.h;

        if(app.fire && bullet.health == 0)
        {
            bullet.x = player.x + player.w / 2;
            bullet.y = player.y + player.h / 2;
            bullet.dx = 16;
            bullet.dy = 0;
            bullet.health = 1;
        }

        bullet.x += bullet.dx;
        bullet.y += bullet.dy;

        if(bullet.x > SCREEN_WIDTH)
        {
            bullet.health = 0;
        }

        blit(player.texture, player.x, player.y, player.w, player.h);

        if(bullet.health > 0) {
            renderTextureRotated(bullet.texture, app.renderer, bullet.x, bullet.y, bullet.w, bullet.h, 90);
        }
        presentScene();

        SDL_Delay(16);
    }

    return 0;
}
