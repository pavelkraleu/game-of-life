SOURCES := $(wildcard src/*.cpp src/*/*.cpp)
LDFLAGS = -lpng
EXECUTABLE = pavelkral
CXX=g++
CXXFLAGS=-Wall -pedantic -O3

.PHONY: all
all: $(SOURCES:.cpp=.o) doc
	@$(CXX) $(CXXFLAGS) $(SOURCES:.cpp=.o) -o $(EXECUTABLE) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f src/*.o src/*/*.o
	rm -f ./$(EXECUTABLE)
	rm -rf ./doc

.PHONY: run
run:
	./$(EXECUTABLE) ./examples/test_image_forrest_crop.png ./assets/patterns/ ./examples/out 2 0

.PHONY: runvalgrind
runvalgrind:
	valgrind --leak-check=full ./$(EXECUTABLE) ./examples/test_image_forrest_crop.png ./assets/patterns/ ./examples/out 2 0

.PHONY: doc
doc:
	mkdir -p doc
	doxygen Doxyfile

.PHONY: compile
compile: all
