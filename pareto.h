/*
 * pareto.h: Vehicular Container Placement Problem - Pareto Header
 * Date: 01-12-2019
 * Author: Hani Sami (hos03@mail.aub.edu)
 * IEEE TNET 2020
 */

/* include functions */
struct pareto_element * pareto_create(int v_size, int *individual, float *objectives_functions);
struct pareto_element * pareto_insert(struct pareto_element *pareto_head, int v_size, int *individual, float *objectives_functions);
void pareto_remove_duplicates(struct pareto_element *pareto_head, int v_size);
float get_min_cost(struct pareto_element *pareto_head, int objective);
float get_max_cost(struct pareto_element *pareto_head, int objective);
void print_pareto_set(struct pareto_element *pareto_head, int v_size);
void print_pareto_front(struct pareto_element *pareto_head);
int load_pareto_size(struct pareto_element *pareto_head);
void report_best_population(struct pareto_element *pareto_head, int **H, int **V, int v_size, int h_size);
void getHighestFitnessSolution(struct pareto_element *pareto_head, int **H, int **V, int v_size, int h_size);
