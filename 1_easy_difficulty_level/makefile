CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-Wall -Wextra -Wpedantic -std=c++17 -O3 -Ofast
SRCS=33_superincreasing.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: 33_superincreasing

33_superincreasing: $(OBJS)
	$(CXX) $(CPPFLAGS) -o 33_superincreasing $(OBJS) 

33_superincreasing.o: 33_superincreasing.cpp

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) 33_superincreasing