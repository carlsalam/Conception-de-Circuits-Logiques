#include "t_porte.h"


t_porte *t_porte_init(int id, e_types_portes type)
{
    //Memoire alloué pour *nouvelle_porte
    t_porte *nouvelle_porte;
    nouvelle_porte = (t_porte*)malloc(sizeof(t_porte));

    if(nouvelle_porte == NULL)
    {
        return NULL;
    }

    nouvelle_porte -> id = id;

    char nom_porte[NOM_PORTE_TAILLE_MAX];
    snprintf(nom_porte, NOM_PORTE_TAILLE_MAX, "P%d", id);// sprintf mais avec la taille

//    nouvelle_porte -> nom = strdup(nom_porte);            g remplacer ca par:

    nouvelle_porte->nom = (char*)malloc(strlen(nom_porte) + 1); //+1 pour le caractere nul en fin de chaine
    if (nouvelle_porte->nom == NULL)        //if au cas ou l'initialisation de la porte echoue
    {
        for (int i = 0; i < nouvelle_porte -> nb_entrees; i++)
        {
            t_pin_entree_destroy(nouvelle_porte -> entrees[i]);
        }
        free(nouvelle_porte);
        return NULL;
    }
    strcpy(nouvelle_porte -> nom, nom_porte);     //copier le tableau nom_porte dans nouvelle_porte -> nom


    nouvelle_porte -> type = type;


//    int nb_entrees; //???

    //Initislidstion des pins d'entrée en fonction du type de porte
    switch (type) {
            //la porte NOT est la seule qui a une entree
        case PORTE_NOT:
            nouvelle_porte -> nb_entrees = 1;
            break;
        case PORTE_ET:
        case PORTE_OU:
        case PORTE_XOR:
            // Les portes OU, ET et XOR on 2 entrees
            nouvelle_porte -> nb_entrees = 2;
            break;
        default:
            // Autres type de portes ou retourner erreur si type inconnu
            free(nouvelle_porte -> nom);
            free(nouvelle_porte);
            return NULL;
    }

    //parcour le nombre d'entree de chaque type de portes
    for(int i = 0; i <nouvelle_porte -> nb_entrees; i++)
    {
        nouvelle_porte -> entrees[i] = t_pin_entree_init();     //allocation et init du pin d'entree

        if(nouvelle_porte -> entrees[i] == NULL)        //if au cas ou l'initialisation echoue
        {
            free(nouvelle_porte -> nom);
            for (int j = 0; j < i; j++)
            {
                free(nouvelle_porte->entrees[j]);
            }
            free(nouvelle_porte);
            return NULL;
        }
    }

    //Initialisation pin sortie
    nouvelle_porte -> sortie = t_pin_sortie_init();
    if(nouvelle_porte -> nom == NULL)           //if au cas ou l'initialisation echoue : free chaque nom de porte et les pin de sortie
    {
        free(nouvelle_porte -> nom);
        for(int i = 0; i < (nouvelle_porte -> nb_entrees); i++)
        {
            free(nouvelle_porte -> entrees[i]);
        }
        free(nouvelle_porte);
        return NULL;
    }

    return nouvelle_porte;
}


void t_porte_destroy(t_porte *porte)
{
    if(porte != NULL)   //if pour ne pas liberer de la memoire qui n'a pas ete initialisee
    {
        free(porte -> nom);

        //Liberer chaque pin entree assoiee a la porte
        for(int i = 0; i < porte -> nb_entrees; i++)
        {
            if(porte -> entrees[i] != NULL)
            {
                t_pin_entree_destroy(porte -> entrees[i]);
            }
        }

        //Liberer la pin sortie porte
        if(porte -> sortie != NULL)
        {
            t_pin_sortie_destroy(porte -> sortie);
        }
        //Liberer memoir de t_porte
        free(porte);
    }
}


