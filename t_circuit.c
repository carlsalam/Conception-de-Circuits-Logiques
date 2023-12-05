#include "t_circuit.h"

t_circuit* t_circuit_init(void)
{
    //Allouer de la memoire pour nouveau circuit
    t_circuit* nouveau_circuit;
    nouveau_circuit = (t_circuit*)malloc(sizeof(t_circuit));

    //Si l'allocation de mémoire echoue
    if(nouveau_circuit == NULL)
    {
        return NULL;
    }

    //Initialisation
    nouveau_circuit -> nb_entrees = 0 ;
    nouveau_circuit -> nb_sorties = 0 ;
    nouveau_circuit -> nb_portes = 0 ;

    //Initialisation tab de pointeurs vers entrees
    for(int i = 0; i <MAX_ENTREES; i++)
    {
        nouveau_circuit -> entrees[i] = NULL;
    }
    //Initialisation tab de pointeurs vers sorties
    for(int i = 0; i <MAX_SORTIES; i++)
    {
        nouveau_circuit -> sorties[i] = NULL;
    }
    //Initialisation tab de pointeurs vers portes
    for(int i = 0; i <CIRCUIT_MAX_PORTES; i++)
    {
        nouveau_circuit -> portes[i] = NULL;
    }

    return nouveau_circuit;
}

void t_circuit_destroy(t_circuit *circuit)
{
    //Si circuit NULL
    if(circuit == NULL)
    {
        return;
    }

    // Libérer les entrées
    for (int i = 0; i < MAX_ENTREES; i++)
    {
        if (circuit->entrees[i] != NULL)
        {
            t_entree_destroy(circuit -> entrees[i]);
        }
    }

    // Libérer sorties
    for (int i = 0; i < MAX_SORTIES; i++)
    {
        if (circuit -> sorties[i] != NULL)
        {
            t_sortie_destroy(circuit -> sorties[i]);
        }
    }

    // Libérer les portes
    for (int i = 0; i < CIRCUIT_MAX_PORTES; i++)
    {
        if (circuit -> portes[i] != NULL)
        {
            t_porte_destroy(circuit -> portes[i]);
        }
    }

    // Libérer la mémoire du circuit
    free(circuit);
}



t_porte* t_circuit_ajouter_porte(t_circuit *circuit, e_types_portes le_type)
{
    //Si circuit NULL, ne peut pas ajouter de porte
    if(circuit == NULL)
    {
        return NULL;
    }

    //Si nombre max de portes est atteint on ne peut pas ajouter une nouvelle porte
    if((circuit -> nb_portes) >= CIRCUIT_MAX_PORTES)
    {
        return NULL;
    }

    //creer des nouveaux id
    int id_seul = 0;    //stocker le plus grand id de porte du circuit

    for(int i = 0; i < circuit -> nb_portes; i++)     //for qui parcour le id des porte et trouve le plus grand
    {
        if(circuit -> portes[i] != NULL && circuit -> portes[i] -> id > id_seul)
        {
            id_seul = circuit -> portes[i] -> id;
        }
    }

    id_seul++;  //incremente pour obtenir un id unique

    t_porte* nouvelle_porte = t_porte_init(id_seul, le_type);   //creation d'une nouvelle porte avec le nouveau id
    if(nouvelle_porte == NULL)
    {
        return  NULL;
    }

    circuit -> portes[circuit -> nb_portes] = nouvelle_porte;       //ajouter la nouvelle porte au circuit
    circuit -> nb_portes++;

    return nouvelle_porte;
} //A VERFIFER



t_entree* t_circuit_ajouter_entree(t_circuit * circuit)
{
    //  Verifier si le circuit est NULL
    if(circuit == NULL)
    {
        return NULL;
    }

    //  s'assurer qu'on ne dépasse pas le nombre d'entrées permis
    if(circuit -> nb_entrees >= MAX_ENTREES)
    {
        return NULL;
    }

    //creation des nouveaux id

    int id_seul = 0;    //stocker le plus grand id de porte du circuit

    for (int i = 0; i < circuit -> nb_entrees; i++)
    {
        if(circuit -> entrees[i] != NULL && circuit -> entrees[i]->id > id_seul)
        {
            id_seul = circuit -> entrees[i] -> id;
        }
    }
    //incr pour avoir un id unique
    id_seul++;

    //utiliser ce id dans la nouvelle entree
    t_entree* nouvelle_entree = t_entree_init(id_seul);
    if(nouvelle_entree == NULL)
    {
        return NULL;
    }

    //ajouter cette nouvelle entree dans le circuit
    circuit -> entrees[circuit -> nb_entrees] = nouvelle_entree;
    //actualiser le nombre d'entree dans le circuit
    circuit -> nb_entrees++;

    return nouvelle_entree;
}


t_sortie* t_circuit_ajouter_sortie(t_circuit * circuit)
{
    //  Verifier si le circuit est NULL
    if(circuit == NULL)
    {
        return NULL;
    }

    //  s'assurer qu'on ne dépasse pas le nombre de sorties permis
    if(circuit -> nb_sorties >= MAX_SORTIES)
    {
        return NULL;
    }

    //creation des nouveaux id

    int id_seul = 0;    //stocker le plus grand id de porte du circuit

    for (int i = 0; i < circuit -> nb_sorties; i++)
    {
        if(circuit -> sorties[i] != NULL && circuit -> sorties[i]->id> id_seul)
        {
            id_seul = circuit -> sorties[i] -> id;
        }
    }
    //incr pour avoir un id unique
    id_seul++;

    //utiliser ce id dans la nouvelle sortie
    t_sortie* nouvelle_sortie = t_sortie_init(id_seul);
    if(nouvelle_sortie == NULL)
    {
        return NULL;
    }

    //ajouter cette nouvelle sortie dans le circuit
    circuit -> sorties[circuit -> nb_sorties] = nouvelle_sortie;
    //actualiser le nombre de sortie dans le circuit
    circuit -> nb_sorties++;

    return nouvelle_sortie;
}

