CXX = g++
CFLAGS = -Wall -DUSE_FTGL -c

ifdef NCURSES
LDFLAGS = -lvga -lncurses
else
LDFLAGS = -lglut -lftgl  
endif
ifdef USE_FTGL
LDFLAGS = $(LDFLAGS) -lftgl
endif


EXECUTABLE=bomber
SOURCES= baddy.cpp blok.cpp board.cpp bomb.cpp fire.cpp initialiser.cpp keys.cpp main.cpp menu.cpp object.cpp player.cpp twin.cpp Tga.cpp
OBJS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o bomber 

.cpp.o:
	$(CXX) $(CFLAGS)  $< -o $@

clean:
	rm -f *.o *~ .*swp 
