#include "fonctions_test_circuit.h"
#include <assert.h>


void test_t_circuit_init(void)
{
    t_circuit* circuit = t_circuit_init();
    assert(circuit != NULL);

    // Vérifie que la taille des tableaux est initialisée à 0
    assert(circuit->nb_entrees == 0);
    assert(circuit->nb_sorties == 0);
    assert(circuit->nb_portes == 0);

    free(circuit);
}


void test_t_circuit_ajouter_porte(void)
{
    t_circuit* circuit = t_circuit_init();

    circuit->nb_portes = 10;
    t_porte* porte = t_circuit_ajouter_porte(circuit, PORTE_ET);

    // Vérifie que la porte a le bon type et que le tableau de portes a la bonne taille
    // ainsi que les bons éléments
    assert(porte != NULL);
    assert(porte->type == PORTE_ET);
    assert(circuit->portes[10] == porte);
    assert(circuit->nb_portes == 11);

    circuit->nb_portes = 101;
    t_porte* nouvelle_porte = t_circuit_ajouter_porte(circuit, PORTE_NOT);

    assert(nouvelle_porte == NULL); // La taille est plus grande que la limite permise de 100

    free(porte);
    free(nouvelle_porte);
}

void test_t_circuit_ajouter_entree(void)
{
    t_circuit* circuit = t_circuit_init();

    circuit->nb_entrees = 5;
    t_entree* entree = t_circuit_ajouter_entree(circuit);

    // Vérifie que l'entrée à l'id et le nom supposé et est présent dans la bonne case du tableau
    assert(entree != NULL);
    assert(entree->id == 5);
    assert(circuit->entrees[5] == entree);
    assert(strcmp(entree->nom, "E5") == 0);
    assert(circuit->nb_entrees == 6); // Vérifie que la taille du tableau a été mise à jour

    circuit->nb_entrees = 51;
    t_entree* nouvelle_entree = t_circuit_ajouter_entree(circuit);

    assert(nouvelle_entree == NULL); // Le tableau dépasse la taille limite de 50

    free(entree);
    free(nouvelle_entree);
}

void test_t_circuit_ajouter_sortie(void)
{
    t_circuit* circuit = t_circuit_init();

    circuit->nb_sorties = 5;
    t_sortie* sortie = t_circuit_ajouter_sortie(circuit);

    // Vérifie que l'entrée à l'id et le nom supposé et est présent dans la bonne case du tableau
    assert(sortie != NULL);
    assert(sortie->id == 5);
    assert(circuit->sorties[5] == sortie);
    assert(strcmp(sortie->nom, "S5") == 0);
    assert(circuit->nb_sorties == 6); // Vérifie que la taille du tableau a été mise à jour

    circuit->nb_sorties = 51;
    t_sortie* nouvelle_sortie = t_circuit_ajouter_sortie(circuit);

    assert(nouvelle_sortie == NULL); // Le tableau dépasse la taille limite de 50

    free(sortie);
    free(nouvelle_sortie);
}

void test_t_circuit_est_valide(void)
{
    t_circuit* circuit = t_circuit_init();
    circuit->nb_portes = 2;
    circuit->nb_sorties = 2;
    circuit->nb_entrees = 2;

    // Création des entrées
    t_entree* entree1 = t_entree_init(0);
    t_entree* entree2 = t_entree_init(1);
    circuit->entrees[0] = entree1;
    circuit->entrees[1] = entree2;

    // Création des sorties
    t_sortie* sortie1 = t_sortie_init(0);
    t_sortie* sortie2 = t_sortie_init(1);
    circuit->sorties[0] = sortie1;
    circuit->sorties[1] = sortie2;

    // Création des portes
    t_porte* porte1 = t_porte_init(0, PORTE_ET);
    t_porte* porte2 = t_porte_init(0, PORTE_XOR);
    circuit->portes[0] = porte1;
    circuit->portes[1] = porte2;

    t_porte_relier(porte1, 0, t_entree_get_pin(entree1));
    t_porte_relier(porte1, 1, t_entree_get_pin(entree2));

    // porte2, sortie1 et sortie2 ne sont pas reliés
    assert(t_circuit_est_valide(circuit) == 0);

    t_porte_relier(porte2, 0 , t_entree_get_pin(entree1));
    t_porte_relier(porte2, 1 , t_entree_get_pin(entree2));

    // sortie1 et sortie2 ne sont pas reliés
    assert(t_circuit_est_valide(circuit) == 0);

    t_sortie_relier(sortie1, t_porte_get_pin_sortie(porte1));
    t_sortie_relier(sortie2, t_porte_get_pin_sortie(porte2));

    // Tous les éléments sont reliés
    assert(t_circuit_est_valide(circuit) != 0);

    free(circuit);
    free(entree1);
    free(entree2);
    free(sortie1);
    free(sortie2);
    free(porte1);
    free(porte2);
}

