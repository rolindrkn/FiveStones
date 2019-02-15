FiveStone: FiveStone.o 
	g++ FiveStone.o -o FiveStone
FiveStone.o: FiveStone.cpp
	g++ -c FiveStone.cpp