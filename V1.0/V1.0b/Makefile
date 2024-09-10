# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -I"C:/crow" -I"C:/asio"

# Linker flags for WSAStartup and Mswsock.lib
LDFLAGS = -lWs2_32 -lMswsock

# Executable name
TARGET = crow

# Source files
SRCS = crow_server.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Build rules
all: sqlite3CPP $(TARGET) 

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS) sqlite3/sqlite3.o $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Sqlite3 target for c++ compilation
sqlite3CPP: sqlite3/sqlite3.c
	gcc -o sqlite3/sqlite3.o -c $^

clean:
	rm -f $(TARGET) $(OBJS) *.exe

.PHONY: all clean
