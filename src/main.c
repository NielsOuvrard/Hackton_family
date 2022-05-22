/*
** EPITECH PROJECT, 2022
** Jam
** File description:
** familly
*/

#include "my.h"
#include "jam_familly.h"

void ajoute_un_enfant (tree_s *parent, tree_s *enfant)
{
    tree_s **enfants_perso1 = malloc(sizeof(tree_s *) * (parent->nbr_enfants + 1));
    // on copie l'ancien tableau dans le nouveau
    for (int j = 0; j < parent->nbr_enfants; j++)
        enfants_perso1[j] = parent->enfants[j];
    enfants_perso1[parent->nbr_enfants] = enfant;
    // enfant->parents = parent;
    // si on avait déjà créé un tableau d'enfant, on le free
    if (parent->nbr_enfants > 0)
        free(parent->enfants);
    parent->enfants = enfants_perso1;
    parent->nbr_enfants++;
}

int deep_tree (tree_s* node)
{
    if (node == NULL)
        return -1;
    int deep = 0;
    for (int i = 0; i < node->nbr_enfants; i++) {
        int tmp;
        if ((tmp = deep_tree(node->enfants[i])) > deep)
            deep = tmp;
    }
    return deep + 1;
}

int le_plus_haut_dans_arbre (list_s *list_names)
{
    int deep = 0, id = 0, id_most_deep = 0;
    while (list_names) {
        // my_printf("profondeur de %s\n", list_names->perso->name);
        int tmp;
        if ((tmp = deep_tree(list_names->perso)) > deep) {
            deep = tmp;
            id_most_deep = id;
        }
        // my_printf("%d\n\n", );
        list_names = list_names->next;
        id++;
    }
    return id_most_deep;
}

void disp_enfants (tree_s *node);

void disp_conjoint (tree_s *node)
{
    my_printf("%s - %s\n", node->name, node->conjoint ? node->conjoint->name : NULL);
    my_printf("   |\n");
    disp_enfants(node);
}

void disp_enfants (tree_s *node)
{
    for (int i = 0; i < node->nbr_enfants; i++) {
        if (node->enfants[i]->conjoint) {
            disp_conjoint(node->enfants[i]);
        } else {
            my_printf("%s", node->enfants[i]->name);
            for (int j = 0; j < node->nbr_enfants; j++)
                my_putchar(' ');
        }
    }
}

void print_according_to_tree (list_s *list_names)
{
    list_s *most_old = list_names;
    int deep = le_plus_haut_dans_arbre(list_names);
    for (int i = 0; i < deep; i++)
        most_old = most_old->next;
    disp_conjoint(most_old->perso);
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
        enfant->parent_1 = perso1;
        ajoute_un_enfant(perso2, enfant);
        enfant->parent_2 = perso2;
        free_my_arr(parse);
    }

    // * afficher
    // print_all_perso(list_names);

    print_according_to_tree(list_names);
    my_putchar('\n');

    // * free
    free_all_perso(list_names);
    free(src);
    return 0;
}
