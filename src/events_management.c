/*
** EPITECH PROJECT, 2024
** events_management.c
** File description:
** The function that analises events.
*/
#include "hunter.h"

static void sprite_hitbox_sec(project_t *hunter, sprite_t *sprite,
    sfVector3f event, menu_t *settings)
{
    float nb = randint(5, 7);

    if (randint(1, 2) == 1) {
        sfSprite_setPosition(sprite->sprite,
            (sfVector2f){randint(100, 1600), 1100});
    } else {
        sfSprite_setPosition(sprite->sprite,
            (sfVector2f){randint(100, 1600), -150});
    }
    if (settings->difficulty_chosen == 1) {
        hunter->real_time += 25;
    } else {
        hunter->real_time += hunter->time_gain;
        hunter->time_gain -= 0.04;
    }
    sfSprite_setScale(sprite->sprite, (sfVector2f){nb, nb});
    sfSprite_setColor(sprite->sprite, (sfColor){rand() % 255, rand() % 255,
        rand() % 255, 255});
}

static int sprite_hitbox(project_t *hunter, sprite_t *sprite,
    sfVector3f event, menu_t *settings)
{
    sfFloatRect position = sfSprite_getGlobalBounds(sprite->sprite);

    if (event.z >= 1) {
        return 1;
    }
    sfSound_setPitch(hunter->clicked->sound, randfloat(0.9, 1.1));
    if (sfFloatRect_contains(&position, event.x, event.y)) {
        sprite_hitbox_sec(hunter, sprite, event, settings);
        sfSound_play(hunter->clicked->sound);
        hunter->catched += 1;
        return 1;
    }
    return 0;
}

static void manage_mouse_click(project_t *hun, sfMouseButtonEvent event,
    menu_t *set)
{
    int ic = 0;

    if (hun->time >= 30) {
        ic += sprite_hitbox(hun, hun->blue_butterfly,
            (sfVector3f){event.x, event.y, ic}, set);
        ic += sprite_hitbox(hun, hun->grey_butterfly,
            (sfVector3f){event.x, event.y, ic}, set);
        ic += sprite_hitbox(hun, hun->pink_butterfly,
            (sfVector3f){event.x, event.y, ic}, set);
        ic += sprite_hitbox(hun, hun->red_butterfly,
            (sfVector3f){event.x, event.y, ic}, set);
        ic += sprite_hitbox(hun, hun->white_butterfly,
            (sfVector3f){event.x, event.y, ic}, set);
        ic += sprite_hitbox(hun, hun->yellow_butterfly,
            (sfVector3f){event.x, event.y, ic}, set);
    }
    set->ca = 2;
}

void analyse_events_hunter(project_t *hunter, sfEvent event, menu_t *settings)
{
    while (sfRenderWindow_pollEvent(hunter->window, &event)) {
        if (event.type == sfEvtMouseButtonPressed) {
            manage_mouse_click(hunter, event.mouseButton, settings);
            pause_button(hunter, event.mouseButton, settings);
        }
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(hunter->window);
            settings->stop = 20;
        }
        if (hunter->real_time <= 0) {
            settings->stop = 10;
        }
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

static void button_hitbox(menu_t *menu, sprite_t *sprite,
    sfMouseButtonEvent event, int nb)
{
    sfFloatRect position = sfSprite_getGlobalBounds(sprite->sprite);

    if (sfFloatRect_contains(&position, event.x, event.y)) {
        if (nb == 1) {
            sfSound_setPitch(menu->clicked->sound, randfloat(1.1, 1.3));
            sfSound_play(menu->clicked->sound);
            menu->stopped = 1;
        }
        if (nb == 0) {
            sfSound_setPitch(menu->clicked->sound, randfloat(1.1, 1.3));
            sfSound_play(menu->clicked->sound);
            sfRenderWindow_close(menu->window);
            menu->stop = 20;
        }
    }
    if (nb != 0 && nb != 1) {
        if (sfFloatRect_contains(&position, event.x, event.y)) {
            button_hitbox2(menu, nb);
        }
    }
}

static void manage_mouse_click2(menu_t *menu, sfMouseButtonEvent event, int *t)
{
    if (menu->stopped == 1) {
        (*t) = 0;
        return;
    }
    clickable(menu, event);
    button_hitbox(menu, menu->arrow1, event, 2);
    button_hitbox(menu, menu->arrow2, event, 3);
    button_hitbox(menu, menu->arrow3, event, 4);
    button_hitbox(menu, menu->arrow4, event, 5);
    button_hitbox(menu, menu->play_b, event, 1);
    button_hitbox(menu, menu->quit_b, event, 0);
    change_mode(menu);
    change_dif(menu);
    menu->ca = 2;
}

static void mouse_moved_menu2(menu_t *menu, sfVector2i pos)
{
    if (menu->difficulty_chosen == 1) {
        manage_mouse_move(menu->arrow3, pos,
        (sfColor){255, 150, 150, 100}, (sfColor){255, 150, 150, 150});
        manage_mouse_move(menu->arrow4, pos,
        (sfColor){255, 255, 0, 225}, (sfColor){255, 255, 255, 255});
    } else if (menu->difficulty_chosen == 2) {
        manage_mouse_move(menu->arrow3, pos,
        (sfColor){255, 255, 0, 225}, (sfColor){255, 255, 255, 255});
        manage_mouse_move(menu->arrow4, pos,
        (sfColor){255, 255, 0, 225}, (sfColor){255, 255, 255, 255});
    }
    if (menu->difficulty_chosen == 3) {
        manage_mouse_move(menu->arrow3, pos,
        (sfColor){255, 255, 0, 225}, (sfColor){255, 255, 255, 255});
        manage_mouse_move(menu->arrow4, pos,
        (sfColor){255, 150, 150, 100}, (sfColor){255, 150, 150, 150});
    }
}

static void mouse_moved_menu(menu_t *menu, sfVector2i pos)
{
    sfFloatRect position = sfSprite_getGlobalBounds(menu->quit_b->sprite);

    manage_mouse_move(menu->arrow1, pos,
    (sfColor){255, 255, 0, 225}, (sfColor){255, 255, 255, 255});
    manage_mouse_move(menu->arrow2, pos,
    (sfColor){255, 255, 0, 225}, (sfColor){255, 255, 255, 255});
    mouse_moved_menu2(menu, pos);
    manage_mouse_move(menu->play_b, pos,
        (sfColor){255, 200, 200, 200}, (sfColor){255, 200, 200, 150});
    manage_mouse_move(menu->quit_b, pos,
    (sfColor){255, 200, 200, 200}, (sfColor){255, 200, 200, 150});
    if (sfFloatRect_contains(&position, pos.x, pos.y)) {
        menu->quit_b->texture = sfTexture_createFromFile(
            "src/images/frames/NoF.png", NULL);
    } else {
        menu->quit_b->texture = sfTexture_createFromFile(
            "src/images/frames/Quit.png", NULL);
    }
    sfSprite_setTexture(menu->quit_b->sprite, menu->quit_b->texture,
        sfTrue);
}

void analyse_events_menu(menu_t *menu, sfEvent event, int *t)
{
    while (sfRenderWindow_pollEvent(menu->window, &event)) {
        if (event.type == sfEvtMouseButtonPressed) {
            manage_mouse_click2(menu, event.mouseButton, t);
        }
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(menu->window);
            menu->stop = 20;
        }
    }
    transition(menu, t);
    mouse_moved_menu(menu, sfMouse_getPositionRenderWindow(menu->window));
}