void t_porte_calculer_sorties(t_porte *porte)
{
    //Si porte = NULL ou si pin = non definie rien a faire
    if(porte == NULL || porte -> sortie == NULL)
    {
        return;     //termine la fonction sans faire les calculs si la porte ou la sortie n'est pas definie
    }

    int res = 0; // Variable de résultat pour stocker le resultat du calcul logique

    switch (porte->type)
    {
        case PORTE_ET:
            res = t_pin_entree_est_reliee(porte->entrees[0]) & t_pin_entree_get_valeur(porte->entrees[1]);
            break;
        case PORTE_OU:
            res = t_pin_entree_est_reliee(porte->entrees[0]) | t_pin_entree_get_valeur(porte->entrees[1]);
            break;
        case PORTE_NOT:
            res = !t_pin_entree_get_valeur(porte->entrees[0]);  // seule porte avec 1 pin d'entree
            break;
        case PORTE_XOR:
            res = t_pin_entree_get_valeur(porte->entrees[0]) ^ t_pin_entree_get_valeur(porte->entrees[1]);
            break;
        default:
            return;
    }

    //Définir valeur pin sortie apres l'obtention du resultat du calcul
    t_pin_sortie_set_valeur(porte -> sortie, res);
}

int t_porte_relier(t_porte *dest, int num_entree, t_pin_sortie *source)
{
    //verifie si la porte destination et le pointeur source sont bien definie
    if(dest == NULL || source == NULL)
    {
        return 0;
    }

    //indice d'entree valide?
    if(num_entree < 0 || num_entree >= MAX_ENTREES || num_entree >= (dest -> nb_entrees))
    {
        return 0; //Faux si indice = non valide
    }

    //Relier l'entree de la porte a pin_sortie de la source
    t_pin_entree_relier(dest->entrees[num_entree], source);

    //Retourne 1 quand la liaison est faite avec succès
    return 1;
}

int t_porte_est_reliee(t_porte *porte)
{
    //if si la porte n'est initialisee
    if(porte == NULL)
    {
        return 0;
    }

    //Si pin de sortie n'est pas reliée (n'est pas vrai) retourner 0
    if(!t_pin_sortie_est_reliee(porte -> sortie))
    {
        return 0;
    }

    //Si les pins d'entrée sont inter relier
    for(int i = 0; i < porte -> nb_entrees; i++)
    {
        if(!t_pin_entree_est_reliee(porte -> entrees[i]))
        {
            return 0;       //if pour si une pin d'entree n'est pas relier
        }
    }

    if (!t_pin_sortie_est_reliee(porte->sortie))
    {
        return 0;       //if pour si la pin de sortie n'est pas relier
    }

    //sinon, la porte est relier (vrai)
    return 1;
}

void t_porte_reset(t_porte *porte)
{
    //Si porte = NULL
    if(porte == NULL)
    {
        return;
    }

    //Reinitialisation pin_entree
    for (int i = 0; i < porte->nb_entrees; i++)
    {
        if (porte->entrees[i] != NULL)
        {
            t_pin_entree_reset(porte->entrees[i]);
        }
    }

    // Réinitialisation pin_sortie
    if (porte->sortie != NULL)
    {
        t_pin_sortie_reset(porte->sortie);
    }
}

int t_porte_propager_signal(t_porte *porte)
{
    //si la porte est NULL
    if (porte == NULL)
    {
        return 0;
    }

    // Verifier si toutes les pins d'entrée ont reçu un signal
    for (int i = 0; i < porte -> nb_entrees; i++)
    {
        // Si une des entrées n'a pas reçu de signal
        if (t_pin_entree_get_valeur(porte -> entrees[i]) == -1)
        {
            return 0;
        }
    }

    // Calculer la valeur de la sortie en fonction du type de la porte
    t_porte_calculer_sorties(porte);

    // Propager le signal à partir de la pin_sortie de la porte
    return t_pin_sortie_propager_signal(porte -> sortie);
}

t_pin_sortie* t_porte_get_pin_sortie(t_porte* porte)
{
    //Si la porte est NULL
    if(porte == NULL)
    {
        return NULL;
    }
    //Retour pointeur vers pin sortie de la porte
    return porte -> sortie;
}