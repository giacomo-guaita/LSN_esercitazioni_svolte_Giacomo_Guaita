CC = g++
CFLAGS = -Wall -O3 --std=c++11

genetic_salesman : genetic_salesman.o random.o classes.o
	$(CC) random.o genetic_salesman.o classes.o -o genetic_salesman
genetic_salesman.o : genetic_salesman.cpp random.h classes.h
	$(CC) -c genetic_salesman.cpp -o genetic_salesman.o $(CFLAGS)
classes.o : classes.cpp classes.h random.h
	$(CC) -c classes.cpp -o classes.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o genetic_salesman seed.out
clear :
	rm *.dat