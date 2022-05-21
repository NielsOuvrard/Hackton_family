/*
** EPITECH PROJECT, 2022
** hackton
** File description:
** familly
*/

#include "my.h"

typedef struct tree_s {
    char *name;
    struct tree_s *frere_soeur;
    struct tree_s *conjoint;
    struct tree_s *parents;
    struct tree_s *enfants;
} tree_s;

char **filepath_to_arr(char *filepath);


int main (int ac, char **av)
{
    char **src = filepath_to_arr(av[1]);
    my_show_word_array(src);
    int names;
    for (names = 0; src[names] && src[names][0] != '#'; names++);
    free_my_arr(src);
    my_printf("ok\n");
    return 0;
}
