/*
** EPITECH PROJECT, 2024
** sprite_management2.c
** File description:
** The second file for the sprite management.
*/
#include "hunter.h"

static void draw(project_t *hunter, sprite_t *sprite)
{
    sfRenderWindow_drawSprite(hunter->window, sprite->sprite, NULL);
}

void draw_butterflies(project_t *hunter, firef_t *fir)
{
    draw(hunter, hunter->blue_butterfly);
    draw(hunter, hunter->grey_butterfly);
    draw(hunter, hunter->pink_butterfly);
    draw(hunter, hunter->red_butterfly);
    draw(hunter, hunter->white_butterfly);
    draw(hunter, hunter->yellow_butterfly);
    draw(hunter, fir->firefly1);
    draw(hunter, fir->firefly2);
    draw(hunter, fir->firefly3);
    draw(hunter, fir->firefly4);
    draw(hunter, fir->firefly5);
    draw(hunter, hunter->pause);
}

void animate_butterflies(project_t *hunter, firef_t *fir,
    menu_t *settings)
{
    set_animation(hunter, hunter->blue_butterfly, settings);
    set_animation(hunter, hunter->grey_butterfly, settings);
    set_animation(hunter, hunter->pink_butterfly, settings);
    set_animation(hunter, hunter->red_butterfly, settings);
    set_animation(hunter, hunter->white_butterfly, settings);
    set_animation(hunter, hunter->yellow_butterfly, settings);
    set_animation_fir(hunter, fir, settings);
}

void transition(menu_t *menu, int *t)
{
    if (menu->stopped == 0 && menu->BlR->velocity.x > 20) {
        sfSprite_setColor(menu->BlR->sprite, (sfColor){255, 255, 255,
        menu->BlR->velocity.x});
        menu->BlR->velocity.x -= 2;
    }
    if (menu->stopped == 1) {
        if (menu->BlR->velocity.x < 250) {
            menu->BlR->velocity.x += 2;
            sfSprite_setColor(menu->BlR->sprite, (sfColor){255, 255, 255,
            menu->BlR->velocity.x});
        } else {
            menu->stop = 1;
        }
    }
}

static char *my_final_boss_score(player_t *players, int sort)
{
    char *result = malloc(sizeof(char) * 1);

    result[0] = '\0';
    if (players[0].nb >= 10) {
        players[0].nb = 10;
    }
    for (int i = 0; i < players[0].nb; i++) {
        result = my_sec_strcat(result, put_in_char(players, i, sort));
    }
    return result;
}

void display_scores(menu_t *menu, int sort)
{
    player_t *players = load_data();

    my_sort_players(players, players[0].nb, sort);
    my_sort_players(players, players[0].nb, 4);
    sfText_setString(menu->score_list->text,
        my_final_boss_score(players, sort));
    free(players);
}
