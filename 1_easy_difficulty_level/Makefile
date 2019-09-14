CC=gcc
CXX=g++
CODE_FORMAT=clang-format
CODE_FORMAT_PARAMS=-i -style=Chromium
RM=rm -f
CPPFLAGS=-Wall -Wextra -Wpedantic -std=c++17 -O3 -Ofast -fexceptions
BUILD_DIR=build

SRCS=$@
OBJS=$(subst .cpp,.o,$(SRCS))

all: test

test:
	$(CXX) $(CPPFLAGS) $@ -o $(BUILD_DIR)/test.exe


format:
	$(CODE_FORMAT) $(CODE_FORMAT_PARAMS) $(SRCS)

run:	
	$(BUILD_DIR)/test.exe
	

clean:
	$(RM) $(BUILD_DIR)/test $(BUILD_DIR)/test.exe *.o *.obj
