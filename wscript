#!/usr/bin/env python
# encoding: utf-8

def options(opt):
	opt.load('compiler_cxx')
	opt.add_option('--vr',
				action='store',
				default=False,
				help='Build virtual reality verion of the game')
	opt.add_option('--portvideo_src',
				action='store',
				default='../PortVideoSDL',
				help='Path to the PortVideo source tree')

def configure(conf):
	conf.load('compiler_cxx')

	conf.env.CXXFLAGS_FLAGS = [ '-DLINUX' ]
	if conf.options.vr:
		conf.env.CXXFLAGS_FLAGS.append('-DVR')
	conf.env.LIBPATH_PORTVIDEO = conf.options.portvideo_src + '/linux',
	conf.env.INCLUDES_PORTVIDEO = [
		conf.options.portvideo_src + '/common',
		conf.options.portvideo_src + '/ext/tinyxml',
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
	Highscore.cpp
	"""

	bld.program(
		source = src,
		target = 'quantumminigolf',
		includes = '',
		cxxflags = '-O2 -ggdb -malign-double',
		use = 'FLAGS PORTVIDEO SDL FFTW3F DC1394',
	)
