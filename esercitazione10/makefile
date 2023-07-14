CC = mpiCC
CFLAGS = -Wall -O3 --std=c++11

parallel_genetic_salesman : parallel_genetic_salesman.o random.o classes.o
	$(CC) random.o parallel_genetic_salesman.o classes.o -o parallel_genetic_salesman
parallel_genetic_salesman.o : parallel_genetic_salesman.cpp random.h classes.h
	$(CC) -c parallel_genetic_salesman.cpp -o parallel_genetic_salesman.o $(CFLAGS)
classes.o : classes.cpp classes.h random.h
	$(CC) -c classes.cpp -o classes.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o parallel_genetic_salesman seed.out
clear_output :
	rm mean.dat best.dat draw.dat
