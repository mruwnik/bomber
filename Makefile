CXX = g++
LDFLAGS = -lvga -lncurses -Wall

OBJS = baddy.o blok.o board.o bomb.o initialiser.o main.o object.o player.o twin.o
SRCS = $(OBJS:.o=.cpp)

bomber: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o bomber 

clean:
	rm -f *.o *~ .*swp 
