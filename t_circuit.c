#include "t_circuit.h"

t_circuit* t_circuit_init(void)
{
    //Allouer de la memoire pour nouveau circuit
    t_circuit *nouveau_circuit;
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
    for (int i = 0; i < circuit -> nb_entrees; i++)
    {
        if (circuit->entrees[i] != NULL)
        {
            t_entree_destroy(circuit -> entrees[i]);
        }
    }

    // Libérer sorties
    for (int i = 0; i < circuit -> nb_sorties; i++)
    {
        if (circuit -> sorties[i] != NULL)
        {
            t_sortie_destroy(circuit -> sorties[i]);
        }
    }

    // Libérer les portes
    for (int i = 0; i < circuit -> nb_portes; i++)
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

    int id_seul = 0;
    for(int i = 0; i < (circuit -> nb_portes); i++)
    {
        if(circuit -> portes[i] != NULL && circuit -> portes[i] -> id > id_seul)
        {
            id_seul = circuit -> portes[i] -> id;
        }
    }

    id_seul++;

    t_porte *nouvelle_porte;
    nouvelle_porte = t_porte_init(id_seul, le_type);
    if(nouvelle_porte == NULL)
    {
        return  NULL;
    }

    circuit -> portes[circuit -> nb_portes] = nouvelle_porte;
    circuit -> nb_portes++;

    return nouvelle_porte;
}





t_entree* t_circuit_ajouter_entree(t_circuit * circuit);
t_sortie* t_circuit_ajouter_sortie(t_circuit * circuit);
int t_circuit_est_valide(t_circuit *circuit);
int t_circuit_appliquer_signal(t_circuit * circuit, int signal[], int nb_bits);
void t_circuit_reset(t_circuit *circuit);
int t_circuit_propager_signal(t_circuit *circuit);