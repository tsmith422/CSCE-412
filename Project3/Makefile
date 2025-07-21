CXX = g++
CXXFLAGS = -std=c++11 -Iinclude -Wall

SRC = src/main.cpp \
      src/LoadBalancer.cpp \
      src/WebServer.cpp \
      src/RequestQueue.cpp \
      src/utility.cpp

OBJ = $(SRC:.cpp=.o)

TARGET = loadbalancer

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)
