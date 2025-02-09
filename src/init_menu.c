/*
** EPITECH PROJECT, 2024
** init_menu.c
** File description:
** The function for the initialisation of the manu page.
*/
#include "hunter.h"

static void init_menu9(menu_t *menu, stat_t *stats)
{
    display_scores(menu, 1);
    menu->stopped = 0;
    menu->BlR = create_sprite((sfVector2f){0, 0}, (sfIntRect)
        {0, 0, 1792, 1024}, "src/images/black.png", (sfVector2f){0, 0});
    menu->BlR->velocity.x = 255;
}

static void init_menu8(menu_t *menu, stat_t *stats)
{
    menu->score_showt = create_text("Display Scores",
        (sfVector2f){150, 50}, 50, "src/polices/BlackNorth.ttf");
    sfText_setColor(menu->score_showt->text, (sfColor){255, 255, 255, 155});
    sfText_setScale(menu->score_showt->text, (sfVector2f){0.8, 0.8});
    menu->tri = create_sprite((sfVector2f){200, 210}, (sfIntRect)
            {0, 0, 128, 64}, "src/images/Score.png", (sfVector2f){0, 0});
    menu->tri_v = 1;
    menu->ca = 0;
    menu->fg = create_sprite((sfVector2f){50, 150}, (sfIntRect)
            {0, 0, 70, 64}, "src/images/frames/cl.png", (sfVector2f){0, 0});
    menu->change = create_sprite((sfVector2f){200, 150}, (sfIntRect)
            {0, 0, 128, 64}, "src/images/frames/D.png", (sfVector2f){0, 0});
    sfSprite_setColor(menu->tri->sprite, (sfColor){250, 250, 250, 150});
    sfSprite_setColor(menu->change->sprite, (sfColor){250, 250, 250, 150});
    menu->score_list = create_text("An Error has Occured",
        (sfVector2f){100, 300}, 50, "src/polices/BlackNorth.ttf");
    sfText_setColor(menu->score_list->text, (sfColor){250, 230, 0, 150});
    sfText_setScale(menu->score_list->text, (sfVector2f){0.8, 0.8});
    init_menu9(menu, stats);
}

static void init_menu7(menu_t *menu, stat_t *stats)
{
    menu->pseudo_d = create_text(my_sec_strcat(my_sec_strcat(menu->name, "\n"),
    menu->lastname), (sfVector2f){1513, 353}, 50, "src/polices/BlackNorth.ttf");
    sfText_setColor(menu->pseudo_d->text, (sfColor){255, 255, 255, 155});
    sfText_setScale(menu->pseudo_d->text, (sfVector2f){0.8, 0.8});
    menu->generate = create_sprite((sfVector2f){1440, 300}, (sfIntRect)
        {0, 0, 54, 53}, "src/images/frames/rest.png", (sfVector2f){0, 0});
    menu->yourname = create_text("Your name :",
        (sfVector2f){1513, 300}, 50, "src/polices/BlackNorth.ttf");
    sfText_setColor(menu->yourname->text, (sfColor){255, 255, 255, 155});
    sfText_setScale(menu->yourname->text, (sfVector2f){0.8, 0.8});
    if (stats->score_show == 0) {
        menu->score_show = 0;
        menu->clickable2 = create_sprite((sfVector2f){50, 50}, (sfIntRect)
            {0, 0, 70, 64}, "src/images/frames/cl.png", (sfVector2f){0, 0});
    } else {
        menu->score_show = 1;
        menu->clickable2 = create_sprite((sfVector2f){50, 50}, (sfIntRect)
            {0, 0, 70, 64}, "src/images/frames/cl2.png", (sfVector2f){0, 0});
    }
    init_menu8(menu, stats);
}

