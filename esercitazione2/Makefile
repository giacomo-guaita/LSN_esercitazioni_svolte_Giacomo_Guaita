CC = g++
CFLAGS = -Wall -O3 --std=c++11

es1 : es1.o random.o MCIntegral.o statfunctions.o
	$(CC) random.o es1.o MCIntegral.o statfunctions.o -o es1
es2 : es2.o random.o statfunctions.o brownian.o position.o
	$(CC) random.o es2.o statfunctions.o brownian.o position.o -o es2
es2.o : es2.cpp random.h brownian.h statfunctions.h
	$(CC) -c es2.cpp $(CFLAGS)
es1.o : es1.cpp random.h cospi.h MCIntegral.h cos_taylor.h
	$(CC) -c es1.cpp $(CFLAGS)
brownian.o :brownian.cpp brownian.h position.h
	$(CC) -c brownian.cpp $(CFLAGS)
position.o :position.cpp position.h
	$(CC) -c position.cpp $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp $(CFLAGS)
MCIntegral.o : MCIntegral.cpp MCIntegral.h random.h function.h
	$(CC) -c MCIntegral.cpp $(CFLAGS)
statfunctions.o : statfunctions.cpp statfunctions.h
	$(CC) -c statfunctions.cpp $(CFLAGS)
clean :
	rm *.o es1 es2 seed.out