void test_t_circuit_appliquer_signal(void)
{
    t_circuit* circuit = t_circuit_init();
    circuit->nb_entrees = 2;

    int signal[] = {0,1,1,0,1};
    int nb_bits = 1;

    assert(t_circuit_appliquer_signal(circuit, signal, nb_bits) == 0); // Il n'y a pas assez de bits

    t_entree* entree1 = t_entree_init(0);
    t_entree* entree2 = t_entree_init(1);
    circuit->entrees[0] = entree1;
    circuit->entrees[1] = entree2;

    // Vérifie que le signal a été appliqué et que les pins d'entrée ont les bonnes valeurs
    // (0 et 1, respectivement)
    assert(t_circuit_appliquer_signal(circuit, signal, 2) != 0);
    assert(circuit->entrees[0]->pin->valeur == 0);
    assert(circuit->entrees[1]->pin->valeur == 1);

    free(entree1);
    free(entree2);
    free(circuit);
}

void test_t_circuit_reset(void)
{
    t_circuit* circuit = t_circuit_init();

    // Création des entrées
    t_entree* entree1 = t_entree_init(0);
    t_entree* entree2 = t_entree_init(1);
    circuit->entrees[0] = entree1;
    circuit->entrees[1] = entree2;

    // Création des sorties
    t_sortie* sortie1 = t_sortie_init(0);
    t_sortie* sortie2 = t_sortie_init(1);
    t_sortie* sortie3 = t_sortie_init(2);
    circuit->sorties[0] = sortie1;
    circuit->sorties[1] = sortie2;
    circuit->sorties[2] = sortie3;

    // Changement de la valeur des pins
    sortie1->pin->valeur = 1;
    sortie2->pin->valeur = -5;
    sortie3->pin->valeur = 0;
    entree1->pin->valeur = 10;
    // Le circuit n'a pas de portes et entree2 a sa valeur par défaut

    circuit->nb_entrees = 2;
    circuit->nb_sorties = 2; // Plus petit que le nombre réel d'entrées
    t_circuit_reset(circuit);

    // Les deux premières entrées et sorties ont été réinitialisé
    assert(circuit->entrees[0]->pin->valeur == -1);
    assert(circuit->entrees[1]->pin->valeur == -1);
    assert(circuit->sorties[0]->pin->valeur == -1);
    assert(circuit->sorties[1]->pin->valeur == -1);

    // La troisième entrée n'a pas été réinitalisée
    assert(circuit->sorties[2]->pin->valeur != -1);

    free(entree1);
    free(entree2);
    free(sortie1);
    free(sortie2);
    free(sortie3);
    free(circuit);
}

void test_circuit_propager_signal(void)
{
    t_circuit* circuit = t_circuit_init();

    // Création du circuit
    t_porte* porte = t_porte_init(1, PORTE_ET);
    t_entree* entree = t_entree_init(1);
    t_sortie* sortie = t_sortie_init(1);

    circuit->nb_entrees = 1;
    circuit->nb_sorties = 1;
    circuit->nb_portes = 1;

    // Le circuit n'est pas valide car les composantes ne sont pas reliées
    assert(t_circuit_propager_signal(circuit) == 0);

    t_porte_relier(porte, 0, entree->pin);
    t_sortie_relier(sortie, t_porte_get_pin_sortie(porte));

    // Le circuit est valide et ne contient pas de boucles
    assert(t_circuit_propager_signal(circuit) != 0);
}
