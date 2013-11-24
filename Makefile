
#Makefile for quantum minigolf; edit according to your needs 

SHELL=/bin/sh

# Source of the installation. No need to change this
SRCDIR	= .

CC	= g++
LDFLAGS	= -L/usr/lib -L/usr/local/lib -lm -lSDL -lSDL_ttf -lfftw3f -ldc1394
INCFLAGS	= -I/usr/include/SDL \
			  -I/home/matthias/Desktop/QM/PortVideoSDL/common \
			  -I/home/matthias/Desktop/QM/PortVideoSDL/ext/tinyxml
#CFLAGS	= -O3 -fomit-frame-pointer -finline-functions -Wall -Wno-unused -malign-double -funroll-all-loops -DLINUX -DVR
CFLAGS	= -O0 -ggdb -Wall -malign-double -DLINUX -DVR
LDSOFLAGS	= -Wl

OBJS	= quantumminigolf.o Renderer.o ClassicSimulator.o QuantumSimulator.o SoftwareTracker.o Tracker.o TrackSelector.o WebcamTracker.o
EXE	= quantumminigolf

PORTVIDEO = /home/matthias/Desktop/QM/PortVideoSDL/linux/PortVideo.a

# pattern rule to compile object files from C files
# might not work with make programs other than GNU make
%.o : %.cpp Makefile
	$(CC) $(INCFLAGS) $(CFLAGS) -c $< -o $@ 

all: $(EXE)

$(EXE): $(OBJS) Makefile
	$(CC) -o $(EXE) $(OBJS) $(PORTVIDEO) $(LDFLAGS) $(CFLAGS)

.PHONY : clean
clean:
	rm -f $(OBJS) $(EXE)

