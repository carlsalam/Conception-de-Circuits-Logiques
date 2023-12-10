#ifndef TP2_GR02_EQUIPEC_FONCTIONS_TEST_CIRCUIT_H
#define TP2_GR02_EQUIPEC_FONCTIONS_TEST_CIRCUIT_H

#include "t_circuit.h"
#include "t_entree.h"
#include "t_file_porte.h"
#include "t_pin_entree.h"
#include "t_pin_sortie.h"
#include "t_porte.h"
#include "t_sortie.h"
#include <assert.h>


void test_t_circuit_init(void);

void test_t_circuit_ajouter_porte(void);

void test_t_circuit_ajouter_entree(void);

void test_t_circuit_ajouter_sortie(void);

void test_t_circuit_est_valide(void);

void test_t_circuit_appliquer_signal(void);

void test_t_circuit_reset(void);

void test_circuit_propager_signal(void);






#endif //TP2_GR02_EQUIPEC_FONCTIONS_TEST_CIRCUIT_H



