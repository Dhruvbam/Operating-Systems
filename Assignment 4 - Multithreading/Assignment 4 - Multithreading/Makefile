CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pthread
TARGET = assignment_4
SRCS = ass4.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
