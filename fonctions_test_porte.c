
#include "fonctions_test_porte.h"



// Teste l'initialisation d'une porte (gate)
void test_t_porte_init(void) {
    // Création de différents types de portes et vérification de leur création correcte
    t_porte* porte = t_porte_init(0, PORTE_ET);
    t_porte* porte1 = t_porte_init(1, PORTE_OU);
    t_porte* porte2 = t_porte_init(287, PORTE_NOT);
    t_porte* porte3 = t_porte_init(3, PORTE_XOR);

    // Test des 4 types de portes
    assert(porte != NULL);
    assert(porte1 != NULL);
    assert(porte2 != NULL);
    assert(porte3 != NULL);

    // Vérifications supplémentaires sur les propriétés de chaque porte
    assert(porte->id == 0);
    assert(strcmp(porte1->nom, "P1") == 0);

    // Test d'une porte invalide
    t_porte *porte0 = t_porte_init(2, 10); // Type de porte inexistant
    assert(porte0 == NULL);

    // Vérifier les valeurs initiales (0 ou -1 selon le cas)
    assert(porte->nb_entrees == 2);
    assert(porte2->nb_entrees == 1);
    assert(porte->sortie->valeur == -1);
    assert(porte->entrees[0]->valeur == -1);
    assert(porte->entrees[1]->valeur == -1);

    // Libération de la mémoire allouée à la porte
    free(porte);
    free(porte->sortie);
    free(porte->entrees[0]);
    free(porte->entrees[1]);
}

void test_t_porte_destroy(void)
{
    // Créer une porte (ET)
    t_porte *porte = t_porte_init(0, PORTE_ET);
    t_pin_sortie_set_valeur(porte->sortie, 1);
    t_pin_entree_set_valeur(porte->entrees[0], 1);
    t_pin_entree_set_valeur(porte->entrees[1], 1);

    // S'assurer que la porte a été crée
    if (porte == NULL)
    {
        printf("La mémoire n'a pas été alloué correctement");
        exit(EXIT_FAILURE);
    }

    t_porte_destroy(porte);
    t_porte_destroy(porte->nom);
    t_pin_sortie_destroy(porte->sortie);
    t_pin_entree_destroy(porte->entrees[0]);
    t_pin_entree_destroy(porte->entrees[1]);

    if (porte->entrees[0] != NULL||porte->entrees[1] != NULL||porte->sortie != NULL||porte != NULL||porte->nom != NULL)
    {
        printf("La mémoire n'a pas été libéré correctement");
    }
}