static void init_menu6(menu_t *menu, stat_t *stats)
{
    if (stats->score_save == 0) {
        menu->score_save_v = 0;
        menu->clickable = create_sprite((sfVector2f){50, 910}, (sfIntRect)
            {0, 0, 70, 64}, "src/images/frames/cl.png", (sfVector2f){0, 0});
    }
    sfSprite_setColor(menu->logo->sprite, (sfColor){200, 200, 200, 150});
    menu->score_save = create_text("Score Saving",
        (sfVector2f){150, 913}, 50, "src/polices/BlackNorth.ttf");
    sfText_setColor(menu->score_save->text, (sfColor){255, 255, 255, 155});
    sfText_setScale(menu->score_save->text, (sfVector2f){0.8, 0.8});
    if (stats->iterations >= 1) {
        menu->name = my_strdup(stats->name);
        menu->lastname = my_strdup(stats->lastname);
    } else {
        menu->name = my_strdup(chose_name()[0]);
        menu->lastname = my_strdup(chose_name()[1]);
    }
    init_menu7(menu, stats);
}

static void init_menu5(menu_t *menu, stat_t *stats)
{
    if (stats->difficulty_chosen == 3) {
        menu->difficulty = create_sprite((sfVector2f){800, 590}, (sfIntRect)
            {0, 0, 128, 64}, "src/images/frames/Hard.png", (sfVector2f){0, 0});
    }
    sfSprite_setScale(menu->difficulty->sprite, (sfVector2f){2, 2});
    sfSprite_setColor(menu->difficulty->sprite, (sfColor){250, 250, 250, 150});
    menu->clicked = create_sound("src/musics/Punch.ogg", 50);
    menu->logo = create_sprite((sfVector2f){770, 70}, (sfIntRect)
            {0, 0, 165, 100}, "src/images/logo.png", (sfVector2f){0, 0});
    sfSprite_setScale(menu->logo->sprite, (sfVector2f){2, 2});
    sfSprite_setColor(menu->logo->sprite, (sfColor){250, 250, 250, 150});
    if (stats->score_save == 1) {
        menu->score_save_v = 1;
        menu->clickable = create_sprite((sfVector2f){50, 910}, (sfIntRect)
            {0, 0, 70, 64}, "src/images/frames/cl2.png", (sfVector2f){0, 0});
    }
    init_menu6(menu, stats);
}

static void init_menu4(menu_t *menu, stat_t *stats)
{
    sfSprite_setColor(menu->frame_s->sprite, (sfColor){150, 150, 150, 255});
    menu->quit_b = create_sprite((sfVector2f){1550, 900},
        (sfIntRect){0, 0, 160, 80}, "src/images/frames/Quit.png",
        (sfVector2f){0, 0});
    sfSprite_setColor(menu->quit_b->sprite, (sfColor){250, 250, 250, 150});
    menu->time = 0;
    if (stats->mode_chosen == 1) {
        menu->mode = create_sprite((sfVector2f){800, 390}, (sfIntRect)
    {0, 0, 128, 64}, "src/images/frames/TimeTrial.png", (sfVector2f){0, 0});
    } else if (stats->mode_chosen == 2) {
        menu->mode = create_sprite((sfVector2f){800, 390}, (sfIntRect)
            {0, 0, 128, 64}, "src/images/frames/Rush30.png", (sfVector2f){0, 0});
    }
    if (stats->mode_chosen == 3) {
        menu->mode = create_sprite((sfVector2f){800, 390}, (sfIntRect)
            {0, 0, 128, 64}, "src/images/frames/Endless.png", (sfVector2f){0, 0});
    }
    sfSprite_setScale(menu->mode->sprite, (sfVector2f){2, 2});
    sfSprite_setColor(menu->mode->sprite, (sfColor){250, 250, 250, 150});
    init_menu5(menu, stats);
}

