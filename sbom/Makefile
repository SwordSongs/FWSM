LIBNAME := libsbom.a
CFLAGS := -g 
HEADERS := sbom.h automaton.h fifo.h listOfNumbers.h sm.h dawg.h listOfIntegers.h oracle.h triple.h 

$(LIBNAME): sbom.o dawg.o listOfIntegers.o multirf.o fifo.o listOfNumbers.o oracle.o triple.o
	ar -cvq $(LIBNAME) sbom.o dawg.o listOfIntegers.o multirf.o fifo.o listOfNumbers.o oracle.o triple.o

sbom.o: sbom.c $(HEADERS)
	g++ -c sbom.c $(CFLAGS)

dawg.o: dawg.c $(HEADERS)
	g++ -c dawg.c $(CFLAGS)

listOfIntegers.o: listOfIntegers.c $(HEADERS)
	g++ -c listOfIntegers.c $(CFLAGS)

multirf.o: multirf.c $(HEADERS)
	g++ -c multirf.c $(CFLAGS)

fifo.o: fifo.c $(HEADERS)
	g++ -c fifo.c $(CFLAGS)

listOfNumbers.o: listOfNumbers.c $(HEADERS)
	g++ -c listOfNumbers.c $(CFLAGS)

oracle.o: oracle.c $(HEADERS)
	g++ -c oracle.c $(CFLAGS)

triple.o: triple.c $(HEADERS)
	g++ -c triple.c $(CFLAGS)

clean:
	rm -f ahocorasick.o node.o $(LIBNAME)
