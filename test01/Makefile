CFLAGS = -Wall
LFLAGS = -Wall
TEST_NAME = test01

gcc : main.gcc.o overwrite.gcc.o
	g++ $(LFLAGS) main.gcc.o overwrite.gcc.o -o $(TEST_NAME)

clang : main.clang.o overwrite.clang.o
	clang++ $(LFLAGS) main.clang.o overwrite.clang.o -o $(TEST_NAME)

main.gcc.o : main.cpp
	g++ $(CFLAGS) -c main.cpp -o main.gcc.o

main.clang.o : main.cpp
	clang++ $(CFLAGS) -c main.cpp -o main.clang.o

overwrite.gcc.o : overwrite.cpp
	g++ $(CFLAGS) -c overwrite.cpp -o overwrite.gcc.o

overwrite.clang.o : overwrite.cpp
	clang++ $(CFLAGS) -c overwrite.cpp -o overwrite.clang.o

symbols_overwrite: overwrite.gcc.o overwrite.clang.o
	nm -A overwrite.gcc.o | grep "[tTwW] "
	nm -A overwrite.clang.o | grep "[tTwW] "

symbols_main: main.gcc.o main.clang.o
	nm -A main.gcc.o | grep "[tTwW] "
	nm -A main.clang.o | grep "[tTwW] "

symbols: symbols_overwrite symbols_main

clean:
	\rm *.o *~ $(TEST_NAME)
