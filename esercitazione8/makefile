CC = g++
CFLAGS = -Wall -O3 --std=c++11

es1 : es1.o random.o MetroIntegral.o statfunctions.o
	$(CC) random.o MetroIntegral.o statfunctions.o es1.o -o es1
es2 : es2.o random.o MetroIntegral.o statfunctions.o sim_annealing.o
	$(CC) random.o MetroIntegral.o statfunctions.o sim_annealing.o es2.o -o es2
es2.o : es2.cpp random.h
	$(CC) -c es2.cpp -o es2.o $(CFLAGS)
es1.o : es1.cpp random.h
	$(CC) -c es1.cpp -o es1.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
MetroIntegral.o : MetroIntegral.cpp MetroIntegral.h random.h statfunctions.h
	$(CC) -c MetroIntegral.cpp -o MetroIntegral.o $(CFLAGS)
sim_annealing.o : sim_annealing.cpp sim_annealing.h MetroIntegral.h psi2.h Integrand.h
	$(CC) -c sim_annealing.cpp -c sim_annealing.o $(CFLAGS)
statfunctions.o : statfunctions.cpp statfunctions.h
	$(CC) -c statfunctions.cpp -o statfunctions.o $(CFLAGS)
clean :
	rm *.o es1 seed.out
clear:
	rm *.dat