/*Description: Vérifie si un circuit donné est un circuit valide. Pour qu'un circuit soit valide
			 toutes les entrées, portes et sorties du circuit doivent être reliées.
NDE: Vous utiliserez les fonctions t_entree_est_reliee, t_sortie_est_reliee et t_porte_est_reliee. */

int t_circuit_est_valide(t_circuit *circuit)
{
    //  Verifier si le circuit est NULL
    if(circuit == NULL)
    {
        return 0;
    }

    //  Verifier si les entrees sont relier
    for (int i = 0; i < circuit -> nb_entrees; ++i)
    {
        if(!t_entree_est_reliee(circuit ->entrees[i]))
        {
            return 0;       //la fonction t_entree_est_reliee va renvoyer faux si la porte n'est pas completement relier
        }
    }

    //  Verifier si les sorties sont relier
    for (int i = 0; i < circuit -> nb_sorties; ++i)
    {
        if(!t_sortie_est_reliee(circuit -> sorties[i]))
        {
            return 0;       //la fonction t_sortie_est_reliee va renvoyer faux si la porte n'est pas completement relier
        }
    }

    //  Verifier si les portes sont relier
    for (int i = 0; i < circuit -> nb_portes; ++i)
    {
        if(!t_porte_est_reliee(circuit ->portes[i]))
        {
            return 0;       //la fonction t_entree_est_reliee va renvoyer faux si la porte n'est pas completement relier
        }
    }

    // si on entre dans aucun des if, alors le circuit est valide
    return 1;
}

/*NDE:
- Vous devez vous assurer que le nombre de bits du signal est suffisant pour alimenter tout le circuit.
  (donc le nombre est au moins égal au nombre d'entrées du circuit)
- Pour appliquer un bit à un entrée, il faut changer la valeur de la pin de sortie de l'entree (champs
  pin dans t_entree).*/

int t_circuit_appliquer_signal(t_circuit * circuit, int signal[], int nb_bits)
{
    if (circuit == NULL || signal == NULL)
    {
        return 0; // if si le circuit n'est pas initier / si le signal est NULL
    }

    if (nb_bits < circuit->nb_entrees)
    {
        return 0; // if si le nombre de bits est insuffisant ( < nb_entree)
    }

    // si on est pas rentrer if, for qui parcour toutes les entree et appliquer le signal aux entrees
    for (int i = 0; i < circuit->nb_entrees; i++)
    {
        // if qui applique le signal au entree si l'entre existe et sa pin de sortie existe
        if (circuit->entrees[i] != NULL && circuit->entrees[i]->pin != NULL)
        {
            // Appliquer le bit à la pin de sortie de l'entrée
            circuit->entrees[i]->pin->valeur = signal[i];
        } else
        {
            return 0; // else si l'entre ou pin sortie existe pas
        }
    }

    return 1; // si on a pas retourner 0, alors le signal a bien ete appliquer, return 1
}

void t_circuit_reset(t_circuit *circuit)
{
    if(circuit == NULL)
    {
        return; //verifier si le circuit n'est pas NULL
    }
    // parcourir toutes les entree, sortie et porte pour reinitialiser le systeme au complet
    // pour les entree
    for (int i = 0; i < circuit -> nb_entrees; i++)
    {
        t_entree_reset(circuit -> entrees[i]);
    }
    // pour les sorties
    for (int i = 0; i < circuit -> nb_sorties; i++)
    {
        t_sortie_reset(circuit -> sorties[i]);
    }
    // pour les portes
    for (int i = 0; i < circuit -> nb_portes; i++)
    {
        t_porte_reset(circuit -> portes[i]);
    }
}


int t_circuit_propager_signal(t_circuit *circuit)
{
    //initier var locale
    int nb_portes = circuit -> nb_portes;


// if pour si le circuit est invalide ou n'existe pas
    if (circuit == NULL || !t_circuit_est_valide(circuit))
    {
        return 0;
    }

    // Appliquer le signal aux entrées du circuit
    for (int i = 0; i < circuit->nb_entrees; i++)
    {
        t_entree_propager_signal(circuit->entrees[i]);
    }

    // Initialiser la file de portes file
    t_file_porte* file = t_file_porte_initialiser(CIRCUIT_MAX_PORTES);

    // Ajouter toutes les portes du circuit à la file
    for (int i = 0; i < circuit->nb_portes; i++)
    {
        t_file_porte_enfiler(file, circuit->portes[i]);
    }

    int iter = 0;

    while (!t_file_porte_est_vide(file) && iter < nb_portes * (nb_portes + 1) /2)
    {
        // Défiler une porte de la file
        t_porte *porte_courante = t_file_porte_defiler(file);

        // Propager le signal de la porte
        if (!t_porte_propager_signal(porte_courante))
        {
            // Si la porte n'a pas réussi à propager son signal, la remettre dans la file
            t_file_porte_enfiler(file, porte_courante);
        }

        iter++;
    }

    // Libérer la mémoire occupée par la file
    free(file);

    ////pas sur du free

    // Si la file n'est pas vide, cela signifie qu'il y a une boucle dans le circuit
    if (!t_file_porte_est_vide(file))
    {
        return 0;
    }

    return 1; // Si on rentre dans aucuns des return 0, le signale s'est bien propagee
}



