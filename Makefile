CC=c++
LD=c++
CCFLAGS=-I include -g -c -o
LDFLAGS=-o

all: library test

clean:
	rm bin/test-theta-lexer bin/obj/main.o
	rm bin/theta-lexer.so

library: bin/theta-lexer.so

bin/theta-lexer.so: src/theta.cc include/theta.hh
	$(CC) src/theta.cc -shared -fPIC $(CCFLAGS) bin/theta-lexer.so

test: bin/test-theta-lexer

bin/obj/main.o: src/main.cc include/theta.hh
	$(CC) src/main.cc $(CCFLAGS) bin/obj/main.o

bin/test-theta-lexer: bin/theta-lexer.so bin/obj/main.o
	$(LD) bin/theta-lexer.so bin/obj/main.o $(LDFLAGS) bin/test-theta-lexer

