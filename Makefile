# Makefile

FLAGS = -std=c++14

# (For main)
# Get all .cpp files in /src directory and make object files
SRC := $(shell find ./src -name '*.cpp')
OBJ := $(addsuffix .o,$(basename $(SRC)))

# (For test)
# Get all .cpp files (except main.cpp) and make object files
TST_SRC := $(shell find . -name '*.cpp' -not -name 'main.cpp')
TST_OBJ := $(addsuffix .o,$(basename $(TST_SRC)))

# Build all executables and run unit tests
all: main test

# Launch main program
run: main
	./build/main

# Build main executable
main: $(OBJ)
	g++ $(FLAGS) $^ -o $@
	mv main ./build/main

# Build and run unit tests
test: $(TST_OBJ)
	g++ $(FLAGS) $^ -o $@
	mv test ./build/test
	./build/test

clean:
	# Delete object files
	find . -name \*.o -type f -delete 
	# Delete executables
	find . -type f -perm +111 -delete 

# Generic object file rule
%.o: %.cpp
	g++ -c $< -o $@

