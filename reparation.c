/*
 * reparation.c: Vehicular Container Placement Problem - Reparation Stage
 * Date: 01-12-2019
 * Author: Hani Sami (hos03@mail.aub.edu)
 * IEEE TNET 2020
 */

/* include reparation stage header */
#include "reparation.h"

/* reparation: reparates the population
 * parameter: population matrix
 * parameter: physical machines matrix
 * parameter: containers matrix
 * parameter: number of individuals
 * parameter: number of physical machines
 * parameter: number of containers
 * returns: reparated population matrix
 */
int** reparation(int ** population, int *** utilization, int ** H, int ** V, int number_of_individuals, int h_size, int v_size, int max_SLA)
{
	/* repairs population from not factible individuals */
	repair_population(population, utilization, H, V, number_of_individuals, h_size, v_size, max_SLA);
	return population;
}

/* repair_population: repairs population from not factible individuals
 * parameter: population matrix
 * parameter: utilization of the physical machines matrix
 * parameter: physical machines matrix
 * parameter: containers matrix
 * parameter: number of individuals
 * parameter: number of physical machines
 * parameter: number of containers
 * returns: nothing, it's void()
 */
void repair_population(int ** population, int *** utilization, int ** H, int ** V, int number_of_individuals, int h_size, int v_size, int max_SLA)
{
	/* iterators */
	int iterator_individual = 0;
	int iterator_virtual = 0;
	int iterator_physical = 0;
	int iterator_link = 0;
	int factibility = 1;
	/* iterate on individuals */
	for (iterator_individual = 0; iterator_individual < number_of_individuals ; iterator_individual++)
	{
		/* every individual is feasible until it's probed other thing */
		factibility = 1;
		/* constraint 2: Service Level Agreement (SLA) provision. Containers with SLA = max_SLA have to be placed mandatorily */
		for (iterator_virtual = 0; iterator_virtual < v_size; iterator_virtual++)
		{
			if (V[iterator_virtual][3] == max_SLA && population[iterator_individual][iterator_virtual] == 0)
			{
				factibility = 0;
				break;
			}
		}
		/* constraints 3-5: Resource capacity of physical machines. Iterate on physical machines */
		for (iterator_physical = 0; iterator_physical < h_size ; iterator_physical++)
		{
			/* if any physical machine is overloaded on any resource, the individual is not factible */
			if (is_overloaded(H, utilization, iterator_individual, iterator_physical))
			{
				factibility = 0;
				break;
			}
		}

		/* if the individual is not factible */
		if (factibility == 0)
		{
			repair_individual(population, utilization, H, V, number_of_individuals, h_size, v_size, max_SLA, iterator_individual);
		}
	}
}

/* repair_individual: repairs not factible individuals
 * parameter: population matrix
 * parameter: utilization of the physical machines matrix
 * parameter: physical machines matrix
 * parameter: containers matrix
 * parameter: number of individuals
 * parameter: number of physical machines
 * parameter: number of containers
 * parameter: identificator of the not factible individual to repair
 * returns: nothing, it's void()
 */
void repair_individual(int ** population, int *** utilization, int ** H, int ** V, int number_of_individuals, int h_size, int v_size, int max_SLA, int individual)
{
	int iterator_virtual = 0;
	int iterator_virtual_again=0;
	int iterator_physical = 0;
	int iterator_link = 0;
	/* every individual is not feasible until it's probed other thing */
	int factibility = 0;
	/* id of a candidate physical machine for migration */
	int candidate = 0;
	/* a migration flag for overloaded physical machines indicating that a container was or not migrated yet */
	int migration = 0;
	/* iterate on each container to search for overloaded physical machines */
	for (iterator_virtual = 0; iterator_virtual < v_size; iterator_virtual++)
	{
		/* if the container was placed */
		if (population[individual][iterator_virtual] != 0)
		{
			migration = 0;
			/* verify is the physical machine assigned is overloaded in any physical resource */
			if (is_overloaded(H, utilization, individual, (population[individual][iterator_virtual]-1)))
			{
				/* we search for a correct candidate for VM "migration" (it is not really a migration, only a physical machine change) */
				for (iterator_physical=0; iterator_physical < h_size; iterator_physical++)
				{
					/* if the candidate can assume the resource requested */
					if (utilization[individual][iterator_physical][0] + V[iterator_virtual][0] <= H[iterator_physical][0] &&
	   			   	 	utilization[individual][iterator_physical][1] + V[iterator_virtual][1] <= H[iterator_physical][1] &&
									utilization[individual][iterator_physical][2] + V[iterator_virtual][2] <= H[iterator_physical][2])
					{
						/* delete requirements from physical machine migration source */
						utilization[individual][population[individual][iterator_virtual]-1][0] -= V[iterator_virtual][0];
						utilization[individual][population[individual][iterator_virtual]-1][1] -= V[iterator_virtual][1];
						utilization[individual][population[individual][iterator_virtual]-1][2] -= V[iterator_virtual][2];
						/* add requirements from physical machine migration destination */
						utilization[individual][iterator_physical][0] += V[iterator_virtual][0];
						utilization[individual][iterator_physical][1] += V[iterator_virtual][1];
						utilization[individual][iterator_physical][2] += V[iterator_virtual][2];
						/* refresh the population */
						population[individual][iterator_virtual] = iterator_physical + 1;
						/* container correctly "migrated" */
						migration = 1;
						break;
					}
				}
				if (!migration)
				{
					// printf("%d %d %d %d %d %d tt\n", population[individual][0], population[individual][1], population[individual][2], population[individual][3], population[individual][4], population[individual][5]);
					/* delete requirements from physical machine migration source */
					utilization[individual][population[individual][iterator_virtual]-1][0] -= V[iterator_virtual][0];
					utilization[individual][population[individual][iterator_virtual]-1][1] -= V[iterator_virtual][1];
					utilization[individual][population[individual][iterator_virtual]-1][2] -= V[iterator_virtual][2];
					/* refresh the population */
					population[individual][iterator_virtual] = 0;
					/* container correctly "deleted" */
					migration = 1;
					//break;
				}
				// if(!migration)
				// {
				// 	/*remove solution; It is SLA but the solution is not feasible*/
				// 	break;
				// }
			}
		}
	}
}

/* is_overloaded: verificates if a physical machine is overloaded
 * parameter: physical machine resources matrix
 * parameter: utilization of the physical machines matrix
 * parameter: identificator of the individual
 * parameter: identificator of the physical machine
 * returns: 1 if yes, 0 if no
 */
int is_overloaded(int ** H, int *** utilization, int individual, int physical)
{
	/* If the use of the VM exceeds the capacity of the physical machine return 1, otherwise return 0 */
	if ((utilization[individual][physical][0] > H[physical][0])
	||  (utilization[individual][physical][1] > H[physical][1])
  || (utilization[individual][physical][2] > H[physical][2]))
	{
		return 1;
	}
	return 0;
}
