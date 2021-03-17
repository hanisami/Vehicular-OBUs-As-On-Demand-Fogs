/*
 * cpp.c: Interactive Memetic Algorithm for Vehicular Container Placement Problem (VCP)
 * Date: 01-12-2019
 * Author: Hani Sami (hos03@mail.aub.edu)
 * IEEE TNET 2020
 */

/* structure of a pareto element */
struct pareto_element{
	int *solution;
	float *costs;
	struct pareto_element *prev;
	struct pareto_element *next;
};

/* include libraries */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* include own headers */
#include "common.h"
#include "initialization.h"
#include "reparation.h"
#include "local_search.h"
#include "variation.h"
#include "pareto.h"
/* definitions (this could be parameters) */
#define NUMBER_OF_INDIVIDUALS 100
#define NUMBER_OF_GENERATIONS 1000
#define SELECTION_PERCENT 0.5
#define MAX_SLA 1
#define SERVICES_COUNT 2
#define MAX_SURV 2000 // maximum survivability in the input file
#define MAX_CONNECTION 20 // maximum possible connection time between microservices

/* main: Interactive Memetic Algorithm for container Placement (CPP)
 * parameter: path to the datacenter infrastructure file
 * returns: exit state
 */
int main (void) {
	char str[] = "4x6.vcp";
    /* parameters verification */
    /* good parameters */
		/* Interactive Memetic Algorithm previous stuff */
		/* number of generation, for iterative reference of generations */
		int generation = 0;
		int h_size = get_h_size(str);
		int v_size = get_v_size(str);

		printf("\nH=%d, V=%d\n",h_size,v_size);
		int **H = load_H(h_size, str);
		// printf("\nH LOADED SUCCESSFULLY\n");
		int **V = load_V(v_size, str);
		// printf("\nV LOADED SUCCESSFULLY\n");

		/* seed for rand() */
		srand((unsigned int) time(NULL));
		/* randon value of 0-1 */
		srand48(time(NULL));
		// printf("\nDATACENTER LOADED SUCCESSFULLY\n");

		/* Interactive Memetic Algorithm starts here */
		/* If the problem instance have at least one solution, we can continue */
		/* 02: Initialize population P_0 */
		int **P = initialization(NUMBER_OF_INDIVIDUALS, h_size, v_size, V, MAX_SLA);
		// printf("\nP_0 CREATED SUCCESSFULLY\n");
		/* Additional task: load the utilization of vehicles links of all individuals/solutions */
		int ***utilization_P = load_utilization(P, H, V, NUMBER_OF_INDIVIDUALS, h_size, v_size);
		/* 03: P0’ = repair infeasible solutions of P_0 */
		P = reparation(P, utilization_P, H, V, NUMBER_OF_INDIVIDUALS, h_size, v_size, MAX_SLA);
		// printf("\nP_0 REPAIRED SUCCESSFULLY\n");
		/* 04: P0’’ = apply local search to solutions of P_0’ */
		P = local_search(P, utilization_P, H, V, NUMBER_OF_INDIVIDUALS, h_size, v_size);
		/* Additional task: calculate the cost of each objective function for each solution */
		float **objectives_functions_P = load_objectives(P, utilization_P, H, V, NUMBER_OF_INDIVIDUALS, h_size, v_size, SERVICES_COUNT, MAX_SURV, MAX_CONNECTION);
		// printf("\nP_0 OBJECTIVE FUNCTIONS VALUES CALCULATED SUCCESSFULLY\n");
		/* Additional task: calculate the non-dominated fronts according to NSGA-II */
		int *fronts_P = non_dominated_sorting(objectives_functions_P,NUMBER_OF_INDIVIDUALS);
		//printf("%d %d %d %d %d\n",objectives_functions_P[0][0],objectives_functions_P[0][1],objectives_functions_P[0][2]
		//,objectives_functions_P[0][3],objectives_functions_P[0][4]);
		// printf("\nP_0 NON-DOMINATED SORTING CALCULATED SUCCESSFULLY\n");
		/* 05: Update set of nondominated solutions Pc from P_0’’ */
		struct pareto_element *pareto_head = NULL;
		int iterator_individual;
		/* considering that the P_c is empty at first population, each non-dominated solution from first front is added */
		for (iterator_individual = 0 ; iterator_individual < NUMBER_OF_INDIVIDUALS ; iterator_individual++)
		{
		 	if(fronts_P[iterator_individual] == 1)
		 	{
		 		pareto_head = (struct pareto_element *) pareto_insert(pareto_head,v_size,P[iterator_individual],objectives_functions_P[iterator_individual]);
		 	}
		}
		getHighestFitnessSolution(pareto_head, H, V, v_size, h_size);
		// printf("\nP_KNOWN CALCULATED SUCCESSFULLY\n");
		/* 06: t = 0 */
		/* 06: Pt = P0’’ */
		/* Additional task: identificators for the crossover parents */
		int father, mother;
		/* Additional task: structures for Q and PQ */
		int **Q;
		int ***utilization_Q;
		float **objectives_functions_Q;
		int *fronts_Q;
		/* 07: While (stopping criterion is not met), do */
		while (generation < NUMBER_OF_GENERATIONS)
		{
			// printf("\nGENERATION %d STARTED SUCCESSFULLY\n",generation);
			/* this is a new generation! */
			generation++;
		 	/* Additional task: Q is a random generated population, lets initialize it */
			Q = initialization(NUMBER_OF_INDIVIDUALS, h_size, v_size, V, MAX_SLA);
			/* 08: Q_t = selection of solutions from P_t ∪ P_c */
			father = selection(fronts_P, NUMBER_OF_INDIVIDUALS, SELECTION_PERCENT);
			mother = selection(fronts_P, NUMBER_OF_INDIVIDUALS, SELECTION_PERCENT);
			// printf("\nSELECTION SUCCESSFULL\n");
			/* 09: Q_t’ = crossover and mutation of solutions of Q_t */
			Q = crossover(Q, father, mother, v_size);
			// printf("\nCROSSOVER SUCCESSFULL\n");
			/* 10: Q_t’ = crossover and mutation of solutions of Q_t */
			// printf("\nMUTATION SUCCESSFULL\n");
			Q = mutation(Q,V,NUMBER_OF_INDIVIDUALS,h_size,v_size);
			/* Additional task: load the utilization of vehicles links of all individuals/solutions */
			utilization_Q = load_utilization(Q, H, V, NUMBER_OF_INDIVIDUALS, h_size, v_size);
			// printf("\nP_%d UTILIZATION CALCULATED SUCCESSFULLY\n",generation);
			/* 10: Q_t’’ = repair infeasible solutions of Q_t’ */
			Q = reparation(Q, utilization_Q, H, V, NUMBER_OF_INDIVIDUALS, h_size, v_size, MAX_SLA);
			// printf("\nP_%d REPAIRED SUCCESSFULLY\n",generation);
			/* 11: Q_t’’’ = apply local search to solutions of Q_t’’ */
			Q = local_search(Q, utilization_Q, H, V, NUMBER_OF_INDIVIDUALS, h_size, v_size);
			/* Additional task: calculate the cost of each objective function for each solution */
			objectives_functions_Q = load_objectives(Q, utilization_Q, H, V, NUMBER_OF_INDIVIDUALS, h_size, v_size, SERVICES_COUNT, MAX_SURV, MAX_CONNECTION);
			// printf("\nP_%d OBJECTIVE FUNCTIONS VALUES CALCULATED SUCCESSFULLY\n",generation);
			/* Additional task: calculate the non-dominated fronts according to NSGA-II */
			fronts_Q = non_dominated_sorting(objectives_functions_Q,NUMBER_OF_INDIVIDUALS);
			// printf("\nP_%d NON-DOMINATED SORTING CALCULATED SUCCESSFULLY\n",generation);
			/* 12: Update set of nondominated solutions Pc from Qt’’’ */
			for (iterator_individual = 0 ; iterator_individual < NUMBER_OF_INDIVIDUALS ; iterator_individual++)
		    	{
			 	if(fronts_Q[iterator_individual] == 1)
			 	{
			 		pareto_head = (struct pareto_element *) pareto_insert(pareto_head,v_size,Q[iterator_individual],objectives_functions_Q[iterator_individual]);
			 	}
			}
			// printf("\nP_KNOWN CALCULATED SUCCESSFULLY\n");
			/* 17: Pt = fitness selection from Pt ∪ Qt’’’ */
			P = population_evolution(P, Q, objectives_functions_P, objectives_functions_Q, fronts_P, NUMBER_OF_INDIVIDUALS, v_size);
			getHighestFitnessSolution(pareto_head, H, V, v_size, h_size);
			//printf("%s %d\n","saff",generation);
			// printf("\nP_%d EVOLVED TO P_%d\n",generation-1,generation);
		}

		report_best_population(pareto_head, H, V, v_size, h_size);
		getHighestFitnessSolution(pareto_head, H, V, v_size, h_size);
		printf("\n");
		return 0;

}

/* check_instance: checks if the problem instance has at least one solution
 * returns: 1 if there is no solution, 0 if the is at least one solution
 */
