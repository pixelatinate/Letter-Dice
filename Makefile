CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
LDFLAGS=	
SHELL=		bash
PROGRAMS=	worddice
SOURCES=	worddice.cpp
OBJECTS=	$(SOURCES:.cpp=.o)

all:		$(PROGRAMS)

worddice:	$(OBJECTS) 
	$(CXX) $(LDFLAGS)-o $@ $(OBJECTS)

clean:
	rm -f $(PROGRAMS) $(OBJECTS)

test: 		$(PROGRAMS) 
	./gradeall