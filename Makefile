CXXFLAGS = -Wall -lX11 -lXtst -lXss

all: cursor_move

cursor_move: cursor_move.cpp
	g++ $^ $(CXXFLAGS) -o $@ 

clean: 
	@rm -f cursor_move
