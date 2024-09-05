CC = g++

hotel: hotel.cpp
	g++ hotel.cpp -o hotel

clean:
	rm hotel

test: hotel
	bash test.sh
