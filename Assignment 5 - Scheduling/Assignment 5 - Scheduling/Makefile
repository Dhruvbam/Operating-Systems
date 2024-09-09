CC = g++
CFLAGS = -std=c++11 -Wall -Wextra

assignment_5: ass5.o
	$(CC) $(CFLAGS) ass5.o -o assignment_5

ass5.o: ass5.cpp
	$(CC) $(CFLAGS) -c ass5.cpp

clean:
	rm -f *.o assignment_5