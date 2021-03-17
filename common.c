/*
 * common.c: Vehicular Container Placement Problem - Common Functions
 * Date: 01-12-2019
 * Author: Hani Sami (hos03@mail.aub.edu)
 * IEEE TNET 2020
 */

/* include common header */
#include "common.h"
#include <stdbool.h>

/* get_h_size: returns the number of physical machines
 * parameter: path to the datacenter file
 * returns: number of physical machines
 */
int get_h_size(char path_to_file[])
{
	/* datacenter file to read from */
	FILE *datacenter_file;
	/* line readed from file */
	char input_line[TAM_BUFFER];
	/* number of physical machines */
	int h_size = 0;
	/* 1 if reading the physical machines block in the file */
	int reading_physical = 0;
 	/* open the file for reading */
	datacenter_file = fopen(path_to_file,"r");
    /* if it is opened ok, we continue */
	if (datacenter_file != NULL)
	{
		/* read until the end */
		while(!feof(datacenter_file))
		{
			/* get line per line */
			fgets(input_line, TAM_BUFFER, datacenter_file);
			/* if the line is equal to H_HEADER, we begin the physical machines block in the file */
			if (strstr(input_line,H_HEADER) != NULL)
			{
				reading_physical = 1;
			}
			/* if the line is equal to V_HEADER, we end the physical machines block in the file */
			if (strstr(input_line,V_HEADER) != NULL)
			{
				reading_physical = 0;
				break;
			}
			/* if it is the correct block in the file, it is not the header and it is not a blank line, we count */
			if (reading_physical == 1 && strstr(input_line,H_HEADER) == NULL && strcmp(input_line, "\n") != 0)
			{
				h_size++;
			}
		}
	}
	/* close the file */
	fclose(datacenter_file);
	/* return the value */
	return h_size;
}

/* get_v_size: returns the number of containers
 * parameter: path to the datacenter file
 * returns: number of containers
 */
int get_v_size(char path_to_file[])
{
	/* datacenter file to read from */
	FILE *datacenter_file;
	/* line readed from file */
	char input_line[TAM_BUFFER];
	/* number of containers */
	int v_size = 0;
	/* 1 if reading the containers block in the file */
	int reading_virtual = 0;
 	/* open the file for reading */
	datacenter_file = fopen(path_to_file,"r");
    /* if it is opened ok, we continue */
	if (datacenter_file != NULL)
	{
		/* read until the end */
		while(!feof(datacenter_file))
		{
			/* get line per line */
			fgets(input_line, TAM_BUFFER, datacenter_file);
			/* if the line is equal to V_HEADER, we begin the containers block in the file */
			if (strstr(input_line,V_HEADER) != NULL)
			{
				reading_virtual = 1;
			}
			/* if the line is equal to T_HEADER, we end the containers block in the file */
			if (strstr(input_line,T_HEADER) != NULL)
			{
				reading_virtual = 0;
				break;
			}
			/* if we are in the correct block in the file, it is not the header and it is not a blank line, we count */
			if (reading_virtual == 1 && strstr(input_line,V_HEADER) == NULL && strcmp(input_line, "\n") != 0)
			{
				v_size++;
			}
		}
	}
	/* close the file */
	fclose(datacenter_file);
	/* return the value */
	return v_size;
}

/* print_int_matrix: prints on screen a integer matrix
 * parameter: matrix to print
 * parameter: number of individuals
 * parameter: number of containers
 * returns: nothing, it's void
 */
void print_int_matrix(int **matrix, int rows, int columns)
{
	/* iterators */
	int iterator_row;
	int iterator_column;
	/* iterate on rows */
	for (iterator_row=0; iterator_row < rows; iterator_row++)
	{
		printf("[DEBUG] ROW %d:\t\t",iterator_row);
		/* iterate on columns */
		for (iterator_column = 0; iterator_column < columns; iterator_column++)
		{
			printf("%d ",matrix[iterator_row][iterator_column]);
		}
		printf("\n");
	}
}

/* print_float_matrix: prints on screen a float matrix
 * parameter: matrix to print
 * parameter: number of individuals
 * parameter: number of containers
 * returns: nothing, it's void
 */
