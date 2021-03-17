/*
 * variation.h: Vehicular Container Placement Problem - Genetic Operators Header
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
int *non_dominated_sorting(float ** solutions, int number_of_individuals);
int is_dominated(float ** solutions, int a, int b);
int selection(int *fronts, int number_of_individuals, float percent);
int** crossover(int **population, int position_parent1, int position_parent2, int v_size);
int ** mutation(int **population, int **V, int number_of_individuals, int h_size, int v_size);
int ** population_evolution(int **P, int **Q, float **objectives_functions_P, float **objectives_functions_Q, int *fronts_P, int number_of_individuals, int v_size);
long double pareto_size();
void update_pareto_set(int **P, float **objectives_functions_P, int *fronts_P, int number_of_individuals, int v_size);
