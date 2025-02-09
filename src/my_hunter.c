/*
** EPITECH PROJECT, 2024
** my_hunter.c
** File description:
** Principal function for the myhunter project.
*/
#include "hunter.h"

static void wait_animate(project_t *hunter, firef_t *fir, menu_t *settings)
{
    score_management(hunter, settings);
    display_catched(hunter);
    hunter->timex6 = wait(hunter->timex6, 0.016666666);
    if (hunter->timex6 >= 6) {
        hunter->timex6 = 0;
        hunter->time++;
        hunter->real_time--;
        animate_butterflies(hunter, fir, settings);
    }
    draw_butterflies(hunter, fir);
    set_ready(hunter);
    draw_cursor(settings);
    sfRenderWindow_drawSprite(hunter->window, hunter->BlR->sprite, NULL);
    sfSprite_setColor(hunter->BlR->sprite, (sfColor){255, 255, 255,
        hunter->BlR->velocity.x});
    if (hunter->BlR->velocity.x > 50)
        hunter->BlR->velocity.x -= 1;
}

static void endless_mode(menu_t *settings)
{
    project_t *endless = init_project_hunter(settings);
    firef_t *fir = init_fire_flies();
    sfEvent event;

    while (settings->stop == 0) {
        sfRenderWindow_clear(endless->window, sfBlack);
        sfRenderWindow_drawSprite(endless->window, endless->bck->sprite, NULL);
        analyse_events_endless(endless, event, settings);
        wait_animate(endless, fir, settings);
        sfRenderWindow_display(endless->window);
    }
    settings->catched = endless->catched;
    settings->tot_time = endless->time - 30;
    my_free_project(endless, fir);
}

static void time_trial(menu_t *settings)
{
    project_t *hunter = init_project_hunter(settings);
    firef_t *fir = init_fire_flies();
    sfEvent event;

    while (hunter->real_time > 0 && settings->stop == 0) {
        sfRenderWindow_clear(hunter->window, sfBlack);
        sfRenderWindow_drawSprite(hunter->window, hunter->bck->sprite, NULL);
        analyse_events_hunter(hunter, event, settings);
        wait_animate(hunter, fir, settings);
        sfRenderWindow_display(hunter->window);
    }
    settings->catched = hunter->catched;
    settings->tot_time = hunter->time - 30;
    my_free_project(hunter, fir);
}

menu_t *menu(menu_t *menu, stat_t *stats)
{
    sfEvent event;
    int t = 0;
    sfTexture *texture;

    while (sfRenderWindow_isOpen(menu->window) && menu->stop == 0) {
        sfRenderWindow_clear(menu->window, sfBlack);
        sfRenderWindow_drawSprite(menu->window, menu->bg->sprite, NULL);
        move_arrows(menu);
        if (stats->iterations >= 1) {
            draw_score_anim(stats, menu, &t);
        }
        analyse_events_menu(menu, event, &t);
        draw_cursor(menu);
        sfRenderWindow_drawSprite(menu->window, menu->BlR->sprite, NULL);
        sfRenderWindow_display(menu->window);
        t = wait(t, 0.01666666);
    }
    texture = sfTexture_createFromFile("src/images/net.png", NULL);
    sfSprite_setTexture(menu->cursor->sprite, texture, sfTrue);
    return menu;
}

static int starting_animation(void)
{
    anim_t *anim = init_animation();
    sfEvent event;

    while (anim->stop == 0 && sfRenderWindow_isOpen(anim->window)) {
        sfRenderWindow_clear(anim->window, sfBlack);
        analyse_events_anim(anim, event);
        sfRenderWindow_drawSprite(anim->window, anim->bg->sprite, NULL);
        animate_start(anim);
        sfRenderWindow_display(anim->window);
        anim->timex6 = wait(anim->timex6, 0.016666666);
        if (anim->timex6 >= 6) {
            anim->timex6 = 0;
            anim->time++;
        }
    }
    return anim->stop;
}

static void init_stats(stat_t *stats, menu_t *settings, int nb)
{
    if (nb == 1) {
        stats->catched = settings->catched;
        stats->tot_time = settings->tot_time;
        stats->stop = settings->stop;
        stats->mode_chosen = settings->mode_chosen;
        stats->difficulty_chosen = settings->difficulty_chosen;
        stats->score_save = settings->score_save_v;
        stats->name = my_strdup(settings->name);
        stats->lastname = my_strdup(settings->lastname);
        stats->score_show = settings->score_show;
        stats->tri_score = settings->tri_v;
    } else {
        if (stats->iterations < 1) {
            stats->mode_chosen = 1;
            stats->difficulty_chosen = 2;
            stats->score_save = 1;
            stats->score_show = 0;
        }
        stats->stop = 0;
    }
}

stat_t *other_main(stat_t *stats)
{
    menu_t *settings;

    init_stats(stats, settings, 0);
    settings = init_menu(create_my_window(1792, 1024, "My Hunter"), stats);
    settings = menu(settings, stats);
    if (settings->stop == 1) {
        settings->stop = 0;
    }
    if (sfRenderWindow_isOpen(settings->window) &&
        settings->mode_chosen == 1) {
        time_trial(settings);
    } else if (sfRenderWindow_isOpen(settings->window) &&
        (settings->mode_chosen == 2 || settings->mode_chosen == 3)) {
        endless_mode(settings);
    }
    stats->iterations++;
    init_stats(stats, settings, 1);
    my_menu_free(settings);
    return stats;
}

static int check_argv(int argc, char **argv)
{
    if (argc > 1) {
        if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'h') {
            display_help();
            my_putstr("\n\n");
        }
        return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    stat_t *stats = malloc(sizeof(stat_t));

    if (check_argv(argc, argv)) {
        return 0;
    }
    srand(time(NULL));
    stats->iterations = 0;
    stats->stop = 0;
    stats->bgm = sfMusic_createFromFile("src/musics/OST.ogg");
    sfMusic_setVolume(stats->bgm, 15);
    sfMusic_play(stats->bgm);
    sfMusic_setLoop(stats->bgm, sfTrue);
    while (stats->stop != 20 && stats->iterations < 150) {
        stats = other_main(stats);
        save_score(stats);
    }
    return 0;
}
