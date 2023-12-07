//
// Created by user on 2023-12-07.
//

#include "fonction_test_sortie.h"


void test_t_porte_init(void)
{
    t_porte* porte0 = t_porte_init(0, PORTE_ET);
    t_porte* porte1 = t_porte_init(1, PORTE_OU);
    t_porte* porte2 = t_porte_init(2, PORTE_NOT);
    t_porte* porte3 = t_porte_init(3, PORTE_XOR);

    assert(porte0 != NULL);
    assert(porte1 != NULL);
    assert(porte2 != NULL);
    assert(porte3 != NULL);

    assert(porte0 -> id == 0);
    assert(strcmp(porte1 -> nom, "P1")== 0);

    t_porte *porteinvalid = t_porte_init(2,10);
    assert(porteinvalid == NULL);


    assert(porte0 ->nb_entrees == 2);
    assert(porte2 ->nb_entrees == 1);
    assert(porte0->sortie->valeur == -1);
    assert(porte0 ->entrees[0] ->valeur == -1);

    //On libere la memoire totale

    free(porte0);
    free(porte0 ->sortie);
    free(porte0 ->entrees[0]);
    free(porte0 ->entrees[1]);
}
void test_t_porte_destroy(void);
{
    //not yet
}

void test_t_porte_calculer_sorties(void)
    {

    t_porte *porte_test = t_porte_init(0, PORTE_ET);

    assert(porte_test != NULL);
    //premier bloc
    t_pin_entree_set_valeur(porte_test->entrees[0], 1);
    t_pin_entree_set_valeur(porte_test->entrees[1], 1);
    t_porte_calculer_sorties(porte_test);
    assert(t_pin_sortie_get_valeur(porte_test->sortie) == 1);

//deuxieme bloc
    t_pin_entree_set_valeur(porte_test->entrees[0], 0);
    t_pin_entree_set_valeur(porte_test->entrees[1], 1);
    t_porte_calculer_sorties(porte_test);
    assert(t_pin_sortie_get_valeur(porte_test->sortie) == 0);

//troisieme bloc
    t_pin_entree_set_valeur(porte_test->entrees[0], 1);
    t_pin_entree_set_valeur(porte_test->entrees[1], 0);
    t_porte_calculer_sorties(porte_test);
    assert(t_pin_sortie_get_valeur(porte_test->sortie) == 0);

    //4eme bloc

    t_pin_entree_set_valeur(porte_test->entrees[0], 0);
    t_pin_entree_set_valeur(porte_test->entrees[1], 0);
    t_porte_calculer_sorties(porte_test);
    assert(t_pin_sortie_get_valeur(porte_test->sortie) == 0);
    //Ceci complete la 1ere porte(porte ET)


    //Voici les essaie pour porte ou
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


    //On passe a la porte NOT

    t_porte *porte_not = t_porte_init(2, PORTE_NOT);
    assert(porte_not != NULL);


    t_pin_entree_set_valeur(porte_not->entrees[0], 0);
    t_porte_calculer_sorties(porte_not);
    assert(t_pin_sortie_get_valeur(porte_not->sortie) == 1);

    t_pin_entree_set_valeur(porte_not->entrees[0], 1);
    t_porte_calculer_sorties(porte_not);
    assert(t_pin_sortie_get_valeur(porte_not->sortie) == 0);

    //DERNIERE PORTE XOR

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
       t_porte *porte_et = t_porte_init(1, PORTE_ET);
       t_porte *porte_et_source = t_porte_init(2, PORTE_ET);
       t_pin_sortie_set_valeur(porte_et_source->sortie, 0);
       assert(t_porte_relier(porte_et, 0 , porte_et_source ->sortie)== 1);
       assert(t_pin_entree_est_reliee(porte_et -> entrees[0]) == 1);


       t_porte *porte_not = t_porte_init(3, PORTE_NOT);
       t_porte *porte_not_source = t_porte_init(4, PORTE_NOT);
       t_pin_sortie_set_valeur(porte_not_source->sortie, 0);
       assert(t_porte_relier(porte_not, 0 , porte_not_source ->sortie)== 1);
       assert(t_pin_entree_est_reliee(porte_not -> entrees[0]) == 1);

       t_porte *porte_ou = t_porte_init(5, PORTE_OU);
       t_porte *porte_ou_source = t_porte_init(6, PORTE_OU);
       t_pin_sortie_set_valeur(porte_ou_source->sortie, 0);
       assert(t_porte_relier(porte_ou, 0 , porte_ou_source ->sortie)== 1);
       assert(t_pin_entree_est_reliee(porte_ou -> entrees[0]) == 1);

       t_porte *porte_xor = t_porte_init(7, PORTE_XOR);
       t_porte *porte_xor_source = t_porte_init(8, PORTE_XOR);
       t_pin_sortie_set_valeur(porte_xor_source->sortie, 0);
       assert(t_porte_relier(porte_xor, 0 , porte_xor_source ->sortie)== 1);
       assert(t_pin_entree_est_reliee(porte_xor -> entrees[0]) == 1);





   }