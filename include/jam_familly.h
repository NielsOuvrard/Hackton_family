/*
** EPITECH PROJECT, 2022
** Jam fammilly
** File description:
** header
*/

#pragma once

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
    struct tree_s *parent_1;
    struct tree_s *parent_2;
    struct tree_s **enfants;
} tree_s;

typedef struct list_s {
    tree_s *perso;
    struct list_s *next;
} list_s;

char **filepath_to_arr(char *filepath);

char **my_str_parse (char *str, char *part);


// tools

tree_s *where_is_it (list_s *list, char *name);

list_s *add_new_node (list_s *list, char *name);

void print_all_perso (list_s *list);

void free_all_perso (list_s *list);
