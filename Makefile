# Tair Mazriv
# id: 209188382
# tairmazriv@gmail.com

CXX=g++
CXXFLAGS=-std=c++20 -Wall -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES=Board.cpp Catan.cpp Player.cpp DevelopmentCard.cpp Build.cpp Demo.cpp TestCounter.cpp Tests.cpp Test.cpp
HEADERS=Catan.hpp Build.hpp Board.hpp Player.hpp DevelopmentCard.hpp doctest.h
OBJECTS=$(SOURCES:.cpp=.o)

all: demo tests

run: demo
	./$^

demo: Demo.o Board.o Catan.o Player.o DevelopmentCard.o Build.o
	$(CXX) $(CXXFLAGS) $^ -o demo

catan: Demo.o Board.o Catan.o Player.o DevelopmentCard.o Build.o
	$(CXX) $(CXXFLAGS) $^ -o catan
	./catan

tests: Tests.o Board.o Catan.o Player.o DevelopmentCard.o Build.o
	$(CXX) $(CXXFLAGS) $^ -o tests

cppcheck:
	cppcheck $(SOURCES) --enable=all

valgrind: demo test tests
	valgrind $(VALGRIND_FLAGS) ./demo
	valgrind $(VALGRIND_FLAGS) ./test
	valgrind $(VALGRIND_FLAGS) ./tests

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o demo test catan tests