void print_float_matrix(float **matrix, int rows, int columns)
{
	/* iterators */
	int iterator_row;
	int iterator_column;
	/* iterate on rows */
	for (iterator_row=0; iterator_row < rows; iterator_row++)
	{
		printf("[DEBUG] ROW %d:\t",iterator_row);
		/* iterate on columns */
		for (iterator_column = 0; iterator_column < columns; iterator_column++)
		{
			printf("%g\t",matrix[iterator_row][iterator_column]);
		}
		printf("\n");
	}
}

/* print_int_array: prints on screen a int array
 * parameter: array to print
 * parameter: number of containers
 * returns: nothing, it's void
 */
void print_int_array(int *array, int columns)
{
	/* iterators */
	int iterator_column;
	/* iterate on columns */
	for (iterator_column = 0; iterator_column < columns; iterator_column++)
	{
		printf("[DEBUG] [%d]: %d\n",iterator_column,array[iterator_column]);
	}
}

/* print_float_array: prints on screen a float array
 * parameter: array to print
 * parameter: number of columns
 * returns: nothing, it's void
 */
void print_float_array(float *array, int columns)
{
	/* iterators */
	int iterator_column;
	/* iterate on columns */
	for (iterator_column = 0; iterator_column < columns; iterator_column++)
	{
		printf("[DEBUG] [%d]: %g\n",iterator_column,array[iterator_column]);
	}
}

/* load_H: load the values of H
 * parameter: number of physical machines
 * parameter: path to the datacenter file
 * returns: H matrix
 */
int** load_H(int h_size, char path_to_file[])
{
	/* datacenter file to read from */
	FILE *datacenter_file;
	/* line readed from file */
	char input_line[TAM_BUFFER];
	/* iterator */
	int iterator = 0;
	/* 1 if is reading the physical machines block in the file */
	int reading_physical = 0;
	/* memory reserve for h_size physical machines */
	int **H = (int **) malloc (h_size *sizeof (int *));
 	/* open the file for reading */
	datacenter_file = fopen(path_to_file,"r");
    /* if it is opened ok, we continue */
	if (datacenter_file != NULL)
	{
		/* read until the end */
		while(!feof(datacenter_file))
		{
			/* get line per line */
			fgets(input_line, TAM_BUFFER, datacenter_file);
			/* if the line is equal to H_HEADER, we begin the physical machines block in the file */
			if (strstr(input_line,H_HEADER) != NULL)
			{
				reading_physical = 1;
			}
			/* if the line is equal to V_HEADER, we end the physical machines block in the file */
			if (strstr(input_line,V_HEADER) != NULL)
			{
				reading_physical = 0;
				break;
			}
			/* if it's the correct block in the file, it is not the header and it is not a blank line, we count */
			if (reading_physical == 1 && strstr(input_line,H_HEADER) == NULL && strcmp(input_line, "\n") != 0)
			{
				/* reserve 4 columns for Processor, Memory, Storage and Power Consumption */
				H[iterator] = (int *) malloc (6 *sizeof (int));
				/* load on the matrix and increment iterator */
				sscanf(input_line,"%d %d %d %d %d %d\n",&H[iterator][0],&H[iterator][1],&H[iterator][2],&H[iterator][3],&H[iterator][4],&H[iterator][5]);
				iterator++;
			}
		}
	}
	fclose(datacenter_file);
	return H;
}

/* load_V: load the values of V
 * parameter: number of Containers
 * parameter: path to the datacenter file
 * returns: V matrix
 */
