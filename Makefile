MF=     Makefile
 
CC=     g++
 
CFLAGS= -g -fopenmp -msse4.2 -fomit-frame-pointer -funroll-loops 
 
LFLAGS= -std=c++11 -lahocorasick -I ./ahocorasick -L ./ahocorasick -I ./libdatrie/include -L ./libdatrie/lib -ldatrie -Wl,-rpath=$(PWD)/libdatrie/lib -lz -DNDEBUG  

EXE=    fwsm
 
SRC=    main.cpp input.cpp preparation.cpp wpm.cpp kmp.cpp wtm.cpp aca.cpp filter.cpp
 
HD=     global.h defs.h aca.h trie.h  Makefile
 
# 
# No need to edit below this line 
# 
 
.SUFFIXES: 
.SUFFIXES: .cpp .o 
 
OBJ=    $(SRC:.cpp=.o) 
 
.cpp.o: 
	$(CC) $(CFLAGS)-c $(LFLAGS) $< 
 
all:    $(EXE) 
 
$(EXE): $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LFLAGS) 
 
$(OBJ): $(MF) $(HD) 
 
clean: 
	rm -f $(OBJ) $(EXE) *~
