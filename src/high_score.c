/*
** EPITECH PROJECT, 2024
** high_score.c
** File description:
** The functions for the high score management.
*/
#include "hunter.h"

static char *get_time(stat_t *stats)
{
    int fd = open("/proc/driver/rtc", O_RDONLY);
    char buffer[2];
    int i = 0;
    char *date = malloc(sizeof(char) * 12);
    int ratio = (stats->catched * 100) - stats->tot_time;

    date[0] = '\0';
    date = my_sec_strcat(date, ":");
    date = my_sec_strcat(date, my_int_to_str(ratio));
    date = my_sec_strcat(date, ":");
    return date;
}

static void write_score(stat_t *stats)
{
    int fd;
    char *date = get_time(stats);
    char *score = malloc(sizeof(char) * 1);

    score[0] = '\0';
    score = my_sec_strcat(score, stats->name);
    score = my_sec_strcat(score, stats->lastname);
    score = my_sec_strcat(score, date);
    score = my_sec_strcat(score, my_int_to_str(stats->catched));
    score = my_sec_strcat(score, ":");
    score = my_sec_strcat(score, my_int_to_str(stats->tot_time));
    score[my_strlen(score) - 1] = '\n';
    fd = open("A-score.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    write(fd, score, my_strlen(score));
    close(fd);
    free(date);
    free(score);
}

void save_score(stat_t *stats)
{
    if (stats->stop == 20 || stats->score_save == 0 ||
        stats->tot_time < 30) {
        return;
    }
    write_score(stats);
}

char *my_strncpy(char *dest, char const *src, int nb)
{
    int i = 0;

    while (src[i] != '\0' && i < nb - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

static void pseudo_generator(menu_t *menu, sfMouseButtonEvent event)
{
    sfFloatRect position = sfSprite_getGlobalBounds(menu->generate->sprite);

    if (sfFloatRect_contains(&position, event.x, event.y)) {
        sfSound_setPitch(menu->clicked->sound, randfloat(1.1, 1.3));
        sfSound_play(menu->clicked->sound);
        free(menu->name);
        free(menu->lastname);
        menu->name = my_strdup(chose_name()[0]);
        menu->lastname = my_strdup(chose_name()[1]);
        sfText_setString(menu->pseudo_d->text, my_sec_strcat(
            my_sec_strcat(menu->name, "\n"), menu->lastname));
        sfSprite_rotate(menu->generate->sprite, randint(1, 15));
    }
    sfSprite_setRotation(menu->generate->sprite, 0);
}

static void clickable_tf(sprite_t *sprite, int *value, text_t *text,
    char *texte)
{
    sfTexture *texture;

    if (*value == 1) {
        *value = 0;
        sfText_setString(text->text, my_sec_strcat(texte, "(OFF)"));
        texture = sfTexture_createFromFile("src/images/frames/cl.png", NULL);
    } else {
        *value = 1;
        sfText_setString(text->text, my_sec_strcat(texte, "(ON)"));
        texture = sfTexture_createFromFile("src/images/frames/cl2.png", NULL);
    }
    sfSprite_setTexture(sprite->sprite, texture, sfTrue);
}

void change_tri2(menu_t *menu)
{
    sfTexture *texture;

    switch (menu->tri_v) {
    case 1 :
        texture = sfTexture_createFromFile("src/images/Catches.png", NULL);
        menu->tri_v = 2;
        display_scores(menu, 2);
        break;
    case 2 :
        texture = sfTexture_createFromFile("src/images/Time.png", NULL);
        menu->tri_v = 3;
        display_scores(menu, 3);
        break;
    case 3:
        texture = sfTexture_createFromFile("src/images/Score.png", NULL);
        menu->tri_v = 1;
        display_scores(menu, 1);
        break;
    }
    sfSprite_setTexture(menu->tri->sprite, texture, sfTrue);
}

static void change_tri(menu_t *menu, sfMouseButtonEvent event)
{
    sfFloatRect position = sfSprite_getGlobalBounds(menu->change->sprite);
    sfTexture *texture;

    if (sfFloatRect_contains(&position, event.x, event.y)) {
        sfSound_setPitch(menu->clicked->sound, randfloat(1.1, 1.3));
        sfSound_play(menu->clicked->sound);
        change_tri2(menu);
    }
}

void clickable(menu_t *menu, sfMouseButtonEvent event)
{
    sfFloatRect position = sfSprite_getGlobalBounds(menu->clickable->sprite);
    sfFloatRect position2 = sfSprite_getGlobalBounds(menu->clickable2->sprite);

    sfSound_setPitch(menu->clicked->sound, randfloat(1.1, 1.3));
    if (sfFloatRect_contains(&position, event.x, event.y)) {
        sfSound_play(menu->clicked->sound);
        clickable_tf(menu->clickable, &(menu->score_save_v), menu->score_save,
            "Score Saving ");
    } else if (sfFloatRect_contains(&position2, event.x, event.y)) {
        sfSound_play(menu->clicked->sound);
        clickable_tf(menu->clickable2, &(menu->score_show), menu->score_showt,
            "Display Score ");
    }
    pseudo_generator(menu, event);
    change_tri(menu, event);
}

char **chose_name(void)
{
    char *first[] = {"The Big ", "Beautiful ", "Stupid ", "Mr. ", "Mrs. ",
        "Silly ", "The Pro ", "Bad ", "Goofy ", "The ",
        "Ahhhh ", "Goofy  Ahhh ", "Dirty ", "Best ", NULL};
    char *last[] = {"Player ", "Nerd ", "Idiot ", "Catcher ", "Cobblestone ",
        "Guy ", "blebleble ", "Gamer ", "Duck ", "Butterfly ", "Firefly ",
        "Animation", "Hunter", NULL};
    char **result = malloc(sizeof(char *) * 2);

    result[0] = '\0';
    result[0] = my_strdup(first[(randint(0, 12) * randint(0, 12)) % 14]);
    result[1] = my_strdup(last[(randint(0, 12) * randint(0, 12)) % 13]);
    return result;
}
