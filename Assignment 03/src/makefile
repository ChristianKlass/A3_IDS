all: IDS

IDS: IDS.o Stat.o Entry.o
	g++ IDS.o Stat.o Entry.o -o IDS
	@echo "Compilation successful.  Do \"make run\" to run the program."

IDS.o: IDS.cpp IDS.hpp Stat.o Entry.o
	g++ -c IDS.cpp

Stat.o: Stat.cpp Stat.hpp
	g++ -c Stat.cpp

Entry.o: Entry.cpp Entry.hpp
	g++ -c Entry.cpp

clean:
	@\rm *.o
	@\rm IDS
	@echo "Directory cleaned."

run:
	@./IDS

