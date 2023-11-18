#define _CRT_SECURE_NO_WARNINGS
#include "t_entree.h"


t_entree *t_entree_init(int num)
{

    //Initialisation du pointeur vers NULL
    t_entree* nouvelle_entree = NULL;

    //Réservation de mémoire pour la nouvelle entrée et verifier si malloc fonctionne
    nouvelle_entree = (t_entree*) malloc(sizeof(t_entree));
    if(nouvelle_entree == NULL)
    {
        return NULL;
    }

    //Initialisation de l'ID
    nouvelle_entree->id = num;


    char entree[10]; //Initialisation d'une chaine de caractère où l'on va stocker le nom.
    sprintf(entree, "E%d", num); //Formatage

    //Réservation de mémoire pour le nom et verifier si malloc fonctionne
    nouvelle_entree->nom = (char *) malloc(strlen(entree) + 1);
    if(nouvelle_entree->nom == NULL)
    {
        free(nouvelle_entree);
        return NULL;
    }
    //Copier le nom dans nouvelle entrée
    strcpy(nouvelle_entree->nom, entree);

    //Initialisation du pin de sortie à NULL
    nouvelle_entree->pin = NULL;

    return nouvelle_entree;
}