int** load_V(int v_size, char path_to_file[])
{
	/* datacenter file to read from */
	FILE *datacenter_file;
	/* line readed from file */
	char input_line[TAM_BUFFER];
	/* iterator */
	int iterator = 0;
	/* 1 if is reading the containers block in the file */
	int reading_virtual = 0;
	/* memory reserve for v_size containers */
	int **V = (int **) malloc (v_size *sizeof (int *));
 	/* open the file for reading */
	datacenter_file = fopen(path_to_file,"r");
    /* if it is opened ok, we continue */
	if (datacenter_file != NULL)
	{
		/* read until the end */
		while(!feof(datacenter_file))
		{
			/* get line per line */
			fgets(input_line, TAM_BUFFER, datacenter_file);
			/* if the line is equal to V_HEADER, we begin the containers block in the file */
			if (strstr(input_line,V_HEADER) != NULL)
			{
				reading_virtual = 1;
			}
			/* if the line is equal to T_HEADER, we end the containers block in the file */
			if (strstr(input_line,T_HEADER) != NULL)
			{
				reading_virtual = 0;
				break;
			}
			/* if it's the correct block in the file, it is not the header and it is not a blank line, we count */
			if (reading_virtual == 1 && strstr(input_line,V_HEADER) == NULL && strcmp(input_line, "\n") != 0)
			{
				/* reserve 4 columns for Processor, Memory, Storage and Service ID */
				V[iterator] = (int *) malloc (4 *sizeof (int));
				sscanf(input_line,"%d %d %d %d\n",&V[iterator][0],&V[iterator][1],&V[iterator][2],&V[iterator][3]);
				iterator++;
			}
		}
	}
	fclose(datacenter_file);
	return V;
}

/* load_utilization: loads the utilization of the physical machines of all the individuals
 * parameter: population matrix
 * parameter: physical machines matrix
 * parameter: containers matrix
 * parameter: number of individuals
 * parameter: number of physical machines
 * parameter: number of containers
 * returns: utilization tridimentional matrix
 */
int*** load_utilization(int **population, int **H, int **V, int number_of_individuals, int h_size, int v_size)
{
	/* iterators */
	int iterator_individual;
	int iterator_virtual;
	int iterator_physical;
	/* utilization holds the physical machines utilization of Processor, Memory and Storage of every individual */
	int ***utilization = (int ***) malloc (number_of_individuals *sizeof (int **));
	/* iterate on individuals */
	for (iterator_individual=0; iterator_individual < number_of_individuals; iterator_individual++)
	{
		/* requirements matrix, holds the sum of containers requirements for each physical machine */
		int **requirements = (int **) malloc (h_size *sizeof (int *));
		/* utilization holds the physical machines utilization of Processor, Memory and Storage of every individual */
		utilization[iterator_individual] = (int **) malloc (h_size *sizeof (int *));
		for (iterator_physical=0; iterator_physical < h_size; iterator_physical++)
		{
			/* container requirements in Processor, Memory and Storage. Initialized to 0 */
			requirements[iterator_physical] = (int *) malloc (3 *sizeof (int));
 			requirements[iterator_physical][0] = requirements[iterator_physical][1] = requirements[iterator_physical][2] = 0;
			/* physical machine utilization of Processor, Memory and Storage. Initialized to 0 */
			utilization[iterator_individual][iterator_physical] = (int *) malloc (3 *sizeof (int));
			utilization[iterator_individual][iterator_physical][0] = utilization[iterator_individual][iterator_physical][1] = utilization[iterator_individual][iterator_physical][2] = 0;
		}
		/* iterate on positions of an individual */
		for (iterator_virtual = 0; iterator_virtual < v_size; iterator_virtual++)
		{
			/* if the container has a placement assigned */
			if (population[iterator_individual][iterator_virtual] != 0)
			{
				/* increment the requirements of the assigned physical machine with the container requirements
				of Processor, Memory and Storage */
				requirements[population[iterator_individual][iterator_virtual]-1][0] += V[iterator_virtual][0];
				requirements[population[iterator_individual][iterator_virtual]-1][1] += V[iterator_virtual][1];
				requirements[population[iterator_individual][iterator_virtual]-1][2] += V[iterator_virtual][2];
			}
		}
		/* iterate on positions of an individual */
		for (iterator_physical=0; iterator_physical < h_size; iterator_physical++)
		{
			/* container requirements in Processor, Memory and Storage. Initialized to 0 */
			utilization[iterator_individual][iterator_physical][0] = requirements[iterator_physical][0];
			utilization[iterator_individual][iterator_physical][1] = requirements[iterator_physical][1];
			utilization[iterator_individual][iterator_physical][2] = requirements[iterator_physical][2];
		}
	}
	return utilization;
}

