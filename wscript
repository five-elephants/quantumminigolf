#!/usr/bin/env python
# encoding: utf-8

def options(opt):
	opt.load('compiler_c')
	opt.load('compiler_cxx')
	opt.add_option('--vr',
				action='store_true',
				default=False,
				help='Build virtual reality verion of the game')
	opt.add_option('--portvideo_src',
				action='store',
				default='../PortVideoSDL',
				help='Path to the PortVideo source tree')
	opt.add_option('--debug',
				action='store_true',
				default=False,
				help='Build with debug symbols.')

def configure(conf):
	conf.load('compiler_c')
	conf.load('compiler_cxx')

	conf.env.CXXFLAGS_FLAGS = [ '-DLINUX' ]
	if conf.options.vr:
		conf.env.CXXFLAGS_FLAGS.append('-DVR')
	if conf.options.debug:
		conf.env.CXXFLAGS_FLAGS.append('-ggdb')
	#conf.env.LIBPATH_PORTVIDEO = conf.options.portvideo_src + '/linux',
	conf.env.INCLUDES_PORTVIDEO = [
		conf.options.portvideo_src + '/common',
		conf.options.portvideo_src + '/ext/tinyxml',
	]
	#conf.check_cxx(stlib='PortVideo', use='PORTVIDEO')
	conf.check_cfg(args='--cflags --libs', package='sdl SDL_ttf', uselib_store='SDL')
	conf.check_cxx(lib='fftw3f', uselib_store='FFTW3F')
	conf.check_cxx(lib='dc1394', uselib_store='DC1394')

def build(bld):
	#pv_src = ' '.join([
		#bld.options.portvideo_src + '/common/*.c',
		#bld.options.portvideo_src + '/common/*.cpp',
		#bld.options.portvideo_src + '/linux/*.cpp',
	#])
	pv_src = bld.path.ant_glob(bld.options.portvideo_src + '/common/*.cpp')
	print "pv_src = ", pv_src

	bld.stlib(
		source = pv_src,
		target = 'portvideosdl',
		includes = [
			bld.options.portvideo_src + '/common',
			bld.options.portvideo_src + '/linux',
			bld.options.portvideo_src + '/ext/tinyxml',
			bld.options.portvideo_src + '/ext/ccvt',
		],
		use = 'FLAGS SDL DC1394'
	)

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
		cxxflags = '-O2 -malign-double',
		use = 'FLAGS SDL FFTW3F PORTVIDEO portvideosdl',
	)

