CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude
# Linker Flags: add the crypto library for SHA256
LDFLAGS = -lcrypto

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

EXECUTABLE = $(BINDIR)/main

all: $(EXECUTABLE)

# CRITICAL FIX IS HERE: Added $(LDFLAGS) to the end of the command
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

run: all
	./$(EXECUTABLE)

.PHONY: all clean run