/* load_objectives: calculate the cost of each objective of each solution
 * parameter: population matrix
 * parameter: physical machines matrix
 * parameter: containers matrix
 * parameter: number of individuals
 * parameter: number of physical machines
 * parameter: number of containers
 * parameter: maximum values for  normalization
 * returns: cost of each objetive matrix
 */
float** load_objectives(int **population, int ***utilization, int **H, int **V, int number_of_individuals, int h_size, int v_size, int virtual_id, int max_surv, int serv_con_max)
{
	/* iterators */
	int iterator_individual;
	int iterator_virtual_id;
	int iterator_virtual;
	int iterator_virtual2;
	int iterator_physical;
	int iterator_physical2;
	float min_surv;
	float active_hosts;
	float services_connection = 0.0;
	float services_count = 0.0;
	/* value solution holds the cost of each solution */
	float **value_solution = (float **) malloc (number_of_individuals *sizeof (float *));
	for (iterator_individual = 0 ; iterator_individual < number_of_individuals; iterator_individual++)
		value_solution[iterator_individual] = (float *) malloc (4 *sizeof (float));
	/* iterate on individuals */
	for (iterator_individual = 0; iterator_individual < number_of_individuals; iterator_individual++)
	{
		min_surv = 10000;
		value_solution[iterator_individual][0] = value_solution[iterator_individual][1] = value_solution[iterator_individual][2] =
		value_solution[iterator_individual][3] = 0.0;

		/* iterate on containers */
		// calculate micro-services connection time
		// check if all micro-services for a service are placed. Else, return a high cost.

		for (iterator_virtual_id = 0 ; iterator_virtual_id < virtual_id ; iterator_virtual_id++)
		{
			int placed_service = -1;
			
			for (iterator_virtual = 0 ; iterator_virtual < v_size ; iterator_virtual++)
			{
				if (V[iterator_virtual][3] == iterator_virtual_id)
				{
					for (iterator_physical = 0 ; iterator_physical < h_size ; iterator_physical++)
					{
						if(iterator_physical+1 == population[iterator_individual][iterator_virtual])
						{
							placed_service = iterator_virtual;
							break;
						}
					}
					for (iterator_virtual2 = 0 ; iterator_virtual2 < v_size ; iterator_virtual2++)
					{
						for (iterator_physical2 = 0 ; iterator_physical2 < h_size ; iterator_physical2++) {
							if(iterator_physical2+1 == population[iterator_individual][iterator_virtual2] && V[iterator_virtual2][3] == iterator_virtual_id && iterator_virtual2!=placed_service){
								if (placed_service != -1)
								{
									services_connection = services_connection + abs(abs(H[iterator_physical2][0] - H[iterator_physical][0]) - abs(H[iterator_physical2][1] - H[iterator_physical][1]));
								}
								else
								{
									services_connection = 10.0;
									break;
								}
							}
						}
					}
					break;
				}
			}
		}
		/* iterate on vehicles */
		for (iterator_virtual = 0 ; iterator_virtual < v_size ; iterator_virtual++)
		{
			if(population[iterator_individual][iterator_virtual] > 0)
			{
				services_count++;
			}
		}

		/* iterate on vehicles */
		for (iterator_physical = 0 ; iterator_physical < h_size ; iterator_physical++)
		{
			if (utilization[iterator_individual][iterator_physical][0] > 0)
			{
				// Take the minimum vehicle availability if used

				if (H[iterator_physical][3] < min_surv ) {
					min_surv = H[iterator_physical][3];
				}
				//number of active hosts
				active_hosts = active_hosts + 1;
				//printf("%f active\n",active_hosts);
				//printf("%s\n",distance);
				//printf("%f %d %d\n\n",survivability,active_hosts,distance);
			}
		}
		/* loads energy consumption of each solution */
		value_solution[iterator_individual][0] = min_surv / max_surv;
		value_solution[iterator_individual][1] = services_connection / serv_con_max;
		value_solution[iterator_individual][2] = services_count / v_size;
		value_solution[iterator_individual][3] = active_hosts / h_size;
		min_surv = 0.0;
		services_count = 0.0;
		active_hosts = 0.0;
		services_connection = 0.0;
	}
	return value_solution;
}
