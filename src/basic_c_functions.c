/*
** EPITECH PROJECT, 2024
** my_putstr.c
** File description:
** fonction that displays, one-by-one, the charaters of a string.
*/
#include <sys/stat.h>
#include <stdarg.h>
#include "hunter.h"

static int my_putchar(char c)
{
    write(1, &c, 1);
    return 1;
}

int my_putstr(char const *str)
{
    int i = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        write(1, &str[i], 1);
    }
    return i;
}

static void my_put_nbr(int nb)
{
    if (nb < 0) {
        my_putstr("-");
        nb = nb * (-1);
    }
    if (nb == -2147483648) {
        my_putstr("2147483648");
    }
    if (nb <= 9 && nb >= 0) {
        my_putchar(nb + 48);
    } else if (nb > 9) {
        my_put_nbr(nb / 10);
        my_putchar(nb % 10 + 48);
    }
}

static int condition_flag(const char *s, int i, va_list arg)
{
    if (s[i + 1] == 's') {
        my_putstr(va_arg(arg, char *));
    }
    if (s[i + 1] == 'd' || s[i + 1] == 'i') {
        my_put_nbr(va_arg(arg, int));
    }
    if (s[i + 1] == 'c') {
        my_putchar(va_arg(arg, int));
    }
    if (s[i + 1] == '%') {
        my_putchar('%');
    }
    return i;
}

int mini_printf(const char *format, ...)
{
    va_list arg;

    va_start(arg, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i = condition_flag(format, i, arg);
            i += 1;
        } else {
            my_putchar(format[i]);
        }
    }
    va_end(arg);
    return 1;
}

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }
    return i;
}

static void my_revstr(char *str)
{
    int i = 0;
    int j = my_strlen(str) - 1;
    char res;

    while (str[i] != '\0' && i < j) {
        res = str[i];
        str[i] = str[j];
        str[j] = res;
        i++;
        j--;
    }
}

char *my_int_to_str(int nbr)
{
    int i = 0;
    char *result = malloc(sizeof(char) * 12 + 1);

    if (nbr < 10) {
        result[0] = '0';
        result[1] = nbr + 48;
        result[2] = '\0';
    } else {
        while (nbr > 0) {
            result[i] = (nbr % 10) + 48;
            nbr = nbr / 10;
            i++;
        }
        result[i] = '\0';
        my_revstr(result);
    }
    return result;
}

void display_help(void)
{
    int fd = open("src/desc.txt", O_RDONLY);
    struct stat s;
    char *buffer = malloc(sizeof(char) * 341);

    mini_printf("\n\033[1mMy Butterfly\033[0m");
    read(fd, buffer, 340);
    write(1, buffer, 340);
    mini_printf("\n\033[1mTime's Trial\033[0m");
    read(fd, buffer, 135);
    write(1, buffer, 135);
    my_putstr("\n\033[1mRush30\033[0m: Catch as many butterflies as you can");
    my_putstr(" in 30 seconds.\nTest your reflexes!\n\033[1mEndless\033[0m");
    my_putstr(": Relax or challenge yourself with unlimited time.\n\n");
    my_putstr("Speed options:\n\033[1mEric Mode\033[0m: A slow pace, ");
    my_putstr("suitable for beginners or the curious.\n\033[1m");
    my_putstr("Normal Mode\033[0m: Perfect for discovering the game.");
    my_putstr("\n\033[1mHarder\033[0m:");
    read(fd, buffer, 221);
    write(1, buffer, 221);
    close(fd);
}
