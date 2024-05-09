# Compiler
CXX := g++

# Directories
SRCDIR := src
BUILDDIR := build
TARGET := main

# Files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))

# Build target
$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@

# Compile rule
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) -c -o $@ $<

# Clean rule
clean:
	@rm -rf $(BUILDDIR) $(TARGET)

# Run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
