TARGET = PortVideoSDL
CSOURCES = $(shell ls ../common/*.c) 
COBJECTS = $(CSOURCES:.c=.o)
CPPSOURCES = $(shell ls ./*.cpp ../common/*.cpp ../ext/tinyxml/*.cpp) 
CPPOBJECTS = $(CPPSOURCES:.cpp=.o)

SDL_CFLAGS  := $(shell sdl-config --cflags)
SDL_LDFLAGS := $(shell sdl-config --libs)

COPTS  = -Wall -O3 -finline-functions -ffast-math -funroll-all-loops -fomit-frame-pointer
CDEBUG = -Wall -g
CFLAGS = $(COPTS) $(SDL_CFLAGS) -DLINUX
CXXFLAGS = $(INCLUDES) $(CFLAGS)
INCLUDES = -I../ext/tinyxml -I../ext/ccvt -I../common


LIBS = $(SDL_LDFLAGS) -ldc1394

all:	$(TARGET) 

$(TARGET) : $(CPPOBJECTS) $(COBJECTS)
	$(CXX) -o $@ $+ $(LIBS) 

clean:
	rm -f $(TARGET) $(CPPOBJECTS) $(COBJECTS)

run:	$(TARGET)
	./$(TARGET)

lib: $(TARGET)
	ar cq PortVideo.a $(CPPOBJECTS) $(COBJECTS)

install: $(TARGET)
	install -d $(DESTDIR)$(BINDIR)
	install -d $(DESTDIR)$(PREFIX)/share/$(TARGET)
	install -m 755 -c $(TARGET) $(DESTDIR)$(BINDIR)
	install -m 644 -c ../readme.txt $(DESTDIR)$(PREFIX)/share/$(TARGET)
	install -m 644 -c ../license.txt $(DESTDIR)$(PREFIX)/share/$(TARGET)
