#!/usr/bin/env python
# encoding: utf-8

def options(opt):
	opt.load('compiler_c')
	opt.load('compiler_cxx')
	opt.load('boost')
	opt.add_option('--vr',
				action='store_true',
				default=False,
				help='Build virtual reality verion of the game')
	opt.add_option('--debug',
				action='store_true',
				default=False,
				help='Build with debug symbols.')

def configure(conf):
	conf.load('compiler_c')
	conf.load('compiler_cxx')
	conf.load('boost')
	#conf.check_boost(lib='property_tree')

	#conf.env.CXXFLAGS_FLAGS = [ '-std=c++11', '-DLINUX' ]
	conf.env.CXXFLAGS_FLAGS = [ '-DLINUX' ]
	if conf.options.vr:
		conf.env.CXXFLAGS_FLAGS.append('-DVR')
	if conf.options.debug:
		conf.env.CXXFLAGS_FLAGS.append('-ggdb')
	conf.env.INCLUDES_PORTVIDEO = [
		'portvideo/common',
		'portvideo/ext/tinyxml',
	]
	conf.check_cfg(args='--cflags --libs', package='sdl SDL_ttf', uselib_store='SDL')
	conf.check_cxx(lib='fftw3f', uselib_store='FFTW3F')
	conf.check_cxx(lib='dc1394', uselib_store='DC1394')

def build(bld):
	pv_src = bld.path.ant_glob([
		'portvideo/common/*.cpp',
		'portvideo/common/*.c',
		'portvideo/linux/*.cpp',
		'portvideo/ext/tinyxml/*.cpp',
	])

	bld.stlib(
		source = pv_src,
		target = 'portvideosdl',
		includes = [
			'portvideo/common',
			'portvideo/linux',
			'portvideo/ext/tinyxml',
			'portvideo/ext/ccvt',
		],
		use = 'FLAGS SDL DC1394'
	)

	bld.program(
		source = 'portvideo/common/PortVideoSDL.cpp',
		target = 'portvideo-demo',
		use = 'FLAGS SDL PORTVIDEO portvideosdl',
	)

	src = """
	quantumminigolf.cpp
	Renderer.cpp
	ClassicSimulator.cpp
	QuantumSimulator.cpp
	SoftwareTracker.cpp
	Tracker.cpp
	TrackSelector.cpp
	GameTrackSelector.cpp
	WebcamTracker.cpp
	Highscore.cpp
	Game.cpp
	"""

	bld.program(
		source = src,
		target = 'quantumminigolf',
		includes = '',
		cxxflags = '-O2 -malign-double',
		use = 'FLAGS SDL FFTW3F PORTVIDEO BOOST portvideosdl',
	)

