# Variables
CXX = g++
CXXFLAGS = -std=c++11 -I src

SRC_DIR = src
CORE_DIR = $(SRC_DIR)/core
ROOMS_DIR = $(SRC_DIR)/core/rooms
OBJECTS_DIR = $(SRC_DIR)/objects
FURNITURE_DIR = $(SRC_DIR)/furniture
UTILS_DIR = $(SRC_DIR)/utils

SOURCES = $(wildcard $(CORE_DIR)/*.cpp $(ROOMS_DIR)/*.cpp $(OBJECTS_DIR)/*.cpp $(FURNITURE_DIR)/*.cpp $(UTILS_DIR)/*.cpp $(SRC_DIR)/main.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

TARGET = mud-game

# Rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
