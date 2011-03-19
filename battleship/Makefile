battleship: Board 
	g++ Driver.cpp *.o -o battleship 

Board: Board.cpp Board.h
	g++ -Wall -c BoardTest.cpp Board.cpp

Player: Player.cpp Player.h 
	g++ -Wall -c Player.cpp 

Fleet: Fleet.cpp Fleet.h 
	g++ -Wall -c Fleet.cpp 

run: battleship
	./battleship
