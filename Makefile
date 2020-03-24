IDIR = ./
CXX = g++
CXXFLAGS = -Wall -Wextra
DEBUGFLAGS = -g -O0 -D _DEBUG
RELEASEFLAGS = -O2 
CXXGCOV = --coverage

DEPS = bitarray.h
SOURCES = main.cpp bitarray.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = main.out

ODIR = obj
OBJ = $(patsubst %, $(ODIR)/%, $(OBJECTS))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(DEBUGFLAGS) $(CXXGCOV)

release: $(SOURCES)
	$(CXX) $(CXXFLAGS) $(RELEASEFLAGS) -I $(IDIR) -o $(TARGET) $^

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(DEBUGFLAGS) $(CXXGCOV) -I $(IDIR)

.PHONY: all clean

clean:
	rm -f $(ODIR)/*.o

# can include *.d with -MD flag 
