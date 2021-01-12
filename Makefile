
OBJ:=src/prime_gen.o  src/primes.o  src/queue_dispatch.o src/file_writer.o

all:prime_gen

prime_gen:$(OBJ)
	g++ -Ofast $(OBJ) -o prime_gen -lpthread

%.o:%.cpp
	g++ -Iincl -Ofast -c $*.cpp  -o $*.o

clean:
	rm -f prime_gen *.o
