CXX=g++
CXXFLAGS=-Wall -I. -std=c++11
DEPFLAGS=-MMD -MP
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
DEP=$(OBJ:.o=.d)
TARGET=game

all: $(TARGET)

$(TARGET): $(OBJ) | sync-deps
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

sync-deps:
	@for obj in $(OBJ); do \
		d=$${obj%.o}.d; \
		if [ -f $$obj ] && [ ! -f $$d ]; then rm -f $$obj; fi; \
	done

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(DEP) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run sync-deps

-include $(DEP)