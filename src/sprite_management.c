/*
** EPITECH PROJECT, 2024
** sprite_management.c
** File description:
** The functions for the sprite management.
*/
#include "hunter.h"

static void move_rect_top(sfIntRect *rect, int offset, int max_value)
{
    if ((rect->top + offset) < max_value) {
        rect->top = (rect->top + offset);
    } else {
        rect->top = 0;
    }
}

static void move_rect_left(sfIntRect *rect, int offset, int max_value)
{
    if ((rect->left + offset) < max_value) {
        rect->left = (rect->left + offset);
    } else {
        rect->left = 0;
    }
}

static int velocity_calculate(sprite_t *sprite)
{
    int nb = randint(1, 2);

    if (nb == 1) {
        sprite->rect.top = 0;
        return (-1);
    } else {
        sprite->rect.top = 16;
        return 1;
    }
}

sprite_t *create_sprite(sfVector2f pos, sfIntRect rect,
    char *texture_path, sfVector2f rect_depl)
{
    sprite_t *new_sprite = malloc(sizeof(sprite_t));

    new_sprite->texture = sfTexture_createFromFile(texture_path, NULL);
    new_sprite->sprite = sfSprite_create();
    new_sprite->pos = pos;
    new_sprite->rect = rect;
    new_sprite->rect_depl = rect_depl;
    sfSprite_setTexture(new_sprite->sprite, new_sprite->texture, sfTrue);
    sfSprite_setPosition(new_sprite->sprite, pos);
    sfSprite_setTextureRect(new_sprite->sprite, rect);
    new_sprite->velocity.x = velocity_calculate(new_sprite);
    new_sprite->velocity.y = 1;
    new_sprite->hide = 0;
    new_sprite->scale = (sfVector2f){1, 1};
    return new_sprite;
}

static void change_pos(sprite_t *sprite)
{
    sfVector2f pos = sfSprite_getPosition(sprite->sprite);

    if (randint(1, 35) == 1) {
        sprite->velocity.x = sprite->velocity.x * (-1);
        move_rect_top(&(sprite->rect), 16, 32);
    }
    if (pos.x > 1700) {
        sprite->rect.top = 0;
        sprite->velocity.x = (-1);
    } else if (pos.x < 100) {
        sprite->rect.top = 16;
        sprite->velocity.x = 1;
    }
    if (pos.y < 10) {
        sprite->velocity.y = 1;
    } else if (pos.y > 850) {
        sprite->velocity.y = (-1);
    }
}

void set_animation(project_t *hunter, sprite_t *sprite, menu_t *settings)
{
    int smi = 0;
    int sma = 1;

    if (sprite->hide == 1) {
        return;
    }
    speed_set(&smi, &sma, settings, sprite);
    change_pos(sprite);
    sfSprite_setTextureRect(sprite->sprite, sprite->rect);
    move_rect_left(&(sprite->rect), sprite->rect_depl.x, sprite->rect_depl.y);
    if (hunter->time >= 30) {
        sfSprite_move(sprite->sprite, (sfVector2f){randint(1, 25) *
            sprite->velocity.x, randint(smi, sma) * sprite->velocity.y});
    } else {
        sfSprite_move(sprite->sprite, (sfVector2f){randint(1, 25) *
            sprite->velocity.x, (randint(smi, sma) * sprite->velocity.y) * 3});
    }
}

void sprite_move(sfRenderWindow *window, sprite_t *sprite,
    sfVector2f pos, sfVector2f max)
{
    sfVector2f position = sfSprite_getPosition(sprite->sprite);

    if (sprite->velocity.y == 1) {
        sfSprite_move(sprite->sprite, pos);
    } else {
        sfSprite_move(sprite->sprite, (sfVector2f){pos.x * (-1),
            pos.y * (-1)});
    }
    sfRenderWindow_drawSprite(window, sprite->sprite, NULL);
    if (position.y > max.y) {
        sprite->velocity.y = (-1);
    } else if (position.y < max.x) {
        sprite->velocity.y = 1;
    }
}

void set_animation_fir(project_t *hunter, firef_t *fir, menu_t *settings)
{
    set_animation(hunter, fir->firefly1, settings);
    set_animation(hunter, fir->firefly2, settings);
    set_animation(hunter, fir->firefly3, settings);
    set_animation(hunter, fir->firefly4, settings);
    set_animation(hunter, fir->firefly5, settings);
    sprite_move(hunter->window, hunter->pause, (sfVector2f){0, 1},
        (sfVector2f){65, 75});
}

static void reset_sprite(sfVector2f new_pos, sprite_t *sprite)
{
    sfSprite_setPosition(sprite->sprite, (sfVector2f){new_pos.x,
                    new_pos.y});
    sprite->velocity.x = 1;
    sprite->velocity.y = 1;
    sprite->pos = new_pos;
}

static int sprite_position_reset(sfVector2f pos_max, sfVector2f new_pos,
    sfVector2f positivity, sprite_t *sprite)
{
    sfVector2f pos = sfSprite_getPosition(sprite->sprite);

    if (positivity.x == 1 && positivity.y == 1 &&
        pos.x > pos_max.x && pos.y > pos_max.y) {
        reset_sprite(new_pos, sprite);
    } else if (positivity.x == -1 && positivity.y == 1 &&
        pos.x < pos_max.x && pos.y > pos_max.y) {
        reset_sprite(new_pos, sprite);
    }
    if (positivity.x == 1 && positivity.y == -1 &&
        pos.x > pos_max.x && pos.y < pos_max.y) {
        reset_sprite(new_pos, sprite);
    } else if (positivity.x == -1 && positivity.y == -1 &&
        pos.x < pos_max.x && pos.x < pos_max.y) {
        reset_sprite(new_pos, sprite);
    }
}
