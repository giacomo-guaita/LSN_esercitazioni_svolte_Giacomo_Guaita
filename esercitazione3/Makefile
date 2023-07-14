CC = g++
CFLAGS = -Wall -O3 --std=c++11

es1 : es1.o random.o BSprice.o statfunctions.o
	$(CC) random.o BSprice.o statfunctions.o es1.o -o es1
es1.o : es1.cpp random.h
	$(CC) -c es1.cpp -o es1.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
BSprice.o : BSprice.cpp BSprice.h random.h
	$(CC) -c BSprice.cpp -o BSprice.o $(CFLAGS)
statfunctions.o : statfunctions.cpp statfunctions.h
	$(CC) -c statfunctions.cpp -o statfunctions.o $(CFLAGS)
clean :
	rm *.o es1 seed.out
