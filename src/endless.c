/*
** EPITECH PROJECT, 2024
** endless.c
** File description:
** The functions for the endless mode.
*/
#include "hunter.h"

static int sprite_hitbox(project_t *endless, sprite_t *s,
    sfMouseButtonEvent event, int ic)
{
    sfFloatRect position = sfSprite_getGlobalBounds(s->sprite);

    sfSound_setPitch(endless->clicked->sound, randfloat(0.9, 1.1));
    if (ic >= 1) {
        return ic;
    }
    if (sfFloatRect_contains(&position, event.x, event.y)) {
        endless->catched += 1;
        sfSound_play(endless->clicked->sound);
        if (randint(1, 2) == 1) {
            sfSprite_setPosition(s->sprite,
            (sfVector2f){randint(100, 1600), 1100});
        } else {
            sfSprite_setPosition(s->sprite,
                (sfVector2f){randint(100, 1600), -150});
        }
        ic += 1;
    }
    return ic;
}

static void manage_mouse_click(project_t *endl, sfMouseButtonEvent event,
    menu_t *set)
{
    int ic = 0;

    if (endl->time >= 30) {
        ic = sprite_hitbox(endl, endl->yellow_butterfly, event, ic);
        ic = sprite_hitbox(endl, endl->white_butterfly, event, ic);
        ic = sprite_hitbox(endl, endl->red_butterfly, event, ic);
        ic = sprite_hitbox(endl, endl->pink_butterfly, event, ic);
        ic = sprite_hitbox(endl, endl->grey_butterfly, event, ic);
        ic = sprite_hitbox(endl, endl->blue_butterfly, event, ic);
    }
    set->ca = 2;
}

void analyse_events_endless(project_t *endless, sfEvent event,
    menu_t *settings)
{
    while (sfRenderWindow_pollEvent(endless->window, &event)) {
        if (event.type == sfEvtMouseButtonPressed) {
            manage_mouse_click(endless, event.mouseButton, settings);
            pause_button(endless, event.mouseButton, settings);
        }
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(endless->window);
            settings->stop = 20;
        }
        if (settings->mode_chosen == 2 && endless->real_time <= 0) {
            settings->stop = 1;
        }
    }
}
