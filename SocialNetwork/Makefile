# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Iinclude

# Linker flags
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRCS = src/main.cpp src/User.cpp src/Post.cpp src/Network.cpp src/Graph.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = social_network

# Default target
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(EXEC)

# Phony targets
.PHONY: all clean
