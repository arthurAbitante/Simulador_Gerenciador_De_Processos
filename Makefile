CXX = g++
CXXFLAGS = -Wall -std=c++17 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf

SRC = main.cpp Process.cpp Scheduler.cpp Gui.cpp
OBJ = $(SRC:.cpp=.o)

BIN = scheduler_sim

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(BIN)