void test_t_porte_calculer_sorties(void)
{
    // Test PORTE_ET
    t_porte *porte_et = t_porte_init(0, PORTE_ET);
    assert(porte_et != NULL);

    t_pin_entree_set_valeur(porte_et->entrees[0], 1);
    t_pin_entree_set_valeur(porte_et->entrees[1], 1);
    t_porte_calculer_sorties(porte_et);
    assert(t_pin_sortie_get_valeur(porte_et->sortie) == 1);

    t_pin_entree_set_valeur(porte_et->entrees[0], 0);
    t_pin_entree_set_valeur(porte_et->entrees[1], 1);
    t_porte_calculer_sorties(porte_et);
    assert(t_pin_sortie_get_valeur(porte_et->sortie) == 0);

    t_pin_entree_set_valeur(porte_et->entrees[0], 1);
    t_pin_entree_set_valeur(porte_et->entrees[1], 0);
    t_porte_calculer_sorties(porte_et);
    assert(t_pin_sortie_get_valeur(porte_et->sortie) == 0);

    t_pin_entree_set_valeur(porte_et->entrees[0], 0);
    t_pin_entree_set_valeur(porte_et->entrees[1], 0);
    t_porte_calculer_sorties(porte_et);
    assert(t_pin_sortie_get_valeur(porte_et->sortie) == 0);

    // Test PORTE_OU
    t_porte *porte_ou = t_porte_init(1, PORTE_OU);
    assert(porte_ou != NULL);

    t_pin_entree_set_valeur(porte_ou->entrees[0], 0);
    t_pin_entree_set_valeur(porte_ou->entrees[1], 0);
    t_porte_calculer_sorties(porte_ou);
    assert(t_pin_sortie_get_valeur(porte_ou->sortie) == 0);

    t_pin_entree_set_valeur(porte_ou->entrees[0], 1);
    t_pin_entree_set_valeur(porte_ou->entrees[1], 0);
    t_porte_calculer_sorties(porte_ou);
    assert(t_pin_sortie_get_valeur(porte_ou->sortie) == 1);

    t_pin_entree_set_valeur(porte_ou->entrees[0], 0);
    t_pin_entree_set_valeur(porte_ou->entrees[1], 1);
    t_porte_calculer_sorties(porte_ou);
    assert(t_pin_sortie_get_valeur(porte_ou->sortie) == 1);

    t_pin_entree_set_valeur(porte_ou->entrees[0], 1);
    t_pin_entree_set_valeur(porte_ou->entrees[1], 1);
    t_porte_calculer_sorties(porte_ou);
    assert(t_pin_sortie_get_valeur(porte_ou->sortie) == 1);

    // Test with PORTE_NOT
    t_porte *porte_not = t_porte_init(2, PORTE_NOT);
    assert(porte_not != NULL);

    t_pin_entree_set_valeur(porte_not->entrees[0], 0);
    t_porte_calculer_sorties(porte_not);
    assert(t_pin_sortie_get_valeur(porte_not->sortie) == 1);

    t_pin_entree_set_valeur(porte_not->entrees[0], 1);
    t_porte_calculer_sorties(porte_not);
    assert(t_pin_sortie_get_valeur(porte_not->sortie) == 0);

    // Test with PORTE_XOR
    t_porte *porte_xor = t_porte_init(3, PORTE_XOR);
    assert(porte_xor != NULL);

    t_pin_entree_set_valeur(porte_xor->entrees[0], 1);
    t_pin_entree_set_valeur(porte_xor->entrees[1], 0);
    t_porte_calculer_sorties(porte_xor);
    assert(t_pin_sortie_get_valeur(porte_xor->sortie) == 1);

    t_pin_entree_set_valeur(porte_xor->entrees[0], 0);
    t_pin_entree_set_valeur(porte_xor->entrees[1], 1);
    t_porte_calculer_sorties(porte_xor);
    assert(t_pin_sortie_get_valeur(porte_xor->sortie) == 1);

    t_pin_entree_set_valeur(porte_xor->entrees[0], 1);
    t_pin_entree_set_valeur(porte_xor->entrees[1], 1);
    t_porte_calculer_sorties(porte_xor);
    assert(t_pin_sortie_get_valeur(porte_xor->sortie) == 0);

    t_pin_entree_set_valeur(porte_xor->entrees[0], 0);
    t_pin_entree_set_valeur(porte_xor->entrees[1], 0);
    t_porte_calculer_sorties(porte_xor);
    assert(t_pin_sortie_get_valeur(porte_xor->sortie) == 0);
}

void test_t_porte_relier(void)
{
    // Test PORTE_ET
    t_porte *porte_et = t_porte_init(1, PORTE_ET); // Créer nouvelle porte
    t_porte *porte_et_source = t_porte_init(2, PORTE_ET); // Source de connexion
    t_pin_sortie_set_valeur(porte_et_source->sortie, 0); // Valeur de sortie
    assert(t_porte_relier(porte_et, 0, porte_et_source->sortie) == 1); // Relie la porte avec la source
    assert(t_pin_entree_est_reliee(porte_et->entrees[0]) == 1); // Vérifier si reliée

    // Test PORTE_NOT
    t_porte *porte_not = t_porte_init(3, PORTE_NOT);
    t_porte *porte_not_source = t_porte_init(4, PORTE_NOT);
    t_pin_sortie_set_valeur(porte_not_source->sortie, 0);
    assert(t_porte_relier(porte_not, 0, porte_not_source->sortie) == 1);
    assert(t_pin_entree_est_reliee(porte_not->entrees[0]) == 1);

    // Test PORTE_OU
    t_porte *porte_ou = t_porte_init(5, PORTE_OU);
    t_porte *porte_ou_source = t_porte_init(6, PORTE_OU);
    t_pin_sortie_set_valeur(porte_ou_source->sortie, 0);
    assert(t_porte_relier(porte_ou, 0, porte_ou_source->sortie) == 1);
    assert(t_pin_entree_est_reliee(porte_ou->entrees[0]) == 1);

    // Test PORTE_XOR
    t_porte *porte_xor = t_porte_init(7, PORTE_XOR);
    t_porte *porte_xor_source = t_porte_init(8, PORTE_XOR);
    t_pin_sortie_set_valeur(porte_xor_source->sortie, 0);
    assert(t_porte_relier(porte_xor, 0, porte_xor_source->sortie) == 1);
    assert(t_pin_entree_est_reliee(porte_xor->entrees[0]) == 1);
}

