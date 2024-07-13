# Compiler
CXX := g++

# Directories
SRCDIR := src
ALGORITHMDIR := src/algorithms
BUILDDIR := build
TARGET := main

# Files
SOURCES := $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(ALGORITHMDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(patsubst $(ALGORITHMDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o)))

# Build target
$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@

# Compile rule for main and image
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) -c -o $@ $<

# Compile rule for algorithms
$(BUILDDIR)/%.o: $(ALGORITHMDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) -c -o $@ $<

# Clean rule
clean:
	@rm -rf $(BUILDDIR) $(TARGET)

# Run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
