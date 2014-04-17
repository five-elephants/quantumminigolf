Quantum Minigolf
================

This is a fork of the original Quantum Minigolf by Friedemann Reinhard. In
short, this version is more of a game compared to the original. The player starts a
game with three lives, of which he looses one for every failed level. Also, each
successful level adds points to the score while a failed level reduces it. At
the end scores are collected in a highscore list with the top nine players.

The game was played enthusiastically on the Christmas party of the
Kirchhoff-Institute for Physics in Heidelberg, Germany in 2013 using a virtual
reality setup with camera and projector.


Overview of technical changes
-----------------------------

* This version integrates the portvideo library as a subdirectory. The library
does not seem to be maintained any longer.

* Instead of Makefiles the build-tool waf is used. You can compile the project
  using:

> $ ./waf configure

> $ ./waf build

  The binary is then in ./build/quantumminigolf
  To build the virtual reality version use

> $ ./waf configure --vr

  The option "--debug" is also available to build with debug symbols. 

* Code for camera tracking of the golf club (WebcamTracker.cpp) was tweaked for
  our needs. To avoid unintended hits of the ball it is no longer possible to
  shoot the ball to the right, but only to the left towards the goal.


Credits
-------
- Friedemann Reinhard <friedemann.reinhard@ens.fr> developed the original
  Quantum Minigolf
- Matthias Hock built a very nice hardware setup with battery powered golf club
  and robust mechanical foot-button.
- Simon Friedmann <simonf256@googlemail.com> adapted the software for this fork.



Original README
===============

Quantum Minigolf - a computer game visualizing quantum mechanics
----------------------------------------------------------------

Copyright 2007, Friedemann Reinhard, friedemann.reinhard@ens.fr

Overview:
---------

Quantum minigolf is a minigolf simulation, in which the ball
behaves according to the laws of quantum mechanics. Such a quantum
ball can be at several places at once and diffract around obstacles. 

Quantum minigolf exists in two versions
	- the sofware-only version, which you have most probably in
	  front of you when you read this file
	- a virtual-reality version. Here the user plays with a real
	  club which is marked by an infrared LED and tracked by a
	  webcam. The ball is projected to the ground by a video
	  projector mounted on the ceiling. 
	  Basically, the software release contains all the neccessary 
	  code to build the virtual-reality version. However building
	  it will not (yet) be easy, since it is not documented yet :-(

You can find further information and the latest version of quantum
minigolf at
http://www.sourceforge.net/projects/quantumminigolf

Copyright Notice:
-----------------

Quantum minigolf uses several GPLed libraries. Their source code can
be found at the following locations

	* fftw3f  - the single precision (!) version of libfftw
	  http://www.fftw.org/

	* SDL
	  http://www.libsdl.org
	* SDL_ttf
	  http://www.libsdl.org/projects/SDL_ttf/

	* freetype
	  http://www.freetype.org/

	* Linux Libertine open fonts
	  http://sourceforge.net/projects/linuxlibertine/

Installation:
-------------

*Win32
	Binary packages: 
	Double-click on setup.msi or quantumminigolf_win32.exe

	Source packages:
	Open the supplied Visual C++ Project file. It works with Visual C++
	2005 Express Edition, which is free of charge. However, you might need
	to update the library paths according to your needs. 

*Linux / others
       Edit the Makefile according to your needs and compile


Creating Tracks:
----------------

Quantum minigolf allows you to easily create your own tracks. Just
open tracks/empty.bmp with your favorite graphics software and add
some obstacles. Purely white obstacles (i.e. obstacles with color
rgb(255,255,255)) are infinitely high. Gray obstacles have a finite
height proportional to their intensity. 

When you have finished a track, add its name in a new line of
tracks/tracks.cfg. 

If you want to use your new track also with the classical simulator,
create two hard- and softcore bitmaps using the Matlab/Octave file 
tracks/q2c.m and add their names to the tracks.cfg file. 
If you do not create the hard- and softcore bitmaps, the quantum
simulator will nevertheless be able to use your new track. 
 



