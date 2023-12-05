#include "t_circuit.h"
#include "t_entree.h"
#include "t_file_porte.h"
#include "t_pin_entree.h"
#include "t_pin_sortie.h"
#include "t_porte.h"
#include "t_sortie.h"



int main(void) {


    //déclaration des variables
    int signal[3];
    t_circuit *circuit;
    t_porte *porte_ou;
    t_porte *porte_et;
    t_porte *porte_not;
    t_porte *porte_xor;
    t_entree *entree0;
    t_entree *entree1;
    t_entree *entree2;
    t_sortie *sortie0;

//Création du circuit
    circuit = t_circuit_init();

//Ajout des portes
    porte_ou = t_circuit_ajouter_porte(circuit, PORTE_OU);
    porte_et = t_circuit_ajouter_porte(circuit, PORTE_ET);
    porte_not = t_circuit_ajouter_porte(circuit, PORTE_NOT);
    porte_xor = t_circuit_ajouter_porte(circuit, PORTE_XOR);

//Ajout des entrées
    entree0 = t_circuit_ajouter_entree(circuit);
    entree1 = t_circuit_ajouter_entree(circuit);
    entree2 = t_circuit_ajouter_entree(circuit);

//Ajout des sorties
    sortie0 = t_circuit_ajouter_sortie(circuit);

//Ajout de liens
    t_porte_relier(porte_ou, 0, t_entree_get_pin(entree0));
    t_porte_relier(porte_ou, 1, t_entree_get_pin(entree1));
    t_porte_relier(porte_et, 0, t_entree_get_pin(entree1));
    t_porte_relier(porte_et, 1, t_entree_get_pin(entree2));
    t_porte_relier(porte_not, 0, t_porte_get_pin_sortie(porte_ou));
    t_porte_relier(porte_xor, 0, t_porte_get_pin_sortie(porte_not));
    t_porte_relier(porte_xor, 1, t_porte_get_pin_sortie(porte_et));
    t_sortie_relier(sortie0, t_porte_get_pin_sortie(porte_xor));

//Vérification de la validité du circuit
    if (t_circuit_est_valide(circuit)) {
        printf("Circuit valide!\n");
    } else {
        printf("Circuit invalide!\n");
    }
//On définit un signal de 3 bits (111)
    signal[0] = 1;
    signal[1] = 1;
    signal[2] = 1;
    t_circuit_reset(circuit);
    t_circuit_appliquer_signal(circuit, signal, 3);
    if (t_circuit_propager_signal(circuit))
    {
        printf("Signal propage avec succes.\n");
        printf("Sortie 0: %d\n", t_sortie_get_valeur(sortie0));
    } else
    {
        printf("Erreur lors de la propagation du signal.\n");
    }
    t_circuit_destroy(circuit);
    system("pause");
}