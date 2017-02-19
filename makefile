CXX = g++
CXXFLAGS = -Ofast -Wall -Wextra
LDFLAGS = $(CXXFLAGS)
TARGET = orbit

all: $(TARGET)
	$(info)

$(TARGET): $(TARGET).cpp
	$(CXX) $(LDFLAGS) $(TARGET).cpp -o $(TARGET)

