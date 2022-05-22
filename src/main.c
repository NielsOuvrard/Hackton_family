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
    int nbr_enfants;
    struct tree_s *conjoint;
    // struct tree_s *parents;
    struct tree_s **enfants;
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
    new->perso->nbr_enfants = 0;
    new->perso->conjoint = NULL;
    new->perso->enfants = NULL;
    // new->perso->parents = NULL;
    new->next = list;
    return new;
}

void ajoute_un_enfant (tree_s *parent, tree_s *enfant)
{
    tree_s **enfants_perso1 = malloc(sizeof(tree_s *) * (parent->nbr_enfants + 1));
    // on copie l'ancien tableau dans le nouveau
    for (int j = 0; j < parent->nbr_enfants; j++)
        enfants_perso1[j] = parent->enfants[j];
    enfants_perso1[parent->nbr_enfants] = enfant;
    // si on avait déjà créé un tableau d'enfant, on le free
    if (parent->nbr_enfants > 0)
        free(parent->enfants);
    parent->enfants = enfants_perso1;
    parent->nbr_enfants++;
}

void print_all_perso (list_s *list)
{
    // * on affiche le tout
    while (list) {
        my_printf("%sNAME : %s\n%s", MY_COLOR_BLUE, list->perso->name, MY_COLOR_RESET);
        my_printf("conj    :\t%s\n", list->perso->conjoint ? list->perso->conjoint->name : NULL);
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

int main (int ac, char **av)
{
    // * array du fichier
    char **src = filepath_to_arr(av[1]);
    int index = 0;

    // * personnes dans noeuds individuels tree_s
    list_s *list_names = NULL;
    for (int i = 0; src[i] && src[i][0] != '#'; i++, index++)
        list_names = add_new_node(list_names, src[i]);

    // * on relie les noeuds à leurs couples
    for (int i = ++index; src[i] && src[i][0] != '#'; i++, index++) {
        // on parse dans un array selon les '_'
        char **parse = my_str_parse(src[i], "_");
        // parse 1 = conj 1
        // Parse 2 = conj 2
        tree_s *perso1 = where_is_it(list_names, parse[0]);
        tree_s *perso2 = where_is_it(list_names, parse[1]);
        if (!perso1 || !perso2) // gestion d'erreure
            return 84;
        perso2->conjoint = perso1;
        perso1->conjoint = perso2;
        free_my_arr(parse);
    }

    // * on relie les couples à leurs enfants
    for (int i = ++index; src[i] && src[i][0] != '#'; i++, index++) {
        // on parse dans un array selon les '_' et les '-'
        char **parse = my_str_parse(src[i], "_-");
        // parse 1 = Pere
        // Parse 2 = Mere
        // Parse 3 = Enfant
        tree_s *perso1 = where_is_it(list_names, parse[0]);
        tree_s *perso2 = where_is_it(list_names, parse[1]);
        tree_s *enfant = where_is_it(list_names, parse[2]);
        if (!perso1 || !perso2 || !enfant) // gestion d'erreure
            return 84;
        ajoute_un_enfant(perso1, enfant);
        ajoute_un_enfant(perso2, enfant);
        free_my_arr(parse);
    }

    // * afficher
    print_all_perso(list_names);

    // * free
    free_all_perso(list_names);
    free(src);
    return 0;
}
