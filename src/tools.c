/*
** EPITECH PROJECT, 2022
** tools jam
** File description:
** Familly
*/

#include "my.h"
#include "jam_familly.h"

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
    new->perso->nbr_enfants = 0;
    new->perso->conjoint = NULL;
    new->perso->enfants = NULL;
    new->perso->parent_1 = NULL;
    new->perso->parent_2 = NULL;
    new->next = list;
    return new;
}

void print_all_perso (list_s *list)
{
    // * on affiche le tout
    while (list) {
        my_printf("%sNAME : %s\n%s", MY_COLOR_BLUE, list->perso->name, MY_COLOR_RESET);
        my_printf("conj    :\t%s\n", list->perso->conjoint ? list->perso->conjoint->name : NULL);
        my_printf("parent  :\t%s and %s\n",
        list->perso->parent_1 ? list->perso->parent_1->name : NULL,
        list->perso->parent_2 ? list->perso->parent_2->name : NULL);
        my_printf("enfants :\t");
        for (int i = 0; i < list->perso->nbr_enfants; i++)
            my_printf("%s\t", list->perso->enfants[i]->name);
        my_printf("\n\n\n");
        list = list->next;
    }
}

void free_all_perso (list_s *list)
{
    // * on affiche le tout
    while (list) {
        list_s *tmp = list;
        list = list->next;
        free(tmp->perso->name);
        if (tmp->perso->nbr_enfants > 0)
            free(tmp->perso->enfants);
        free(tmp->perso);
        free(tmp);
    }
}
