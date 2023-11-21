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
    snprintf(nom_porte, NOM_PORTE_TAILLE_MAX, "P%d", id);
    nouvelle_porte -> nom = strdup(nom_porte);

    nouvelle_porte -> type = type;


    int nb_entrees;

    //Initislidstion des pins d'entrée en fonction du type de porte
    switch (type) {
        case PORTE_NOT:
            nouvelle_porte -> nb_entrees = 1;
            break;
        case PORTE_ET:
        case PORTE_OU:
        case PORTE_XOR:
            // Assumption: Ces types de portes nécessitent 2 entrées, ajustez selon vos besoins
            nouvelle_porte -> nb_entrees = 2;
            break;
        default:
            // Gérer d'autres types de portes ou retourner une erreur si le type est inconnu
            free(nouvelle_porte -> nom);
            free(nouvelle_porte);
            return NULL;
    }

    for(int i = 0; i <nb_entrees; i++)
    {
        nouvelle_porte -> entrees[i] = t_pin_entree_init();
        if(nouvelle_porte -> entrees[i] == NULL)
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
    if(nouvelle_porte -> nom == NULL)
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
    if(porte != NULL)
    {
        free(porte -> nom);

        //Liberer chaque pin entree assoiee a la porte
        for(int i =0; i < (porte -> nb_entrees); i++)
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
        return;
    }

    int res = 0; //jsp

    switch (porte->type) {
        case PORTE_ET:
            res = t_pin_sortie_get_valeur(porte->entrees[0]) & t_pin_sortie_get_valeur(porte->entrees[1]);
            break;
        case PORTE_OU:
            res = t_pin_sortie_get_valeur(porte->entrees[0]) | t_pin_sortie_get_valeur(porte->entrees[1]);
            break;
        case PORTE_NOT:
            res = !t_pin_sortie_get_valeur(porte->entrees[0]);
            break;
        case PORTE_XOR:
            res = t_pin_sortie_get_valeur(porte->entrees[0]) ^ t_pin_sortie_get_valeur(porte->entrees[1]);
            break;
        default:
            return;
    }

    //Définir valeur pin sortie
    t_pin_sortie_set_valeur(porte -> sortie, res);
}

int t_porte_relier(t_porte *dest, int num_entree, t_pin_sortie *source)
{
    //Validité pointeur dest et source
    if(dest == NULL || source == NULL)
    {
        return 0;
    }

    //indice valide?
    if(num_entree < 0 || num_entree >= MAX_ENTREES || num_entree >= (dest -> nb_entrees))
    {
        return 0; //Faux si indice = non valide
    }

    //Relier pin_entree a pin_sortie de la source
    t_pin_entree_relier(dest -> entrees[num_entree], source);

    //Retourne 1 quand la la liaison est faite avec succès
    return 1;
}

int t_porte_est_reliee(t_porte *porte)
{
    //Si la porte est null retourner 0
    if(porte == NULL)
    {
        return 0;
    }

    //Si pin de sortie n'est pas reliée retourner 0
    if(!t_pin_sortie_est_reliee(porte -> sortie))
    {
        return 0;
    }

    //Si les pins d'entrée sont inter relier
    for(int i = 0; i < porte -> nb_entrees; i++)
    {
        if(!t_pin_entree_est_reliee(porte -> entrees[i]))
        {
            return 0;
        }
    }

    //Vrai aussi-no
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

    //toutes les pins d'entrée ont reçu un signal
    for (int i = 0; i < porte -> nb_entrees; i++)
    {
        // Si une des entrées n'a pas reçu de signal
        if (t_pin_sortie_get_valeur(porte -> entrees[i]) == -1)
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