//
// Created by csala on 2023-11-17.
//

#include "fonctions_test_entree.h"


void test_t_entree_init(void)
{
    t_entree *entree = t_entree_init(1);

    assert(entree != NULL); //le programme s'arrete dans le cas echeant
    assert(entree ->id ==1);
    assert(strcmp(entree->nom, "E1") ==0);
    assert(t_pin_sortie_est_reliee(entree->pin) == 0);

    free(entree -> pin); //destruction de memoire
}

void test_t_entree_destroy(void)
{
    t_entree *entree = t_entree_init(1);
    assert(entree != NULL);

    t_entree_destroy(entree); //on libere la memoire

    assert(entree ->pin == NULL);

}

void test_t_entree_get_pin(void)
{
    t_entree *entree = t_entree_init(1);
    assert(entree != NULL);

    t_pin_sortie *pin = t_entree_get_pin(entree);
    assert(pin == entree -> pin);

    free(entree -> pin); //on libere la memoire
}

void test_t_entree_reliee(void) //Nous voulons savoir si notre fonction retourne 0(grace a assert)
{
    t_entree *entree = t_entree_init(1);
    assert(entree != NULL);

    assert(t_entree_est_reliee(entree) == 0);

    free(entree -> pin);//on libere la memoire

}

void test_t_entree_reset(void)
{
    t_entree *entree = t_entree_init(1);
    assert(entree != NULL);

    t_pin_sortie_propager_signal(entree -> pin);

    t_entree_reset(entree);

    assert(t_entree_get_valeur(entree)==0);

    free(entree ->pin);

}

void test_t_entree_propager_signal(void)
{

    t_entree *entree_test = t_entree_init(1);
    t_sortie* sortietemp1 = t_sortie_init(1);
    t_sortie* sortietemp2 = t_sortie_init(2);

    assert(entree_test != NULL);
    t_pin_sortie_set_valeur (entree_test ->pin, 1);
    t_entree_propager_signal(entree_test);

    assert(t_sortie_get_valeur(sortietemp1) == 1);

    assert(t_sortie_get_valeur(sortietemp2) == 2);
}

void test_t_entree_get_valeur(void)
{
    t_entree *entree_test = t_entree_init(1);

    assert(entree_test != NULL);
    assert(t_entree_get_valeur(entree_test) == -1);

    t_pin_sortie_set_valeur(entree_test->pin, 1);

    assert(t_entree_get_valeur(entree_test)==1);
    free(entree_test);
}