void test_t_porte_est_reliee(void)
{
    // Test PORTE_ET
    t_porte *porte_et = t_porte_init(1, PORTE_ET);
    t_pin_sortie *source_et = t_pin_sortie_init();
    t_pin_entree* pin_entree = t_pin_entree_init();

    // assert(t_pin_sortie_est_reliee(porte_et->sortie) == 1);
    assert(t_porte_relier(porte_et, 0, source_et) == 1);
    assert(t_porte_est_reliee(porte_et) == 0);

    t_porte_relier(porte_et,1,pin_entree);
    t_pin_sortie_ajouter_lien(porte_et->sortie, pin_entree);
    assert(t_porte_est_reliee(porte_et) == 1);

    // Test PORTE_NOT
    t_porte *porte_not = t_porte_init(2, PORTE_NOT);
    t_pin_sortie *source_not = t_pin_sortie_init();
    t_pin_entree* pin_entree2 = t_pin_entree_init();

    t_pin_sortie_ajouter_lien(porte_not->sortie, pin_entree2);

    assert(t_porte_relier(porte_not, 0, source_not) == 1);
    assert(t_porte_est_reliee(porte_not) == 1);

    /*
    // Test PORTE_OU
    t_porte *porte_ou = t_porte_init(3, PORTE_OU);
    t_pin_sortie *source_ou = t_pin_sortie_init();

    assert(t_porte_relier(porte_ou, 0, source_ou) == 1);
    assert(t_porte_est_reliee(porte_ou) == 1);

    // Test PORTE_XOR
    t_porte *porte_xor = t_porte_init(4, PORTE_XOR);
    t_pin_sortie *source_xor = t_pin_sortie_init();

    assert(t_porte_relier(porte_xor, 0, source_xor) == 1);
    assert(t_porte_est_reliee(porte_xor) == 1); */

    // Libérer mémoire
    t_porte_destroy(porte_et);
    t_porte_destroy(porte_not);
    //t_porte_destroy(porte_ou);
    //  t_porte_destroy(porte_xor);
}

void test_t_porte_reset(void)
{
    // PORTE_ET
    t_porte *porte = t_porte_init(1, PORTE_ET);

    // Création des entrées
    porte->entrees[0] = t_pin_entree_init();
    porte->entrees[1] = t_pin_entree_init();

    // Création des sorties
    porte->sortie = t_pin_sortie_init();

    // Assignation des valeurs pin
    porte->entrees[0]->valeur = 1;
    porte->entrees[1]->valeur = 1;
    porte->sortie->valeur = 1;

    // Réinitialisation de la porte
    t_porte_reset(porte);

    // Vérifier la réinitialisation
    assert(t_pin_sortie_get_valeur(porte->sortie) == -1);
    assert(t_pin_entree_get_valeur(porte->entrees[0]) == -1);
    assert(t_pin_entree_get_valeur(porte->entrees[1]) == -1);

    free(porte);

    // PORTE_OU
    t_porte *porte_ou = t_porte_init(2, PORTE_OU);

    // Création des entrées
    porte_ou->entrees[0] = t_pin_entree_init();
    porte_ou->entrees[1] = t_pin_entree_init();

    // Création des sorties
    porte_ou->sortie = t_pin_sortie_init();

    // Assignation des valeurs pin
    porte_ou->entrees[0]->valeur = 1;
    porte_ou->entrees[1]->valeur = 1;
    porte_ou->sortie->valeur = 1;

    // Réinitialisation de la porte
    t_porte_reset(porte_ou);

    // Vérifier la réinitialisation
    assert(t_pin_sortie_get_valeur(porte_ou->sortie) == -1);
    assert(t_pin_entree_get_valeur(porte_ou->entrees[0]) == -1);
    assert(t_pin_entree_get_valeur(porte_ou->entrees[1]) == -1);

    free(porte_ou);

    // PORTE_NOT
    t_porte *porte_not = t_porte_init(3, PORTE_NOT);

    // Création des entrées
    porte_not->entrees[0] = t_pin_entree_init();

    // Création des sorties
    porte_not->sortie = t_pin_sortie_init();

    // Assignation des valeurs pin
    porte_not->entrees[0]->valeur = 1;
    porte_not->sortie->valeur = 1;

    // Réinitialisation de la porte
    t_porte_reset(porte_not);

    // Vérifier la réinitialisation
    assert(t_pin_sortie_get_valeur(porte_not->sortie) == -1);
    assert(t_pin_entree_get_valeur(porte_not->entrees[0]) == -1);

    free(porte_not);

    // PORTE_XOR
    t_porte *porte_xor = t_porte_init(4, PORTE_XOR);

    // Création des entrées
    porte_xor->entrees[0] = t_pin_entree_init();
    porte_xor->entrees[1] = t_pin_entree_init();

    // Création des sorties
    porte_xor->sortie = t_pin_sortie_init();

    // Assignation des valeurs pin
    porte_xor->entrees[0]->valeur = 1;
    porte_xor->entrees[1]->valeur = 1;
    porte_xor->sortie->valeur = 1;

    // Réinitialisation de la porte
    t_porte_reset(porte_xor);

    // Vérifier la réinitialisation
    assert(t_pin_sortie_get_valeur(porte_xor->sortie) == -1);
    assert(t_pin_entree_get_valeur(porte_xor->entrees[0]) == -1);
    assert(t_pin_entree_get_valeur(porte_xor->entrees[1]) == -1);

    free(porte_xor);
}

