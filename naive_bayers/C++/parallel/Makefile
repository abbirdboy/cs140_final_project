CXX = icc
# CXX = clang++ # has better error messages

CFLAGS = -c -Wall -O2 -std=c++0x


all: naive_bayers

naive_bayers: main.o model.o
	$(CXX) $^ -o $@

main.o: main.cpp
	$(CXX) $(CFLAGS) main.cpp

model.o: model.cpp
	$(CXX) $(CFLAGS) model.cpp

clean:
	rm *o naive_bayers
