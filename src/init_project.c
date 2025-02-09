/*
** EPITECH PROJECT, 2024
** init_project.c
** File description:
** Functions to init the project.
*/
#include "hunter.h"

static void scale_butterfly(sprite_t *sprite)
{
    float nb = randint(5, 7);

    sfSprite_setScale(sprite->sprite, (sfVector2f){nb, nb});
}

static void init_project_3(project_t *my_hunter, menu_t *settings)
{
    my_hunter->pause = create_sprite((sfVector2f){1720, 50},
        (sfIntRect){0, 0, 64, 64}, "src/images/frames/P.png",
        (sfVector2f){0, 0});
    sfText_setScale(my_hunter->time_d->text, (sfVector2f){1.1, 1.1});
    my_hunter->clicked = create_sound("src/musics/pop.ogg", 40);
    my_hunter->time_gain = 7;
    my_hunter->BlR = create_sprite((sfVector2f){0, 0},
        (sfIntRect){0, 0, 1792, 1024}, "src/images/black.png", (sfVector2f){0, 0});
    my_hunter->BlR->velocity.x = 255;
}

void init_scale_butterfly(project_t *my_hunter, menu_t *settings)
{
    scale_butterfly(my_hunter->blue_butterfly);
    scale_butterfly(my_hunter->grey_butterfly);
    scale_butterfly(my_hunter->pink_butterfly);
    scale_butterfly(my_hunter->red_butterfly);
    scale_butterfly(my_hunter->white_butterfly);
    scale_butterfly(my_hunter->yellow_butterfly);
    sfSprite_setScale(my_hunter->ready->sprite, (sfVector2f){3, 3});
    if (settings->mode_chosen == 2) {
        my_hunter->real_time = 330;
    } else if (settings->mode_chosen == 1) {
        my_hunter->real_time = 180;
    }
    my_hunter->catched = 0;
    my_hunter->catched_d = create_text("0",
        (sfVector2f){1720, 950}, 50, "src/polices/finalf.ttf");
    sfText_setFillColor(my_hunter->catched_d->text, (sfColor)
        {255, 255, 255, 255});
    my_hunter->timex6 = 0;
    init_project_3(my_hunter, settings);
}

void init_project_2(project_t *my_hunter, menu_t *settings)
{
    my_hunter->time_d = create_text("Score",
        (sfVector2f){730, 941}, 50, "src/polices/finalf.ttf");
    if (settings->mode_chosen == 1) {
        my_hunter->bck = create_sprite((sfVector2f){0, 0}, (sfIntRect)
            {0, 0, 1792, 1024}, "src/images/bck.png", (sfVector2f){0, 0});
    } else if (settings->mode_chosen == 2) {
        my_hunter->bck = create_sprite((sfVector2f){0, 0}, (sfIntRect)
            {0, 0, 1792, 1024}, "src/images/bck3.png", (sfVector2f){0, 0});
    }
    if (settings->mode_chosen == 3) {
        my_hunter->bck = create_sprite((sfVector2f){0, 0}, (sfIntRect)
            {0, 0, 1792, 1024}, "src/images/bck4.png", (sfVector2f){0, 0});
    }
    sfSprite_setColor(my_hunter->bck->sprite, (sfColor){200, 200, 200, 100});
    my_hunter->time = 0;
    my_hunter->ready = create_sprite((sfVector2f){600, 300},
        (sfIntRect){0, 0, 256, 128}, "src/images/R.png", (sfVector2f){0, 0});
    init_scale_butterfly(my_hunter, settings);
}

project_t *init_project_hunter(menu_t *settings)
{
    project_t *my_hunter = malloc(sizeof(project_t));

    my_hunter->window = settings->window;
    my_hunter->blue_butterfly = create_sprite((sfVector2f){900, 900},
        (sfIntRect){0, 0, 16, 16}, "src/images/b/Blue.png", (sfVector2f){16, 80});
    my_hunter->grey_butterfly = create_sprite((sfVector2f){900, 900},
        (sfIntRect){0, 16, 16, 16}, "src/images/b/Grey.png", (sfVector2f){16, 80});
    my_hunter->pink_butterfly = create_sprite((sfVector2f){900, 900},
        (sfIntRect){0, 32, 16, 16}, "src/images/b/Pink.png", (sfVector2f){16, 80});
    my_hunter->red_butterfly = create_sprite((sfVector2f){900, 900},
        (sfIntRect){0, 48, 16, 16}, "src/images/b/Red.png", (sfVector2f){16, 80});
    my_hunter->white_butterfly = create_sprite((sfVector2f){900, 900},
        (sfIntRect){0, 64, 16, 16}, "src/images/b/Whte.png", (sfVector2f){16, 80});
    my_hunter->yellow_butterfly = create_sprite((sfVector2f){900, 900},
        (sfIntRect){0, 16, 16, 16}, "src/images/b/Yelw.png", (sfVector2f){16, 80});
    init_project_2(my_hunter, settings);
    return my_hunter;
}

firef_t *init_fire_flies(void)
{
    firef_t *new_fir = malloc(sizeof(firef_t));

    new_fir->firefly1 = create_sprite((sfVector2f){randint(200, 1500), 300},
        (sfIntRect){0, 0, 16, 16}, "src/images/ff.png", (sfVector2f){16, 112});
    new_fir->firefly2 = create_sprite((sfVector2f){randint(200, 1500), 700},
        (sfIntRect){16, 0, 16, 16}, "src/images/ff.png", (sfVector2f){16, 112});
    new_fir->firefly3 = create_sprite((sfVector2f){randint(200, 1500), 400},
        (sfIntRect){32, 0, 16, 16}, "src/images/ff.png", (sfVector2f){16, 112});
    new_fir->firefly4 = create_sprite((sfVector2f){randint(200, 1500), 300},
        (sfIntRect){64, 0, 16, 16}, "src/images/ff.png", (sfVector2f){16, 112});
    new_fir->firefly5 = create_sprite((sfVector2f){randint(200, 1500), 500},
        (sfIntRect){112, 0, 16, 16}, "src/images/ff.png", (sfVector2f){16, 112});
    sfSprite_setScale(new_fir->firefly1->sprite, (sfVector2f){2, 2});
    sfSprite_setScale(new_fir->firefly2->sprite, (sfVector2f){2, 2});
    sfSprite_setScale(new_fir->firefly3->sprite, (sfVector2f){2, 2});
    sfSprite_setScale(new_fir->firefly4->sprite, (sfVector2f){2, 2});
    sfSprite_setScale(new_fir->firefly5->sprite, (sfVector2f){2, 2});
    return new_fir;
}
