/*
** EPITECH PROJECT, 2024
** score_display.c
** File description:
** The functions for the score _display.
*/
#include "hunter.h"

static int skip(char *scores, int j, char *buffer, char c)
{
    int i = 0;

    while (scores[j] != c && scores[j] != '\0') {
        buffer[i] = scores[j];
        i++;
        j++;
    }
    buffer[i] = '\0';
    if (scores[j] == c) {
        j++;
    }
    return j;
}

static int init_scores(char **scores, player_t *player, int max)
{
    int i = 0;
    char buffer[20];
    int pos;

    while (scores[i] != NULL && i < max) {
        pos = 0;
        pos = skip(scores[i], pos, buffer, ':');
        player[i].name = my_strdup(buffer);
        pos = skip(scores[i], pos, buffer, ':');
        player[i].score = my_get_nbr(buffer);
        pos = skip(scores[i], pos, buffer, ':');
        player[i].captured = my_get_nbr(buffer);
        pos = skip(scores[i], pos, buffer, '\0');
        player[i].time = my_get_nbr(buffer);
        i++;
    }
    player[0].nb = i;
    return i;
}

static char *read_file(char const *file, int *cpt)
{
    int fd = open(file, O_RDONLY);
    char buffer[2];
    int size = 0;
    char *result = malloc(sizeof(char) * 1);

    result[0] = '\0';
    do {
        buffer[1] = '\0';
        size = read(fd, buffer, 1);
        if (buffer[0] == '\n') {
            (*cpt)++;
        }
        result = my_sec_strcat(result, buffer);
    } while (size > 0 && buffer[0] != '\0');
    (*cpt)--;
    close(fd);
    return result;
}

player_t *load_data(void)
{
    int size = 0;
    char *all_data = read_file("A-score.txt", &size);
    char **scores = my_str_to_word_array(all_data, '\n', 0, 0);
    player_t *players = malloc(sizeof(player_t) * size);

    free(all_data);
    init_scores(scores, players, size);
    return players;
}

static int my_sort_score(player_t *players, player_t *temp,
    int nb)
{
    for (int i = 0; i < nb - 1; i++) {
        if (players[i].score > players[i + 1].score) {
            *temp = players[i];
            players[i] = players[i + 1];
            players[i + 1] = *temp;
            return 1;
        }
    }
    return 0;
}

static int my_sort_time(player_t *players, player_t *temp,
    int nb)
{
    for (int i = 0; i < nb - 1; i++) {
        if (players[i].time > players[i + 1].time) {
            *temp = players[i];
            players[i] = players[i + 1];
            players[i + 1] = *temp;
            return 1;
        }
    }
    return 0;
}

static int my_sort_captures(player_t *players, player_t *temp,
    int nb)
{
    for (int i = 0; i < nb - 1; i++) {
        if (players[i].captured > players[i + 1].captured) {
            *temp = players[i];
            players[i] = players[i + 1];
            players[i + 1] = *temp;
            return 1;
        }
    }
    return 0;
}

static int my_reverse_sort(player_t *players, player_t *temp,
    int nb)
{
    int start = 0;
    int last = nb - 1;

    while (start < last) {
        *temp = players[start];
        players[start] = players[last];
        players[last] = *temp;
        start++;
        last--;
    }
    return 0;
}

void my_sort_players(player_t *players, int nb, int sort)
{
    player_t temp;
    int swap = 1;
    int size = players[0].nb;

    while (swap == 1) {
        swap = 0;
        if (sort == 1) {
            swap = my_sort_score(players, &temp, nb);
        }
        if (sort == 3) {
            swap = my_sort_time(players, &temp, nb);
        }
        if (sort == 2) {
            swap = my_sort_captures(players, &temp, nb);
        }
        if (sort == 4) {
            swap = my_reverse_sort(players, &temp, nb);
        }
    }
    players[0].nb = size;
}

char *put_in_char(player_t *players, int i, int sort)
{
    char *str = malloc(sizeof(char) * 1);

    str[0] = '\0';
    str = my_sec_strcat(str, players[i].name);
    str = my_sec_strcat(str, ": ");
    switch (sort) {
    case 1:
        str = my_sec_strcat(str, my_int_to_str(players[i].score));
        break;
    case 2:
        str = my_sec_strcat(str, my_int_to_str(players[i].captured));
        break;
    case 3:
        str = my_sec_strcat(str, my_int_to_str(players[i].time));
        break;
    }
    str = my_sec_strcat(str, "\n");
    return str;
}
