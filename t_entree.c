//
// Created by csala on 2023-11-17.
//



#include "t_entree.h"



t_entree *t_entree_init(int num)
{
    t_entree* nouvel_entree = NULL;

    nouvel_entree = (t_entree*) malloc(sizeof(t_entree));
    if(nouvel_entree == NULL)
    {
        return NULL;
    }

    nouvel_entree->id = num;


    char entree[12];
    sprintf(entree, "E%d", num);

    nouvel_entree->nom = (char *) malloc(strlen(entree) + 1);

    if(nouvel_entree->nom == NULL)
    {
        free(nouvel_entree);
        return NULL;
    }
    strcpy(nouvel_entree->nom, entree);

    nouvel_entree->pin = NULL;

    return nouvel_entree;
}