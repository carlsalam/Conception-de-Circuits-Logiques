//
// Created by csala on 2023-11-17.
//

#ifndef TP2_GR02_EQUIPEC_FONCTIONS_TEST_ENTREE_H
#define TP2_GR02_EQUIPEC_FONCTIONS_TEST_ENTREE_H


#include "t_circuit.h"
#include "t_entree.h"
#include "t_file_porte.h"
#include "t_pin_entree.h"
#include "t_pin_sortie.h"
#include "t_porte.h"
#include "t_sortie.h"
#include <assert.h>

//module t_entree

//Fonction test pour t_entree

void test_t_entree_init(void);

void test_t_entree_destroy(void);

void test_t_entree_get_pin(void);

void test_t_entree_reliee(void);

void test_t_entree_reset(void);

void test_t_entree_get_valeur(void);

void test_t_entree_propager_signal(void);

#endif //TP2_GR02_EQUIPEC_FONCTIONS_TEST_ENTREE_H
