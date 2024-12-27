# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g -std=c++11

# Targets for each program
TARGETS = h1_program h2_program h3_program h4_program

# Individual programs
all: $(TARGETS)

# h1_program
h1_program: h1.o image.o DisjSets.o
	$(CXX) $(CXXFLAGS) -o h1_program h1.o image.o DisjSets.o

# h2_program
h2_program: h2.o image.o DisjSets.o
	$(CXX) $(CXXFLAGS) -o h2_program h2.o image.o DisjSets.o

# h3_program
h3_program: h3.o image.o DisjSets.o
	$(CXX) $(CXXFLAGS) -o h3_program h3.o image.o DisjSets.o

# h4_program
h4_program: h4.o image.o DisjSets.o
	$(CXX) $(CXXFLAGS) -o h4_program h4.o image.o DisjSets.o

# Compile each .cc file into a corresponding .o file
%.o: %.cc image.h DisjSets.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executables
clean:
	rm -f *.o $(TARGETS)

# Phony targets
.PHONY: all clean