static void init_menu3(menu_t *menu, stat_t *stats)
{
    menu->cursor = create_sprite((sfVector2f){0, 0},
        (sfIntRect){0, 0, 32, 32}, "src/images/Hand.png", (sfVector2f){0, 0});
    sfRenderWindow_setMouseCursorVisible(menu->window, sfFalse);
    menu->catched = 0;
    menu->tot_time = 0;
    menu->frame_s = create_sprite((sfVector2f){700, -155}, (sfIntRect)
        {0, 0, 256, 128}, "src/images/frames/stats.jpg", (sfVector2f){0, 0});
    menu->w_but_s = create_sprite((sfVector2f){705, -130},
        (sfIntRect){0, 0, 16, 16}, "src/images/b/Blue.png", (sfVector2f){16, 80});
    menu->stats_w = create_text("An Error have\noccured",
        (sfVector2f){780, -129}, 50, "src/polices/BlackNorth.ttf");
    menu->stats_b = create_text("An Error have\noccured",
        (sfVector2f){783, -126}, 50, "src/polices/BlackNorth.ttf");
    sfText_setScale(menu->stats_b->text, (sfVector2f){0.6, 0.6});
    sfText_setScale(menu->stats_w->text, (sfVector2f){0.6, 0.6});
    sfSprite_setScale(menu->w_but_s->sprite, (sfVector2f){5, 5});
    sfSprite_setScale(menu->frame_s->sprite, (sfVector2f){1.6, 1});
    sfText_setColor(menu->stats_b->text, (sfColor){97, 29, 0, 155});
    sfText_setColor(menu->stats_w->text, (sfColor){255, 255, 255, 155});
    init_menu4(menu, stats);
}

static menu_t *init_menu2(menu_t *menu, stat_t *stats)
{
    menu->bg = create_sprite((sfVector2f){0, 0},
        (sfIntRect){0, 0, 1792, 1024}, "src/images/bck2.png", (sfVector2f){0, 0});
    sfSprite_setColor(menu->bg->sprite, (sfColor){255, 255, 255, 100});
    menu->play_b = create_sprite((sfVector2f){850, 800},
        (sfIntRect){0, 0, 160, 80}, "src/images/frames/Start.png",
        (sfVector2f){0, 0});
    sfSprite_setColor(menu->play_b->sprite, (sfColor){250, 250, 250, 150});
    menu->mode_chosen = stats->mode_chosen;
    menu->stop = 0;
    menu->difficulty_chosen = stats->difficulty_chosen;
    if (stats->difficulty_chosen == 1) {
        menu->difficulty = create_sprite((sfVector2f){800, 590}, (sfIntRect)
        {0, 0, 128, 90}, "src/images/frames/Eric2.png", (sfVector2f){0, 0});
    } else if (stats->difficulty_chosen == 2) {
        menu->difficulty = create_sprite((sfVector2f){800, 590}, (sfIntRect)
        {0, 0, 128, 64}, "src/images/frames/Normal.png", (sfVector2f){0, 0});
    }
    init_menu3(menu, stats);
    return menu;
}

menu_t *init_menu(sfRenderWindow *window, stat_t *stats)
{
    menu_t *menu = malloc(sizeof(menu_t));

    menu->window = window;
    menu->arrow1 = create_sprite((sfVector2f){700, 385},
        (sfIntRect){0, 0, 32, 32}, "src/images/ArwL.png", (sfVector2f){32, 32});
    sfSprite_setScale(menu->arrow1->sprite, (sfVector2f){2, 2});
    menu->arrow2 = create_sprite((sfVector2f){1100, 400},
        (sfIntRect){0, 0, 32, 32}, "src/images/ArwR.png", (sfVector2f){32, 32});
    sfSprite_setScale(menu->arrow2->sprite, (sfVector2f){2, 2});
    menu->arrow3 = create_sprite((sfVector2f){700, 595},
        (sfIntRect){0, 0, 32, 32}, "src/images/ArwL.png", (sfVector2f){32, 32});
    sfSprite_setScale(menu->arrow3->sprite, (sfVector2f){2, 2});
    menu->arrow4 = create_sprite((sfVector2f){1100, 615},
        (sfIntRect){0, 0, 32, 32}, "src/images/ArwR.png", (sfVector2f){32, 32});
    sfSprite_setScale(menu->arrow4->sprite, (sfVector2f){2, 2});
    menu = init_menu2(menu, stats);
    return menu;
}
