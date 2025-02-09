/*
** EPITECH PROJECT, 2024
** animation_file.c
** File description:
** Function for initialise the animation.
*/
#include "hunter.h"

anim_t *init_animation(void)
{
    anim_t *anim = malloc(sizeof(anim_t));

    anim->window = create_my_window(1792, 1024, "My Hunter");
    anim->bg = create_sprite((sfVector2f){0, 0}, (sfIntRect)
    {0, 0, 1792, 1024}, "src/images/bck2.png", (sfVector2f){0, 0});
    sfSprite_setColor(anim->bg->sprite, (sfColor){255, 255, 255, 100});
    anim->text1 = create_sprite((sfVector2f){900, 400}, (sfIntRect)
    {0, 0, 32, 32}, "src/images/ArwL.png", (sfVector2f){0, 0});
    anim->utext1 = create_sprite((sfVector2f){900, 550}, (sfIntRect)
    {0, 0, 48, 64}, "src/images/Jar.png", (sfVector2f){0, 0});
    anim->text2 = create_sprite((sfVector2f){900, 400}, (sfIntRect)
    {0, 0, 32, 32}, "src/images/net.png", (sfVector2f){0, 0});
    anim->timex6 = 0;
    anim->time = 0;
    anim->stop = 0;
    sfSprite_scale(anim->text1->sprite, (sfVector2f){0.36, 0.36});
    sfSprite_scale(anim->utext1->sprite, (sfVector2f){0.36, 0.36});
    sfSprite_scale(anim->text2->sprite, (sfVector2f){0.36, 0.36});
    return anim;
}

void analyse_events_anim(anim_t *anim, sfEvent event)
{
    while (sfRenderWindow_pollEvent(anim->window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(anim->window);
            anim->stop = 20;
        }
        if (anim->time >= 80) {
            anim->stop = 1;
            sfRenderWindow_close(anim->window);
        }
    }
}

static void animate_text(anim_t *anim, sfVector2f bornes, sprite_t *sprite,
    int scl)
{
    sfVector2f scale = sfSprite_getScale(sprite->sprite);

    if (anim->time >= bornes.x && anim->time <= bornes.y) {
        sprite_move(anim->window, sprite, (sfVector2f){0, 0.016666},
            (sfVector2f){sprite->pos.y, sprite->pos.y + 5});
        if (scale.x <= scl) {
            sfSprite_scale(sprite->sprite,
                (sfVector2f){1.026, 1.026});
        }
        sfRenderWindow_drawSprite(anim->window, sprite->sprite, NULL);
    }
}

void animate_start(anim_t *anim)
{
    animate_text(anim, (sfVector2f){20, 55}, anim->text1, 2);
    animate_text(anim, (sfVector2f){25, 50}, anim->utext1, 1.5);
    animate_text(anim, (sfVector2f){65, 90}, anim->text2, 2);
}
