CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = airlineSystem

all: $(TARGET)

$(TARGET): airlineSystem.o main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) airlineSystem.o main.o

airlineSystem.o: airlineSystem.cpp airlineSystem.h
	$(CXX) $(CXXFLAGS) -c airlineSystem.cpp

main.o: main.cpp airlineSystem.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o $(TARGET)