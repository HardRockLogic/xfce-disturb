CXXFLAGS = -Wall -lX11 -lXtst -lXss

all: cursor_move

mouse.o: mouse.cpp
	g++ -c $^ $(CXXFLAGS)

cursor_move.o: cursor_move.cpp
	g++ -c $^ $(CXXFLAGS)  

cursor_move: cursor_move.o mouse.o
	g++ $^ $(CXXFLAGS) -o $@ 

clean: 
	@rm -f cursor_move 

rmobj: 
	@rm mouse.o cursor_move.o
