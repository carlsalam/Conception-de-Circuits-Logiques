#ifndef TP2_GR02_EQUIPEC_FONCTIONS_TEST_PORTE_H
#define TP2_GR02_EQUIPEC_FONCTIONS_TEST_PORTE_H

#include "t_circuit.h"
#include "t_entree.h"
#include "t_file_porte.h"
#include "t_pin_entree.h"
#include "t_pin_sortie.h"
#include "t_porte.h"
#include "t_sortie.h"
#include <assert.h>

void test_t_porte_init(void);

void test_t_porte_destroy(void);

void test_t_porte_calculer_sorties(void);

void test_t_porte_relier(void);

void test_t_porte_est_reliee(void);

void test_t_porte_reset(void);

void test_t_porte_propager_signal(void);

void test_t_porte_get_pin_sortie(void);





#endif //TP2_GR02_EQUIPEC_FONCTIONS_TEST_PORTE_H
