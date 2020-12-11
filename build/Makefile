CC = g++ # adapt to your system
FLAGS = -g -Wall -std=c++11 # c++11 is essential

SDIR = ../src
IDIR = ../include

ifeq ($(THANOS), yes)
    FLAGS += -DTHANOS
endif

###################################

endgame: endgame.o disc.o simulation.o particle.o utils.o
	$(CC) $(FLAGS) -o endgame endgame.o disc.o simulation.o particle.o utils.o

simulation.o: $(SDIR)/simulation.cpp $(IDIR)/disc.h $(IDIR)/utils.h $(IDIR)/particle.h $(IDIR)/simulation.h $(IDIR)/utils.h
	$(CC) $(FLAGS) -o simulation.o -c $(SDIR)/simulation.cpp

particle.o: $(SDIR)/particle.cpp $(IDIR)/disc.h $(IDIR)/particle.h
	$(CC) $(FLAGS) -o particle.o -c $(SDIR)/particle.cpp

disc.o: $(SDIR)/disc.cpp $(IDIR)/utils.h $(IDIR)/disc.h
	$(CC) $(FLAGS) -o disc.o -c $(SDIR)/disc.cpp

utils.o: $(SDIR)/utils.cpp $(IDIR)/utils.h
	$(CC) $(FLAGS) -o utils.o -c $(SDIR)/utils.cpp

endgame.o: $(SDIR)/endgame.cpp $(IDIR)/simulation.h
	$(CC) $(FLAGS) -o endgame.o -c $(SDIR)/endgame.cpp

###################################

all: endgame clean

clean:
	rm *.o
