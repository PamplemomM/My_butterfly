/*
** EPITECH PROJECT, 2024
** pause.c
** File description:
** Function for the pause button.
*/
#include "hunter.h"

static void draw(project_t *hunter, sprite_t *sprite)
{
    sfRenderWindow_drawSprite(hunter->window, sprite->sprite, NULL);
}

static void draw_butterflies_pause(project_t *hunter)
{
    draw(hunter, hunter->blue_butterfly);
    draw(hunter, hunter->grey_butterfly);
    draw(hunter, hunter->pink_butterfly);
    draw(hunter, hunter->red_butterfly);
    draw(hunter, hunter->white_butterfly);
    draw(hunter, hunter->yellow_butterfly);
    draw(hunter, hunter->BlR);
}

static void render_pause_button(project_t *hunter, menu_t *settings,
    pause_t *pause)
{
    firef_t *fir = init_fire_flies();

    sfRenderWindow_drawSprite(hunter->window, pause->bg->sprite, NULL);
    draw_butterflies_pause(hunter);
    sfRenderWindow_drawSprite(hunter->window, pause->fg->sprite, NULL);
    sprite_move(settings->window, pause->fg, (sfVector2f){0, 0.08333},
        (sfVector2f){140, 150});
    sprite_move(settings->window, pause->resume, (sfVector2f){0, 0.08333},
        (sfVector2f){295, 305});
    sprite_move(settings->window, pause->lobby, (sfVector2f){0, 0.08333},
        (sfVector2f){445, 455});
    sprite_move(settings->window, pause->quit, (sfVector2f){0, 0.08333},
        (sfVector2f){595, 605});
    if (hunter->time >= 30) {
        sfRenderWindow_drawText(hunter->window, hunter->time_d->text, NULL);
        sfRenderWindow_drawText(hunter->window, hunter->catched_d->text, NULL);
    }
}

static void manage_mouse_move(sprite_t *sprite,
    sfVector2i event, sfColor color, sfColor go)
{
    sfFloatRect position = sfSprite_getGlobalBounds(sprite->sprite);

    if (sfFloatRect_contains(&position, event.x, event.y)) {
        sfSprite_setColor(sprite->sprite, color);
    } else {
        sfSprite_setColor(sprite->sprite, go);
    }
}

static void mouse_moved_menu(menu_t *menu, sfVector2i pos, pause_t *pause)
{
    sfFloatRect position = sfSprite_getGlobalBounds(pause->quit->sprite);

    manage_mouse_move(pause->resume, pos,
    (sfColor){255, 255, 255, 200}, (sfColor){255, 200, 200, 175});
    manage_mouse_move(pause->lobby, pos,
    (sfColor){255, 255, 255, 200}, (sfColor){255, 200, 200, 175});
    manage_mouse_move(pause->quit, pos,
    (sfColor){255, 255, 255, 200}, (sfColor){255, 200, 200, 175});
    if (sfFloatRect_contains(&position, pos.x, pos.y)) {
        pause->quit->texture = sfTexture_createFromFile(
            "src/images/frames/Sure.png", NULL);
    } else {
        pause->quit->texture = sfTexture_createFromFile(
            "src/images/frames/Quit.png", NULL);
    }
    sfSprite_setTexture(pause->quit->sprite, pause->quit->texture,
        sfTrue);
}

static void mouse_clicked_pause(project_t *hunter, menu_t *settings,
    sfMouseButtonEvent event, pause_t *pause)
{
    sfFloatRect posR = sfSprite_getGlobalBounds(pause->resume->sprite);
    sfFloatRect posL = sfSprite_getGlobalBounds(pause->lobby->sprite);
    sfFloatRect posQ = sfSprite_getGlobalBounds(pause->quit->sprite);
    sfFloatRect posfg = sfSprite_getGlobalBounds(pause->fg->sprite);

    if (sfFloatRect_contains(&posR, event.x, event.y) ||
        !sfFloatRect_contains(&posfg, event.x, event.y)) {
        pause->stop = 1;
    } else if (sfFloatRect_contains(&posL, event.x, event.y)) {
        settings->stop = 1;
    }
    if (sfFloatRect_contains(&posQ, event.x, event.y)) {
        if (pause->quit_nb >= 3) {
            settings->stop = 20;
        }
        sfSprite_setPosition(pause->quit->sprite, (sfVector2f)
            {randint(490, 1180), randint(200, 700)});
        pause->quit_nb++;
    }
}

static void pause_event_analise(project_t *hunter, menu_t *settings,
    sfEvent event, pause_t *pause)
{
    while (sfRenderWindow_pollEvent(settings->window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(settings->window);
            settings->stop = 20;
        }
        mouse_moved_menu(settings,
            sfMouse_getPositionRenderWindow(settings->window), pause);
        if (event.type == sfEvtMouseButtonPressed) {
            settings->ca = 2;
            mouse_clicked_pause(hunter, settings, event.mouseButton, pause);
            sfSound_setPitch(settings->clicked->sound, randfloat(1.1, 1.3));
            sfSound_play(settings->clicked->sound);
        }
    }
}

static void manage_mouse_click_pause(project_t *hunter, menu_t *settings)
{
    pause_t *pause = init_pause(settings);
    sfEvent eventPause;
    sfTexture *texture;

    while (settings->stop == 0 && pause->stop == 0) {
        sfRenderWindow_clear(hunter->window, sfBlack);
        pause_event_analise(hunter, settings, eventPause, pause);
        render_pause_button(hunter, settings, pause);
        draw_cursor(settings);
        wait(0, 0.016666666);
        sfRenderWindow_display(hunter->window);
    }
    texture = sfTexture_createFromFile("src/images/net.png", NULL);
    sfSprite_setTexture(settings->cursor->sprite, texture, sfTrue);
    my_free_pause(pause);
}

void pause_button(project_t *hunter, sfMouseButtonEvent event, menu_t *set)
{
    sfFloatRect position = sfSprite_getGlobalBounds(hunter->pause->sprite);
    sfTexture *texture;

    if (sfFloatRect_contains(&position, event.x, event.y)) {
        sfSound_setPitch(set->clicked->sound, randfloat(0.7, 0.9));
        sfSound_play(set->clicked->sound);
        texture = sfTexture_createFromFile("src/images/Hand.png", NULL);
        sfSprite_setTexture(set->cursor->sprite, texture, sfTrue);
        manage_mouse_click_pause(hunter, set);
    }
}
