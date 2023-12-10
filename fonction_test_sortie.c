
#include "fonction_test_sortie.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void test_t_sortie_init(void)
{
    t_sortie* sortie = t_sortie_init(1);

    assert(sortie!=NULL);
    assert(sortie->id == 1);
    assert(strcmp(sortie->nom, "S1") == 0);
    assert(sortie->pin!=NULL);

    t_pin_entree_destroy(sortie->pin);
    free(sortie);
}



void test_t_sortie_get_pin(void)
{
    t_sortie* sortie = t_sortie_init(1);
    t_pin_entree* pin_entree = t_sortie_get_pin(sortie);

    assert(pin_entree == sortie->pin);

    t_pin_entree_destroy(sortie->pin);
    free(sortie);
}

void test_t_sortie_relier(void)
{
    t_sortie* sortie = t_sortie_init(2);
    t_pin_sortie* pin_sortie = t_pin_sortie_init();

    assert(t_sortie_relier(sortie, pin_sortie));

    t_pin_entree_destroy(sortie->pin);
    t_pin_sortie_destroy(pin_sortie);
    free(sortie);
}

void test_t_sortie_est_reliee(void)
{
    t_sortie* sortie = t_sortie_init(1);
    t_pin_sortie* pin_sortie = t_pin_sortie_init();

    assert(!t_sortie_est_reliee(sortie));

    t_sortie_relier(sortie, pin_sortie);

    assert(t_sortie_est_reliee(sortie));

    t_pin_entree_destroy(sortie->pin);
    t_pin_sortie_destroy(pin_sortie);
    free(sortie);
}

void test_t_sortie_reset(void)
{
    t_sortie* sortie = t_sortie_init(1);

    sortie->pin->valeur = 2;
    t_sortie_reset(sortie);

    assert(t_pin_entree_get_valeur(sortie->pin) == -1);

    t_pin_entree_destroy(sortie->pin);
    free(sortie);
}

void test_t_sortie_get_valeur(void)
{
    t_sortie* sortie = t_sortie_init(1);

    assert(t_sortie_get_valeur(sortie) == -1);

    sortie->pin->valeur = 2;

    assert(t_sortie_get_valeur(sortie) == 2);

    t_pin_entree_destroy(sortie->pin);
    free(sortie);
}

void test_t_sortie(void)
{
    test_t_sortie_init();
    test_t_sortie_est_reliee();
    test_t_sortie_get_pin();
    test_t_sortie_get_valeur();
    test_t_sortie_relier();
    test_t_sortie_reset();
}






