xo: bin/main.o bin/io.o bin/helpers.o bin/core.o bin/computer.o
	gcc -Wall -o xo bin/main.o bin/io.o bin/helpers.o bin/core.o \
					bin/computer.o

computer: bin/computer.o bin/core.o bin/helpers.o bin/io.o
	gcc -Wall -o computer bin/computer.o bin/core.o bin/helpers.o bin/io.o

bin/io.o: io.c io.h
	gcc -Wall -o bin/io.o -c io.c

bin/main.o: main.c 
	gcc -Wall -o bin/main.o -c main.c

bin/helpers.o: helpers.c helpers.h
	gcc -Wall -o bin/helpers.o -c helpers.c

bin/core.o: core.c core.h common.h
	gcc -Wall -o bin/core.o -c core.c

bin/computer.o: computer.c computer.h common.h
	gcc -Wall -o bin/computer.o -c computer.c

clean:
	rm bin/* xo computer
