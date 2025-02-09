/*
** EPITECH PROJECT, 2024
** menu_file.c
** File description:
** The file for the menu functions.
*/
#include "hunter.h"

void change_mode(menu_t *menu)
{
    sfTexture *texture;

    switch (menu->mode_chosen) {
    case 1:
        texture = sfTexture_createFromFile("src/images/frames/TimeTrial.png",
            NULL);
        break;
    case 2:
        texture = sfTexture_createFromFile("src/images/frames/Rush30.png", NULL);
        break;
    case 3:
        texture = sfTexture_createFromFile("src/images/frames/Endless.png",
            NULL);
        break;
    }
    sfSprite_setTexture(menu->mode->sprite, texture, sfTrue);
}

void change_dif(menu_t *menu)
{
    sfTexture *texture;

    sfSprite_setTextureRect(menu->difficulty->sprite, (sfIntRect)
        {0, 0, 128, 64});
    switch (menu->difficulty_chosen) {
    case 1:
        texture = sfTexture_createFromFile("src/images/frames/Eric2.png",
            NULL);
        sfSprite_setTextureRect(menu->difficulty->sprite, (sfIntRect)
            {0, 0, 128, 90});
        break;
    case 2:
        texture = sfTexture_createFromFile("src/images/frames/Normal.png", NULL);
        break;
    case 3:
        texture = sfTexture_createFromFile("src/images/frames/Hard.png",
            NULL);
        break;
    }
    sfSprite_setTexture(menu->difficulty->sprite, texture, sfTrue);
}

static void move_text(menu_t *menu, text_t *text, sfVector2f bornes)
{
    sfVector2f position = sfText_getPosition(text->text);

    sfText_move(text->text, (sfVector2f){0.016 *
        text->velocity.x, 0.0833 *
        text->velocity.y});
    sfRenderWindow_drawText(menu->window, text->text, NULL);
    if (position.y > bornes.y) {
        text->velocity.y = (-1);
        text->velocity.x = (-1);
    } else if (position.y < bornes.x) {
        text->velocity.y = 1;
        text->velocity.x = 1;
    }
}

static void move_arrows3(menu_t *menu)
{
    move_text(menu, menu->score_save, (sfVector2f){910, 925});
    move_text(menu, menu->score_showt, (sfVector2f){45, 60});
    move_text(menu, menu->pseudo_d, (sfVector2f){350, 365});
    move_text(menu, menu->yourname, (sfVector2f){295, 305});
    if (menu->score_show == 1) {
        move_text(menu, menu->score_list, (sfVector2f){295, 300});
    }
}

static void move_arrows2(menu_t *menu)
{
    sprite_move(menu->window, menu->clickable, (sfVector2f){0, 0.083333},
        (sfVector2f){910, 925});
    sprite_move(menu->window, menu->generate, (sfVector2f){0, 0.083333},
        (sfVector2f){295, 305});
    sprite_move(menu->window, menu->clickable2, (sfVector2f){0, 0.083333},
        (sfVector2f){45, 60});
    if (menu->score_show == 1) {
        sprite_move(menu->window, menu->tri, (sfVector2f){0, 0.083333},
        (sfVector2f){205, 220});
        sprite_move(menu->window, menu->change, (sfVector2f){0, 0.083333},
        (sfVector2f){145, 160});
    }
    move_arrows3(menu);
}

void move_arrows(menu_t *menu)
{
    sprite_move(menu->window, menu->logo, (sfVector2f){0, 0.083333},
        (sfVector2f){70, 75});
    sprite_move(menu->window, menu->arrow1, (sfVector2f){0, 0.333},
        (sfVector2f){385, 415});
    sprite_move(menu->window, menu->arrow2, (sfVector2f){0, 0.333},
        (sfVector2f){385, 415});
    sprite_move(menu->window, menu->arrow3, (sfVector2f){0, 0.333},
        (sfVector2f){585, 615});
    sprite_move(menu->window, menu->arrow4, (sfVector2f){0, 0.333},
        (sfVector2f){585, 615});
    sprite_move(menu->window, menu->play_b, (sfVector2f){0, 0.083333},
        (sfVector2f){795, 805});
    sprite_move(menu->window, menu->mode, (sfVector2f){0, 0.166666},
        (sfVector2f){370, 390});
    sprite_move(menu->window, menu->difficulty, (sfVector2f){0, 0.166666},
        (sfVector2f){570, 590});
    sprite_move(menu->window, menu->quit_b, (sfVector2f){0, 0.083333},
        (sfVector2f){895, 905});
    move_arrows2(menu);
}

void speed_set(int *smi, int *sma, menu_t *settings, sprite_t *sprite)
{
    if (randint(1, 35) == 1) {
        sprite->velocity.y = sprite->velocity.y * (-1);
    }
    if (settings->difficulty_chosen == 1) {
        *smi = 1;
        *sma = 5;
    } else if (settings->difficulty_chosen == 2) {
        *smi = 15;
        *sma = 25;
    }
    if (settings->difficulty_chosen == 3) {
        *smi = 25;
        *sma = 45;
    }
}

static void restart_cursor(menu_t *menu)
{
    float rotation = sfSprite_getRotation(menu->cursor->sprite);

    if (menu->ca == 0 && rotation != 0) {
        if (rotation < 361 && rotation > 180) {
            sfSprite_rotate(menu->cursor->sprite, 1);
        }
        if (rotation > 0 && rotation <= 180) {
            sfSprite_rotate(menu->cursor->sprite, -1);
        }
    }
}

void draw_cursor(menu_t *menu)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(menu->window);
    sfVector2f scale = sfSprite_getScale(menu->cursor->sprite);

    if (scale.x >= 1.16) {
        menu->cursor->velocity.x *= -1;
        menu->ca = 1;
    } else if (scale.x <= 1 && menu->ca != 2) {
        menu->ca = 0;
    }
    if (menu->ca >= 2) {
        sfSprite_scale(menu->cursor->sprite, (sfVector2f){1.02, 1.02});
        sfSprite_rotate(menu->cursor->sprite, menu->cursor->velocity.x);
    } else if (menu->ca == 1) {
        sfSprite_scale(menu->cursor->sprite, (sfVector2f){0.98, 0.98});
        sfSprite_rotate(menu->cursor->sprite, menu->cursor->velocity.x);
    }
    restart_cursor(menu);
    sfSprite_setPosition(menu->cursor->sprite, (sfVector2f)
        {pos.x - 1, pos.y - 1});
    sfRenderWindow_drawSprite(menu->window, menu->cursor->sprite, NULL);
}
