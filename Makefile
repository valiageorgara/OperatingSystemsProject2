make:
	g++ -o exe main.c structs.h
clean:
	rm -rf *.o
	rm -rf exe
