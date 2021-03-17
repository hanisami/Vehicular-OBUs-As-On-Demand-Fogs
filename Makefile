all:
	gcc -c common.c initialization.c reparation.c local_search.c variation.c pareto.c cpp.c
	gcc -o cpp common.o initialization.o reparation.o local_search.o variation.o pareto.o cpp.o -lm
clean:
	rm -rf *o imavmp
init:
	rm -rf results/pareto_*
debug:
	gcc -g -c common.c initialization.c reparation.c local_search.c variation.c pareto.c cpp.c
	gcc -g -o cpp common.o initialization.o reparation.o local_search.o variation.o pareto.o cpp.o -lm
