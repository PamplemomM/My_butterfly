/*
** EPITECH PROJECT, 2024
** hunter.h
** File description:
** The header for the project hunter.h
*/

#ifndef HUNTER_H
    #define HUNTER_H

    #include <stddef.h>
    #include <SFML/Graphics.h>
    #include <SFML/Window/Event.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include <SFML/Audio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <time.h>

    #include "typedefs.h"


void set_animation(project_t *hunter, sprite_t *sprite, menu_t *settings);
sprite_t *create_sprite(sfVector2f pos, sfIntRect rect, char *texture_path,
    sfVector2f rect_depl);
firef_t *init_fire_flies(void);
void set_animation_fir(project_t *hunter, firef_t *fir, menu_t *settings);
void sprite_move(sfRenderWindow *window, sprite_t *sprite, sfVector2f pos,
    sfVector2f max);

void draw_butterflies(project_t *hunter, firef_t *fir);
void animate_butterflies(project_t *hunter, firef_t *fir,
    menu_t *settings);
void transition(menu_t *menu, int *t);

void analyse_events_hunter(project_t *hunter, sfEvent event,
    menu_t *settings);
void analyse_events_menu(menu_t *menu, sfEvent event, int *t);


void analyse_events_endless(project_t *endless, sfEvent event,
    menu_t *settings);
void pause_button(project_t *hunter, sfMouseButtonEvent event,
    menu_t *set);


text_t *create_text(char *str, sfVector2f pos, unsigned int size,
    char const *police);
int wait(int tm, float t);
void my_free_project(project_t *hunter, firef_t *fir);
int randint(int min, int max);
void my_menu_free(menu_t *settings);


sfRenderWindow *create_my_window(int width, int height, char *name);
pause_t *init_pause(menu_t *settings);
void my_free_pause(pause_t *pause);
void draw_score_anim(stat_t *stats, menu_t *menu, int *t);
char *my_strcpy(char *dest, char const *src);

int my_putstr(char const *str);
int mini_printf(const char *format, ...);
int my_strlen(char const *str);
char *my_int_to_str(int nbr);

char *my_float_to_str(int nb);
char *my_sec_strcat(char *dest, char const *src);
float randfloat(float min, float max);
sound_t *create_sound(char *path, float volume);
char *my_strdup(char const *src);

void display_help(void);
void init_scale_butterfly(project_t *my_hunter, menu_t *settings);
project_t *init_project_hunter(menu_t *settings);
firef_t *init_fire_flies(void);

void score_management(project_t *hunter, menu_t *settings);
void display_catched(project_t *hunter);
void set_ready(project_t *hunter);
void button_hitbox2(menu_t *menu, int nb);
int my_get_nbr(char const *str);

menu_t *init_menu(sfRenderWindow *window, stat_t *stats);

void move_arrows(menu_t *menu);
void change_mode(menu_t *menu);
void change_dif(menu_t *menu);
void speed_set(int *smi, int *sma, menu_t *settings, sprite_t *sprite);
void draw_cursor(menu_t *menu);


void save_score(stat_t *stats);
char *my_strncpy(char *dest, char const *src, int nb);
void clickable(menu_t *menu, sfMouseButtonEvent event);
char **chose_name(void);
void change_tri2(menu_t *menu);

anim_t *init_animation(void);
void analyse_events_anim(anim_t *anim, sfEvent event);
void animate_start(anim_t *anim);

player_t *load_data(void);
void my_sort_players(player_t *players, int nb, int sort);
char *put_in_char(player_t *players, int i, int sort);
void display_scores(menu_t *menu, int sort);

char **my_str_to_word_array(char *str, int i, int j, int k);
void free_word_array(char **wa);

#endif /* HUNTER_H */
