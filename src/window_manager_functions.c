/*
** EPITECH PROJECT, 2024
** window_manager_functions.c
** File description:
** Functions that manages the window.
*/
#include "hunter.h"

sfRenderWindow *create_my_window(int width, int height, char *name)
{
    sfRenderWindow *window;
    sfVideoMode video_mode;

    video_mode.width = width;
    video_mode.height = height;
    video_mode.bitsPerPixel = 32;
    window = sfRenderWindow_create(video_mode,
                                name,
                                sfDefaultStyle,
                                NULL);
    sfRenderWindow_setPosition(window, (sfVector2i){300, 150});
    return window;
}

static void init_pause2(pause_t *pause, menu_t *settings)
{
    sfSprite_setColor(pause->bg->sprite, (sfColor){200, 200, 200, 100});
    pause->fg = create_sprite((sfVector2f){480, 150}, (sfIntRect)
        {0, 0, 864, 704}, "src/images/frames/Pbck.jpg", (sfVector2f){0, 0});
    pause->resume = create_sprite((sfVector2f){820, 300}, (sfIntRect)
        {0, 0, 128, 64}, "src/images/frames/res.png", (sfVector2f){0, 0});
    pause->lobby = create_sprite((sfVector2f){825, 450}, (sfIntRect)
        {0, 0, 128, 64}, "src/images/frames/menu.png", (sfVector2f){0, 0});
    pause->quit = create_sprite((sfVector2f){840, 600}, (sfIntRect)
        {0, 0, 160, 80}, "src/images/frames/Quit.png", (sfVector2f){0, 0});
    sfSprite_setScale(pause->resume->sprite, (sfVector2f){1.6, 1.6});
    sfSprite_setScale(pause->lobby->sprite, (sfVector2f){1.5, 1.5});
    sfSprite_setColor(pause->resume->sprite, (sfColor){255, 200, 200, 175});
    sfSprite_setColor(pause->lobby->sprite, (sfColor){255, 200, 200, 175});
    sfSprite_setColor(pause->quit->sprite, (sfColor){255, 200, 200, 175});
    pause->quit_nb = 0;
}

pause_t *init_pause(menu_t *settings)
{
    pause_t *pause = malloc(sizeof(pause_t));

    pause->stop = 0;
    if (settings->mode_chosen == 1) {
        pause->bg = create_sprite((sfVector2f){0, 0}, (sfIntRect)
            {0, 0, 1792, 1024}, "src/images/bck.png", (sfVector2f){0, 0});
    } else if (settings->mode_chosen == 2) {
        pause->bg = create_sprite((sfVector2f){0, 0}, (sfIntRect)
            {0, 0, 1792, 1024}, "src/images/bck3.png", (sfVector2f){0, 0});
    }
    if (settings->mode_chosen == 3) {
        pause->bg = create_sprite((sfVector2f){0, 0}, (sfIntRect)
            {0, 0, 1792, 1024}, "src/images/bck4.png", (sfVector2f){0, 0});
    }
    init_pause2(pause, settings);
    return pause;
}

static void free_sprite(sprite_t *sprite)
{
    sfTexture_destroy(sprite->texture);
    sfSprite_destroy(sprite->sprite);
    free(sprite);
}

void my_free_pause(pause_t *pause)
{
    free_sprite(pause->bg);
    free_sprite(pause->fg);
    free_sprite(pause->resume);
    free_sprite(pause->lobby);
    free_sprite(pause->quit);
    free(pause);
}

static void move_down(sfRenderWindow *w, sprite_t *s, sfVector2f pos, int nb)
{
    sfVector2f position = sfSprite_getPosition(s->sprite);

    if (nb == 1 && position.y < pos.x) {
        sfSprite_move(s->sprite, (sfVector2f){0, pos.y});
    } else if (nb == 2 && position.y > pos.x) {
        sfSprite_move(s->sprite, (sfVector2f){0, pos.y});
    }
    sfRenderWindow_drawSprite(w, s->sprite, NULL);
}

static void text_down(sfRenderWindow *w, text_t *t, sfVector2f pos, int nb)
{
    sfVector2f position = sfText_getPosition(t->text);

    if (nb == 1 && position.y < pos.x) {
        sfText_move(t->text, (sfVector2f){0, pos.y});
    } else if (nb == 2 && position.y > pos.x) {
        sfText_move(t->text, (sfVector2f){0, pos.y});
    }
    sfRenderWindow_drawText(w, t->text, NULL);
}

static void move_all(stat_t *stats, menu_t *menu, int *t)
{
    if (stats->tot_time < 30) {
        return;
    }
    if (menu->time <= 45) {
        move_down(menu->window, menu->frame_s, (sfVector2f){12, 3}, 1);
        move_down(menu->window, menu->w_but_s, (sfVector2f){32, 3}, 1);
        text_down(menu->window, menu->stats_b, (sfVector2f){35, 3}, 1);
        text_down(menu->window, menu->stats_w, (sfVector2f){38, 3}, 1);
    } else {
        move_down(menu->window, menu->frame_s, (sfVector2f){-155, -3}, 2);
        move_down(menu->window, menu->w_but_s, (sfVector2f){-130, -3}, 2);
        text_down(menu->window, menu->stats_b, (sfVector2f){-129, -3}, 2);
        text_down(menu->window, menu->stats_w, (sfVector2f){-126, -3}, 2);
    }
}

void draw_score_anim(stat_t *stats, menu_t *menu, int *t)
{
    char *txt = "You have captured ";

    txt = my_sec_strcat(txt, my_int_to_str(stats->catched));
    txt = my_sec_strcat(txt, "\nButterflies in ");
    txt = my_sec_strcat(txt, my_float_to_str(stats->tot_time));
    txt = my_sec_strcat(txt, "secs\n");
    sfText_setString(menu->stats_w->text, txt);
    sfText_setString(menu->stats_b->text, txt);
    if (*t == 6) {
        *t = 0;
        menu->time++;
        if ((menu->w_but_s->rect.left + 16) < 80) {
            menu->w_but_s->rect.left += 16;
        } else {
            menu->w_but_s->rect.left = 0;
        }
        sfSprite_setTextureRect(menu->w_but_s->sprite, menu->w_but_s->rect);
    }
    move_all(stats, menu, t);
}

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
