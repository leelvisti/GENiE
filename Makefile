GENiE.exe: GENiE.o gene.o auxilliary.o
	g++ -std=c++14 -o GENiE.exe GENiE.o auxilliary.o gene.o

GENiE.o: GENiE.cpp
	g++ -std=c++14 -c GENiE.cpp

gene.o: gene.cpp
	g++ -std=c++14 -c gene.cpp

auxilliary.o: auxilliary.cpp
	g++ -std=c++14 -c auxilliary.cpp

.PHONY: clean
clean:
	rm *.o
	rm *.exe

.PHONY: update
update:
	make clean
	make
