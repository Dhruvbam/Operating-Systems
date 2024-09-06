CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDLIBS = -lcurl -lstdc++	
SRCS = assignment_3.cpp
OBJS = $(SRCS:.cpp=.o)

EXEC = assignment_3

all: $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(LDLIBS) $(OBJS)

clean:
	rm -f $(OBJS) $(EXEC)