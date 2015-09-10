CC=		g++
CFLAGS=	-g	-Wall
main: main.o	wpm-simple.o	kmp.o
clean:
	rm main main.o wpm-simple.o kmp.o
