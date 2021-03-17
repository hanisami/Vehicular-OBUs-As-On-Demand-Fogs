/*
 * initialization.c: Vehicular Container Placement Problem - Initialization Header
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
int** initialization(int number_of_individuals, int h_size, int v_size, int **V, int max_SLA);
int generate_solution_position(int max_posible, int SLA);
