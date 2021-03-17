/*
 * reparation.h: Vehicular Container Placement Problem - Reparation Header
 * Date: 01-12-2019
 * Author: Hani Sami (hos03@mail.aub.edu)
 * IEEE TNET 2020
 */

/* include libraries */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* function headers definitions */
int** reparation(int ** population, int *** utilization, int ** H, int ** V, int number_of_individuals, int h_size, int v_size, int max_SLA);
void repair_population(int ** population, int *** utilization, int ** H, int ** V, int number_of_individuals, int h_size, int v_size, int max_SLA);
void repair_individual(int ** population, int *** utilization, int ** H, int ** V, int number_of_individuals, int h_size, int v_size, int max_SLA, int individual);
int is_overloaded(int **H, int ***utilization, int individual, int physical);
int is_overassigned(int *K, int **network_utilization, int individual, int link);
