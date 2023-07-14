CC = g++
CFLAGS = -Wall -O3 --std=c++11
RND:=../RANDOM_GEN

es1 : es1.o random.o statfunctions.o
	$(CC) random.o es1.o statfunctions.o -o es1
es2 : es2.o random.o
	$(CC) random.o es2.o -o es2
es3 : es3.o random.o statfunctions.o
	$(CC) random.o statfunctions.o es3.o -o es3
es2.o : es2.cpp random.h
	$(CC) -c es2.cpp -o es2.o $(CFLAGS)
es3.o : es3.cpp random.h
	$(CC) -c es3.cpp -o es3.o $(CFLAGS)
es1.o : es1.cpp random.h statfunctions.h
	$(CC) -c es1.cpp -o es1.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
statfunctions.o : statfunctions.cpp statfunctions.h
	$(CC) -c statfunctions.cpp -o statfunctions.o $(CFLAGS)
clean :
	rm *.o es1 es2 es3 seed.out


