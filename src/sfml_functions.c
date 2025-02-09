/*
** EPITECH PROJECT, 2024
** sfml_functions.c
** File description:
** Functions for the good usage of sfml.
*/
#include "hunter.h"

text_t *create_text(char *str, sfVector2f pos, unsigned int size,
    char const *police)
{
    text_t *new_text = malloc(sizeof(text_t));

    new_text->font = sfFont_createFromFile(police);
    new_text->text = sfText_create();
    new_text->size = size;
    new_text->pos = pos;
    new_text->velocity = (sfVector2f){1, 1};
    sfText_setFont(new_text->text, new_text->font);
    sfText_setString(new_text->text, str);
    sfText_setCharacterSize(new_text->text, new_text->size);
    sfText_setPosition(new_text->text, pos);
    return new_text;
}

int wait(int tm, float t)
{
    sfClock *clock;
    sfTime time;
    float seconds = 0.0;

    clock = sfClock_create();
    while (seconds < t) {
        time = sfClock_getElapsedTime(clock);
        seconds = time.microseconds / 1000000.0;
    }
    sfClock_destroy(clock);
    return tm + 1;
}

static void free_sprite(sprite_t *sprite)
{
    sfTexture_destroy(sprite->texture);
    sfSprite_destroy(sprite->sprite);
    free(sprite);
}

void my_free_project(project_t *hunter, firef_t *fir)
{
    sfRenderWindow_destroy(hunter->window);
    free_sprite(hunter->blue_butterfly);
    free_sprite(hunter->grey_butterfly);
    free_sprite(hunter->pink_butterfly);
    free_sprite(hunter->red_butterfly);
    free_sprite(hunter->white_butterfly);
    free_sprite(hunter->yellow_butterfly);
    free_sprite(hunter->bck);
    free_sprite(hunter->ready);
    sfText_destroy(hunter->time_d->text);
    free_sprite(hunter->pause);
    free(hunter);
}

int randint(int min, int max)
{
    int temp;
    int random_nbr;

    if (min > max) {
        temp = min;
        min = max;
        max = temp;
    }
    random_nbr = min + rand() % (max - min + 1);
    return random_nbr;
}

static void my_menu_free_2(menu_t *settings)
{
    free_sprite(settings->generate);
    free(settings->name);
    free(settings->lastname);
    free(settings);
}

void my_menu_free(menu_t *settings)
{
    free_sprite(settings->arrow1);
    free_sprite(settings->arrow2);
    free_sprite(settings->arrow3);
    free_sprite(settings->arrow4);
    free_sprite(settings->mode);
    free_sprite(settings->difficulty);
    free_sprite(settings->bg);
    free_sprite(settings->play_b);
    free_sprite(settings->cursor);
    free_sprite(settings->frame_s);
    free_sprite(settings->w_but_s);
    free_sprite(settings->logo);
    free_sprite(settings->clickable);
    sfText_destroy(settings->stats_w->text);
    sfText_destroy(settings->stats_b->text);
    sfText_destroy(settings->score_save->text);
    sfText_destroy(settings->pseudo_d->text);
    my_menu_free_2(settings);
}
