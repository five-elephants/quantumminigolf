#!/usr/bin/env python
# encoding: utf-8

def options(opt):
	opt.load('compiler_cxx')

def configure(conf):
	conf.load('compiler_cxx')

	conf.env.LIBPATH_PORTVIDEO = '/home/simon/Projects/QM/PortVideoSDL/linux',
	conf.env.INCLUDES_PORTVIDEO = [
		'/home/simon/Projects/QM/PortVideoSDL/common',
		'/home/simon/Projects/QM/PortVideoSDL/ext/tinyxml',
	]
	conf.check_cxx(stlib='PortVideo', use='PORTVIDEO')
	conf.check_cfg(args='--cflags --libs', package='sdl SDL_ttf', uselib_store='SDL')
	conf.check_cxx(lib='fftw3f', uselib_store='FFTW3F')
	conf.check_cxx(lib='dc1394', uselib_store='DC1394')

def build(bld):
	src = """
	quantumminigolf.cpp
	Renderer.cpp
	ClassicSimulator.cpp
	QuantumSimulator.cpp
	SoftwareTracker.cpp
	Tracker.cpp
	TrackSelector.cpp
	WebcamTracker.cpp
	"""

	bld.program(
		source = src,
		target = 'quantumminigolf',
		includes = '',
		cxxflags = '-O0 -ggdb -malign-double -DLINUX',
		use = 'PORTVIDEO SDL FFTW3F DC1394',
	)
