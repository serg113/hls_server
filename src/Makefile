CXX ?= g++

CXXFLAGS += -c -Wall $(shell pkg-config --cflags opencv)
LDFLAGS += -lz $(shell pkg-config --libs --static opencv)

SOURCES = main.cpp\
	  LiveStream.cpp\
	  NetworkService.cpp\
	  tests.cpp\
	  utils.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = ss

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
       	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJECTS): $(SOURCES)
	$(CXX) $< -o $@ $(CXXFLAGS)

clean: ; rm -f main.o ss
