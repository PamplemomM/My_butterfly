/*
** EPITECH PROJECT, 2024
** basic_c_functions2.c
** File description:
** The basic c functions.
*/
#include "hunter.h"

char *my_float_to_str(int nb)
{
    char *result = my_int_to_str(nb);
    int len = my_strlen(result);
    char temp = result[len - 1];

    result[len - 1] = '.';
    result[len] = temp;
    result[len + 1] = '\0';
    return result;
}

static char *my_strcat(char *dest, char const *src)
{
    int ldest = my_strlen(dest);
    int lsrc = my_strlen(src);

    for (int i = 0; i < lsrc; i++) {
        dest[ldest + i] = src[i];
    }
    dest[ldest + lsrc] = '\0';
    return dest;
}

char *my_sec_strcat(char *dest, char const *src)
{
    int len_dest = my_strlen(dest);
    int len_src = my_strlen(src);
    char *res = malloc(sizeof(char) * (len_dest + len_src + 1));

    for (int i = 0; i < len_dest; i++) {
        res[i] = dest[i];
    }
    for (int i = 0; i < len_src; i++) {
        res[len_dest + i] = src[i];
    }
    res[len_dest + len_src] = '\0';
    return res;
}

float randfloat(float min, float max)
{
    float temp;
    float random_nbr;

    if (min > max) {
        temp = min;
        min = max;
        max = temp;
    }
    random_nbr = min + (rand() % 100 / max) / 100;
    return random_nbr;
}

sound_t *create_sound(char *path, float volume)
{
    sound_t *new_sound = malloc(sizeof(sound_t));

    new_sound->buffer = sfSoundBuffer_createFromFile(path);
    new_sound->sound = sfSound_create();
    sfSound_setBuffer(new_sound->sound, new_sound->buffer);
    sfSound_setVolume(new_sound->sound, volume);
    return new_sound;
}

char *my_strdup(char const *src)
{
    int i = 0;
    char *str;

    str = malloc(sizeof(char) * (my_strlen(src) + 1));
    while (src[i] != '\0') {
        str[i] = src[i];
        i++;
    }
    str[i] = '\0';
    return str;
}
