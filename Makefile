CXX=g++
LD=g++
BASIC_FLAGS=-std=c++17 -Wall -pedantic
LIBS=-lncurses

HEADERS := $(wildcard src/*.hpp)
SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(SOURCES:src/%.cpp=build/%.o)
DEPENDS := $(SOURCES:src/%.cpp=build/%.d)
.PHONY: all run doc compile start_test

all: compile doc

run: compile
	@./konviji1

doc: $(SOURCES) $(HEADERS) Doxyfile
	doxygen

compile: konviji1

konviji1: build/main
	cp $< $@

build/main: $(OBJECTS)
	mkdir -p $(@D)
	$(LD) $^ -o $@ $(LIBS)

-include $(DEPENDS)

build/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(BASIC_FLAGS) -MMD -MP $< -c -o $@ $(LIBS)

clean:
	rm -rf konviji1 build/ build-tests/ doc/ 2>/dev/null

start_test: build-tests/test
	@./build-tests/test

build-tests/test: tests/test.cpp $(filter-out build/main.o,$(OBJECTS))
	mkdir -p $(@D)
	$(LD) $(BASIC_FLAGS) $< $(filter-out build/main.o,$(OBJECTS)) -o $@ $(LIBS)
