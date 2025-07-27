CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
TARGET = duck_game
SOURCE = Source.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE) $(SFML_FLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run