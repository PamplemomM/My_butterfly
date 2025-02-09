/*
** EPITECH PROJECT, 2024
** my_str_to_word_array.c
** File description:
** Function that splits a string into words.
*/

#include <stddef.h>
#include <stdlib.h>
#include "hunter.h"

static int found_len(char *str, int i)
{
    int result = 0;

    while (str[i] != '\n') {
        result++;
        i++;
    }
    return result;
}

static int count_words(char *str)
{
    int count = 1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            count++;
        }
    }
    return count;
}

static int condition(char *str, int i)
{
    if (str[i] == '\n') {
            i++;
    }
    return i;
}

char **my_str_to_word_array(char *str, int i, int j, int k)
{
    int word_len = found_len(str, i);
    int size = count_words(str);
    char **res = malloc(sizeof(char *) * (size + 1));

    res[j] = malloc(sizeof(char) * (found_len(str, i) + 1));
    while (str[i] != '\0') {
        word_len = found_len(str, i);
        res[j] = malloc(sizeof(char) * (word_len + 1));
        k = 0;
        while (str[i] != '\n' && str[i] != '\0') {
            res[j][k] = str[i];
            k++;
            i++;
        }
        res[j][k] = '\0';
        j++;
        i = condition(str, i);
    }
    res[j] = NULL;
    return res;
}

void free_word_array(char **wa)
{
    if (wa == NULL) {
        return;
    }
    for (int i = 0; wa[i] != NULL; i++) {
        free(wa);
    }
    free(wa);
}
