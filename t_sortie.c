#define _CRT_SECURE_NO_WARNINGS

#include "t_sortie.h"

t_sortie *t_sortie_init(int num)
{
    //Initialisation du pointeur
    t_sortie* nouvelle_sortie = NULL;

    //Reservation de memoire pour une nouvelle sortie et verifier si l'allocation a fonctionner
    nouvelle_sortie = (t_sortie*) malloc(sizeof(t_sortie));
    if(nouvelle_sortie == NULL)
    {
        return NULL;
    }

    //Initialisation de l'ID
    nouvelle_sortie->id = num;

    char sortie[10]; //Initialisation d'une chaine de caractère où l'on va stocker le nom.
    sprintf(sortie, "S%d", num); //Formatage

    //Réservation de mémoire pour le nom et verifier si malloc fonctionne
    nouvelle_sortie->nom = (char *) malloc(strlen(sortie) + 1);
    if(nouvelle_sortie->nom == NULL)
    {
        free(nouvelle_sortie);
        return NULL;
    }
    //Copier le nom dans nouvelle entrée
    strcpy(nouvelle_sortie->nom, sortie);

    //Initialisation du pin de sortie à NULL
    nouvelle_sortie->pin = NULL;

    return nouvelle_sortie;

}
