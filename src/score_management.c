/*
** EPITECH PROJECT, 2024
** score_management.c
** File description:
** The functions for the score management.
*/
#include "hunter.h"

void score_management(project_t *hunter, menu_t *settings)
{
    char const *text;

    if (hunter->time >= 30) {
        if (settings->mode_chosen == 1 || settings->mode_chosen == 2) {
            text = my_float_to_str(hunter->real_time);
        } else {
            text = my_float_to_str(hunter->time - 30);
        }
        if (hunter->time == 10) {
            sfText_setPosition(hunter->time_d->text, (sfVector2f){740, 941});
        }
        if (hunter->time == 130) {
            sfText_setPosition(hunter->time_d->text, (sfVector2f){725, 941});
        }
        if (hunter->time == 1030) {
            sfText_setPosition(hunter->time_d->text, (sfVector2f){715, 941});
        }
        sfText_setString(hunter->time_d->text, text);
        sfRenderWindow_drawText(hunter->window, hunter->time_d->text, NULL);
    }
}

void display_catched(project_t *hun)
{
    char *text = my_int_to_str(hun->catched);

    if (hun->time >= 30) {
        if (hun->catched == 10) {
            sfText_setPosition(hun->catched_d->text, (sfVector2f){1720, 950});
        }
        if (hun->catched == 100) {
            sfText_setPosition(hun->catched_d->text, (sfVector2f){1710, 950});
        }
        if (hun->catched == 1000) {
            sfText_setPosition(hun->catched_d->text, (sfVector2f){1700, 950});
        }
        sfText_setString(hun->catched_d->text, text);
        sfRenderWindow_drawText(hun->window, hun->catched_d->text, NULL);
    }
    free(text);
}

void set_ready(project_t *hunter)
{
    sfTexture *textr = sfTexture_createFromFile("src/images/RGo.png", NULL);

    if (hunter->time < 20) {
        sfRenderWindow_drawSprite(hunter->window, hunter->ready->sprite, NULL);
    } else if (hunter->time < 30) {
        sfSprite_setTexture(hunter->ready->sprite, textr, sfTrue);
        sfSprite_setPosition(hunter->ready->sprite, (sfVector2f)
            {600, 290});
        sfRenderWindow_drawSprite(hunter->window, hunter->ready->sprite, NULL);
    }
    sfTexture_destroy(textr);
}

static void button_hitbox2_2(menu_t *menu, int nb)
{
    if (nb == 4) {
        if (menu->difficulty_chosen <= 1) {
            sfSound_setPitch(menu->clicked->sound, 0.5);
            menu->difficulty_chosen = 1;
        } else {
            sfSound_setPitch(menu->clicked->sound, randfloat(0.9, 1.1));
            menu->difficulty_chosen--;
        }
    }
    if (nb == 5) {
        if (menu->difficulty_chosen >= 3) {
            sfSound_setPitch(menu->clicked->sound, 0.5);
            menu->difficulty_chosen = 3;
        } else {
            sfSound_setPitch(menu->clicked->sound, randfloat(0.9, 1.1));
            menu->difficulty_chosen++;
        }
    }
}

void button_hitbox2(menu_t *menu, int nb)
{
    if (nb == 2) {
        sfSound_setPitch(menu->clicked->sound, randfloat(0.9, 1.1));
        if (menu->mode_chosen <= 1) {
            menu->mode_chosen = 3;
        } else {
            menu->mode_chosen--;
        }
    }
    if (nb == 3) {
        sfSound_setPitch(menu->clicked->sound, randfloat(0.9, 1.1));
        if (menu->mode_chosen >= 3) {
            menu->mode_chosen = 1;
        } else {
            menu->mode_chosen++;
        }
    }
    button_hitbox2_2(menu, nb);
    sfSound_play(menu->clicked->sound);
}

int my_get_nbr(char const *str)
{
    int i = 0;
    int res = 0;
    int is_neg = 1;

    while (!(str[i] >= 48 && str[i] <= 57)) {
        if (str[i] == 45) {
            is_neg = is_neg * (-1);
        }
        i++;
    }
    while (str[i] >= 48 && str[i] <= 57) {
        res = res * 10 + (str[i] - 48);
        i++;
    }
    res = res * is_neg;
    return res;
}