void test_t_porte_propager_signal(void)
{
    // PORTE_ET
    t_porte *porte_et = t_porte_init(1, PORTE_ET);

    // Création des entrées
    porte_et->entrees[0] = t_pin_entree_init();
    porte_et->entrees[1] = t_pin_entree_init();

    // Création de la sortie
    porte_et->sortie = t_pin_sortie_init();

    // Relier la sortie à l'entrée
    t_pin_entree_relier(porte_et->entrees[0], porte_et->sortie);

    // Assignation des valeurs pin
    porte_et->entrees[0]->valeur = 1;
    porte_et->entrees[1]->valeur = 1;

    // Propager le signal et vérifier
    assert(t_porte_propager_signal(porte_et) == 1); // Le signal devrait se propager

    free(porte_et);

    // PORTE_NOT
    t_porte *porte_not = t_porte_init(3, PORTE_NOT);

    // Création des entrées
    porte_not->entrees[0] = t_pin_entree_init();

    // Création de la sortie
    porte_not->sortie = t_pin_sortie_init();

    // Relier la sortie à l'entrée
    t_pin_entree_relier(porte_not->entrees[0], porte_not->sortie);

    // Assignation des valeurs pin
    porte_not->entrees[0]->valeur = 0; // Entrée NOT, donc on met la valeur à 0

    // Propager le signal et vérifier
    assert(t_porte_propager_signal(porte_not) == 1); // Le signal devrait se propager

    free(porte_not);

    // PORTE_XOR
    t_porte *porte_xor = t_porte_init(4, PORTE_XOR);

    // Création des entrées
    porte_xor->entrees[0] = t_pin_entree_init();
    porte_xor->entrees[1] = t_pin_entree_init();

    // Création de la sortie
    porte_xor->sortie = t_pin_sortie_init();

    // Relier la sortie à l'entrée
    t_pin_entree_relier(porte_xor->entrees[0], porte_xor->sortie);
    t_pin_entree_relier(porte_xor->entrees[1], porte_xor->sortie);

    // Assignation des valeurs pin
    porte_xor->entrees[0]->valeur = 1;
    porte_xor->entrees[1]->valeur = 0;

    // Propager le signal et vérifier
    assert(t_porte_propager_signal(porte_xor) == 1); // Le signal devrait se propager

    free(porte_xor);

    // PORTE_OU
    t_porte *porte_ou = t_porte_init(2, PORTE_OU);

    // Création des entrées
    porte_ou->entrees[0] = t_pin_entree_init();
    porte_ou->entrees[1] = t_pin_entree_init();

    // Création de la sortie
    porte_ou->sortie = t_pin_sortie_init();

    // Relier la sortie à l'entrée
    t_pin_entree_relier(porte_ou->entrees[0], porte_ou->sortie);
    t_pin_entree_relier(porte_ou->entrees[1], porte_ou->sortie);

    // Assignation des valeurs pin
    porte_ou->entrees[0]->valeur = 0;
    porte_ou->entrees[1]->valeur = 1;

    // Propager le signal et vérifier
    assert(t_porte_propager_signal(porte_ou) == 1); // Le signal devrait se propager

    free(porte_ou);
}

void test_t_porte_get_pin_sortie(void)
{
    for (e_types_portes type = PORTE_ET; type <= PORTE_XOR; ++type)
    {
        // Initialisation de la porte
        t_porte *porte = t_porte_init(2, type);

        // Création des entrées
        porte->entrees[0] = t_pin_entree_init();
        porte->entrees[1] = t_pin_entree_init();

        // Création de la sortie
        porte->sortie = t_pin_sortie_init();

        // Obtenir la sortie avec la fonction à tester
        t_pin_sortie *sortie = t_porte_get_pin_sortie(porte);

        // Vérifier que la sortie obtenue est la même que celle de la porte
        assert(sortie == porte->sortie);

        free(porte);
    }
}