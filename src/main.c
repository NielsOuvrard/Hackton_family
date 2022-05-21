/*
** EPITECH PROJECT, 2022
** Jam
** File description:
** familly
*/

#include "my.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct tree_s {
    char *name;
    struct tree_s *frere_soeur;
    struct tree_s *conjoint;
    struct tree_s *parents;
    struct tree_s *enfants;
} tree_s;

typedef struct list_s {
    tree_s *perso;
    struct list_s *next;
} list_s;

char **filepath_to_arr(char *filepath);

char **my_str_parse (char *str, char *part);

tree_s *where_is_it (list_s *list, char *name)
{
    while (list) {
        if (!my_strvcmp(list->perso->name, name))
            return list->perso;
        list = list->next;
    }
    return NULL;
}

list_s *add_new_node (list_s *list, char *name)
{
    list_s *new = malloc(sizeof(list_s));
    new->perso = malloc(sizeof(tree_s));
    new->perso->name = name;
    new->perso->conjoint = NULL;
    new->perso->enfants = NULL;
    new->perso->frere_soeur = NULL;
    new->perso->parents = NULL;
    new->next = list;
    return new;
}

int main (int ac, char **av)
{
    char **src = filepath_to_arr(av[1]);
    // my_show_word_array(src);
    int index = 0;
    list_s *list_names = NULL;
    for (int i = 0; src[i] && src[i][0] != '#'; i++, index++)
        list_names = add_new_node(list_names, src[i]);


    my_printf("Valeures\n");
    list_s *expl = list_names;
    while (expl) {
        my_printf("Name : %s\n", expl->perso->name);
        expl = expl->next;
    }


    index++;
    my_printf("\n");
    for (int i = index; src[i] && src[i][0] != '#'; i++, index++) {
        char **parse = my_str_parse(src[i], "_");
        tree_s *perso1 = where_is_it(list_names, parse[0]);
        tree_s *perso2 = where_is_it(list_names, parse[1]);
        if (perso1 && perso2) {
            my_printf("%s conj %s\n", parse[0], parse[1]);
            perso2->conjoint = perso1;
            perso1->conjoint = perso2;
        }
        free_my_arr(parse);
    }
    my_printf("\n");

    // for (int i = 0; i < names; i++)
    //     my_printf("perso %s\t conjoint = %s\n", list_names[i].name, list_names[i].conjoint);
    expl = list_names;
    while (expl) {
        my_printf("-> %s conj %s\n", expl->perso->name, expl->perso->conjoint ? expl->perso->conjoint->name : NULL);
        expl = expl->next;
    }
    free_my_arr(src);
    free(list_names);
    return 0;
}
