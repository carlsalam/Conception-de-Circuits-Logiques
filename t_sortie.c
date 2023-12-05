#define _CRT_SECURE_NO_WARNINGS

#include "t_sortie.h"

t_sortie *t_sortie_init(int num)
{
    //Initialisation du pointeur
    t_sortie* nouvelle_sortie;

    //Reservation de memoire pour une nouvelle sortie et verifier si l'allocation a fonctionner
    nouvelle_sortie = (t_sortie*) malloc(sizeof(t_sortie));
    if(nouvelle_sortie == NULL)
    {
        return NULL;
    }

    //Initialisation de l'ID
    nouvelle_sortie->id = num;

    //Réservation de mémoire pour le nom et verifier si malloc fonctionne
    nouvelle_sortie->nom = (char *) malloc(sizeof(char) * NOM_SORTIE_TAILLE_MAX +1);
    if(nouvelle_sortie->nom == NULL)
    {
        free(nouvelle_sortie);
        return NULL;
    }

    sprintf(nouvelle_sortie->nom, "S%d", num); //Formatage

    //mettre l'adresse dans le champs pin de l'enregistrement nouvelle_sortie
    nouvelle_sortie->pin = t_pin_entree_init();

    return nouvelle_sortie;

}


void t_sortie_destroy(t_sortie *sortie)
{
    // verifier si sortie n'est pas null
    if(sortie != NULL)
    {
        // liberer la mémoire pour le nom
        free( sortie -> nom);

        // if si sortie->pin est pas NULL
        if(sortie -> pin != NULL)
        {
            //Liberer la memoire allouée à în
            t_pin_entree_destroy( sortie -> pin);
        }
        //Liberer la memoire de l'enregistrement
        free(sortie);
    }
}


t_pin_entree *t_sortie_get_pin(t_sortie *sortie)
{
    if(sortie == NULL)
    {
        return NULL;
    }

    return sortie -> pin;
}


int t_sortie_relier(t_sortie *dest, t_pin_sortie *source)
{
    if(dest == NULL || source == NULL)
    {
        return 0;
    }

    t_pin_entree_relier(dest -> pin, source);
    return 1;
}

int t_sortie_est_reliee(t_sortie *sortie)
{
    if(sortie == NULL || sortie -> pin == NULL)
    {
        return 0;
    }

    return t_pin_entree_est_reliee(sortie -> pin);
}


void t_sortie_reset(t_sortie *sortie)
{
    if(sortie == NULL)
    {
        return;
    }

    if(sortie -> pin != NULL)
    {
        t_pin_entree_reset(sortie -> pin);
    }
}

int t_sortie_get_valeur(t_sortie *sortie)
{
    if(sortie == NULL || sortie -> pin == NULL)
    {
        return -1;
    }

    return t_pin_entree_get_valeur(sortie -> pin);
}



