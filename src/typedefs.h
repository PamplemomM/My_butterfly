/*
** EPITECH PROJECT, 2024
** sprite_managment.h
** File description:
** The header for the sprite managment.
*/

#ifndef SPRITE_MANAGEMENT_H
    #define SPRITE_MANAGEMENT_H

    #include "hunter.h"

typedef struct sprite {
    sfSprite *sprite;
    sfVector2f pos;
    sfIntRect rect;
    sfTexture *texture;
    sfVector2f rect_depl;
    sfVector2f velocity;
    sfVector2f scale;
    int hide;
} sprite_t;

typedef struct sound {
    sfSound *sound;
    sfSoundBuffer *buffer;
} sound_t;

typedef struct text {
    sfText *text;
    sfVector2f pos;
    sfFont *font;
    sfVector2f move;
    sfVector2f velocity;
    unsigned int size;
} text_t;

typedef struct my_project {
    sfRenderWindow *window;
    sound_t *clicked;
    sprite_t *blue_butterfly;
    sprite_t *grey_butterfly;
    sprite_t *pink_butterfly;
    sprite_t *red_butterfly;
    sprite_t *white_butterfly;
    sprite_t *yellow_butterfly;
    sprite_t *bck;
    int timex6;
    int time;
    int real_time;
    int catched;
    text_t *time_d;
    text_t *catched_d;
    sprite_t *ready;
    sprite_t *pause;
    float time_gain;
    sprite_t *BlR;
} project_t;

typedef struct fireflies {
    sprite_t *firefly1;
    sprite_t *firefly2;
    sprite_t *firefly3;
    sprite_t *firefly4;
    sprite_t *firefly5;
} firef_t;

typedef struct menu {
    sfRenderWindow *window;
    sound_t *clicked;
    sprite_t *arrow1;
    sprite_t *arrow2;
    sprite_t *arrow3;
    sprite_t *arrow4;
    sprite_t *mode;
    int mode_chosen;
    sprite_t *difficulty;
    int difficulty_chosen;
    sprite_t *bg;
    sprite_t *play_b;
    sprite_t *quit_b;
    int stop;
    int stopped;
    sprite_t *cursor;
    int ca;
    int catched;
    int tot_time;
    int time;
    sprite_t *frame_s;
    sprite_t *w_but_s;
    text_t *stats_w;
    text_t *stats_b;
    sprite_t *logo;
    sprite_t *clickable;
    text_t *score_save;
    int score_save_v;
    text_t *yourname;
    text_t *pseudo_d;
    sprite_t *generate;
    char *name;
    char *lastname;
    sprite_t *clickable2;
    text_t *score_showt;
    int score_show;
    sprite_t *fg;
    sprite_t *tri;
    int tri_v;
    sprite_t *change;
    text_t *score_list;
    sprite_t *BlR;
} menu_t;

typedef struct statistics {
    int stop;
    int catched;
    int tot_time;
    int mode_chosen;
    int difficulty_chosen;
    int iterations;
    int score_save;
    int score_show;
    int tri_score;
    sfMusic *bgm;
    char *name;
    char *lastname;
} stat_t;

typedef struct pause {
    int stop;
    int quit_nb;
    sprite_t *bg;
    sprite_t *fg;
    sprite_t *resume;
    sprite_t *lobby;
    sprite_t *quit;
} pause_t;

typedef struct animation {
    sfRenderWindow *window;
    int stop;
    sprite_t *bg;
    sprite_t *tran;
    sprite_t *text1;
    sprite_t *utext1;
    sprite_t *text2;
    int timex6;
    int time;
} anim_t;

typedef struct {
    int nb;
    char *name;
    int score;
    int captured;
    int time;
} player_t;


#endif /* SPRITE_MANAGEMENT_H */
