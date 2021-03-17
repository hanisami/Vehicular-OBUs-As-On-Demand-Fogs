/*
 * local_search.h: Vehicular Container Placement Problem - Local Search Header
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
int** local_search(int **population, int ***utilization, int **H, int **V, int number_of_individuals, int h_size, int v_size);
