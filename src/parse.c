/*
** EPITECH PROJECT, 2022
** parsing
** File description:
** jam familly
*/

#include "my.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>

int existe_in_part (char *part, char c)
{
    for (int i = 0; part[i]; i++) {
        if (part[i] == c)
            return 1;
    }
    return 0;
}

int count_char_parse_next (char *part, char *str, int *i)
{
    int tmp = 0;
    if (existe_in_part(part, str[(*i)]) == 0)
        while (str[(*i)] && existe_in_part(part, str[(*i)++]) == 0)
            tmp = 1;
    return tmp;
}

int count_char_parse (char *str, char *part)
{
    int i = 0, colone_m = 0, tmp = 0;
    while (str[i]) {
        tmp = count_char_parse_next(part, str, &i);
        if (str[i] && !tmp)
            i++;
        colone_m += tmp;
    }
    return colone_m;
}

char **my_str_parse (char *str, char *part)
{
    int y = count_char_parse(str, part), x = 0, index_tab = 0;
    char **tab = malloc(sizeof(char *) * (y + 1));
    for (int i = 0; str[i] != '\0'; i++) {
        while (str[i] && existe_in_part(part, str[i]) == 1)
            i++;
        char printaaa = i + '0';
        for (x = 0; str[i + x] && existe_in_part(part, str[i + x]) == 0; x++);
        tab[index_tab] = malloc(sizeof(char) * (x + 1));
        int k;
        for (k = 0; str[k + i] && k < x; k++)
            tab[index_tab][k] = str[i + k];
        tab[index_tab++][x] = '\0';
        i += x - 1;
    }
    tab[y] = NULL;
    return tab;
}