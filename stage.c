#include "stage.h"
#include "common.h"
#include "structs.h"
#include "defs.h"
#include "draw.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>

static Stage stage;
static void initPlayer(void);
static void logic(void);
static void doPlayer(void);
static void fireBullet(void);
static void doBullets(void);
static void draw(void);
static void drawPlayer(void);
static void drawBullets(void);

SDL_Texture *bulletTexture;
extern Entity *player;

void initStage(void) {
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(&stage, 0, sizeof(Stage));
    stage.fighterTail = &stage.fighterHead;
    stage.bulletTail = &stage.bulletHead;

    initPlayer();

    bulletTexture = loadTexture("gfx/bullet.png");
}

static void initPlayer()
{
    player = malloc(sizeof(Entity));
    if (!player) {                    // Verifica se a memória foi alocada corretamente
        printf("Erro ao alocar memória para o jogador!\n");
        exit(1);
    }
    memset(player, 0, sizeof(Entity));

    stage.fighterTail->next = player;
    stage.fighterTail = player;

    player->x = 100;
    player->y = 100;
    player->w = 50;
    player->h = 50;
    player->texture = loadTexture("gfx/player.png");
}

static void logic(void)
{
    doPlayer();

    doBullets();
}

static void doPlayer(void)
{
    player->dx = player->dy = 0;

    if(player->reload > 0)
    {
        player->reload--;
    }

    if(app.keyboard[SDL_SCANCODE_UP])
    {
        player->dy = -PLAYER_SPEED;
    }

    if(app.keyboard[SDL_SCANCODE_DOWN])
    {
        player->dy = PLAYER_SPEED;
    }

    if(app.keyboard[SDL_SCANCODE_LEFT])
    {
        player->dx = -PLAYER_SPEED;
    }

    if(app.keyboard[SDL_SCANCODE_LEFT])
    {
        player->dx = PLAYER_SPEED;
    }

    if(app.keyboard[SDL_SCANCODE_LCTRL] && player->reload == 0)
    {
        fireBullet();
    }

    player->x += player->dx;
    player->y += player->dy;
}

static void fireBullet(void)
{
    Entity *bullet;

    bullet = malloc(sizeof(Entity));
    memset(bullet, 0, sizeof(Entity));
    stage.bulletTail->next = bullet;
    stage.bulletTail = bullet;

    bullet->x = player->x;
    bullet->y = player->y;
    bullet->dx = BULLET_SPEED;
    bullet->health = 1;
    bullet->texture = bulletTexture;
    bullet->w = 25;
    bullet->h = 25;

    bullet->y += (player->h / 2) - (bullet->h/ 2);

    player->reload = 8;
}

static void doBullets(void)
{
    Entity *b, *prev;

    prev = &stage.bulletHead;

    for(b = stage.bulletHead.next;b != NULL;b = b->next)
    {
        b->x += b->dx;
        b->y += b->dy;

        if(b->x > SCREEN_WIDTH)
        {
            if(b == stage.bulletTail)
            {
                stage.bulletTail = prev;
            }

            prev->next = b->next;
            free(b);
            b = prev;
        }

        prev = b;
    }
}

static void draw(void)
{
    drawPlayer();

    drawBullets();
}

static void drawPlayer(void)
{
    blit(player->texture, player->x, player->y, player->w, player->h);
}

static void drawBullets(void)
{
    Entity *b;

    for(b = stage.bulletHead.next;b != NULL;b = b->next)
    {
        blit(b->texture, b->x, b->y, b->w, b->h);
    }
}
