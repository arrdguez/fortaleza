CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2

SRCS = main.cpp Game.cpp Parser.cpp WorldData.cpp TerminalUI.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = fortaleza2

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp Types.h WorldData.h Parser.h TerminalUI.h Game.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
