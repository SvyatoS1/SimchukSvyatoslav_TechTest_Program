CC = g++
CFLAGS = -Wall

all: FindFilesByName.o lib_FindFilesByName.a FindFilesByNameProgram

FindFilesByNameProgram: main.cpp lib_FindFilesByName.a
	$(CC) $(CFLAGS) main.cpp -L. -l_FindFilesByName -o FindFilesByNameProgram

FindFilesByName.o: FindFilesByName.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

lib_FindFilesByName.a: FindFilesByName.o
	ar rcs $@ $^
	rm -f FindFilesByName.o

clean:
	rm -f FindFilesByName.o lib_FindFilesByName.a FindFilesByNameProgram		