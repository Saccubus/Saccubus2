# -*- coding: utf-8 -*-
import sys
import os

APPNAME = 'Saccubus'
VERSION = '2.0.0'

srcdir = '.'
blddir = 'build'

def enum(dirname, exclude=[], exts=['.cpp','.c']):
	dirname = os.path.join(*(dirname.split('/')))
	f = []
	for root,dirs,files in os.walk(dirname):
		matched = False
		for e in exclude:
			if root.startswith(e):
				matched = True
				break
		if matched:
			continue
		for fitem in files:
			fabs = os.path.join(root, fitem)
			_, ext = os.path.splitext(fabs)
			if ext in exts:
				f.append(os.path.relpath(fabs))
	return f

def checkPython(conf):
	# Pythonを探す
	python_bin = conf.find_program('python')
	# Linuxなどではpkg-configを使って設定する
	if conf.check_cfg(package='python3', uselib_store='PYTHON', mandatory=False, args='--cflags --libs'):
		return
	#XXX: Windows版Pythonの変なディレクトリ構成にあわせる
	if sys.platform == 'win32' or sys.platform == 'win64':
		# Python.exeのパスから、includeとlibをチェック
		dname = os.path.dirname(python_bin)
		dinc = os.path.abspath(os.path.join(dname,'include'))
		dlib = os.path.abspath(os.path.join(dname,'libs'))
		# フォルダのチェック
		if not os.path.isdir(dinc):
			conf.fatal('could not find python include directory!: {}'.format(dinc))
		elif not os.path.isdir(dlib):
			conf.fatal('could not find python library directory!: {}'.format(dlib))
		conf.check(features='cxx cxxprogram', lib=['python33'], cflags=['-I'+dinc], linkflags=["-L"+dlib], uselib_store='PYTHON', mandatory=True)
		conf.env.append_value('INCLUDES_PYTHON', [dinc])
		conf.env.append_value('LIBPATH_PYTHON', [dlib])
	else:
		conf.fatal('could not find python!')

SACC_DIR=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'src', 'saccubus')
SACC_SRC=enum('src/saccubus')

CLI_DIR=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'src','entry_points','cli')
CLI_SRC=enum('src/entry_points/cli')

TEST_DIR=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'test')
TEST_SRC=enum('test')

FFMPEG_DIR=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'src','entry_points','ffmpeg')
FFMPEG_SRC=enum('src/entry_points/ffmpeg')

def options(opt):
	opt.add_option('--coverage', action='store_true', default=False, help='Enabling coverage measuring.')
	opt.add_option('--debug', action='store_true', default=False, help='debug build')
	opt.load('compiler_c compiler_cxx')

def configure(conf):
	# release
	conf.setenv('release')
	conf.env.append_value('CXXFLAGS', ['-O3', '-Wall', '-std=gnu++11', '-D__GXX_EXPERIMENTAL_CXX0X__=1'])
	conf.env.append_value('LINKFLAGS', ['-fvisibility=hidden'])
	configureLibrary(conf)
	# debug
	conf.setenv('debug')
	denv = conf.env;
	conf.env.append_value('CXXFLAGS', ['-ggdb','-O0', '-Wall', '-std=gnu++11', '-D__GXX_EXPERIMENTAL_CXX0X__=1','-DDEBUG'])
	conf.env.append_value('LINKFLAGS', ['-fvisibility=hidden'])
	configureLibrary(conf)
	if conf.options.coverage:
		conf.setenv('coverage', denv)
		conf.env.append_value('LINKFLAGS', '-fprofile-arcs')
		conf.env.append_value('CXXFLAGS', ['-fprofile-arcs','-ftest-coverage'])

def configureLibrary(conf):
	conf.load('compiler_c compiler_cxx')
	conf.check_cfg(package='libxml-2.0', uselib_store='LIBXML2', mandatory=True, args='--cflags --libs')
	conf.check_cfg(package='cairo', uselib_store='CAIRO', mandatory=True, args='--cflags --libs')
	conf.check_cfg(package='freetype2', uselib_store='FREETYPE2', mandatory=True, args='--cflags --libs')
	conf.check_cfg(package='fontconfig', uselib_store='FONTCONFIG', mandatory=True, args='--cflags --libs')
	conf.check_cfg(package='sdl2', uselib_store='SDL2', mandatory=True, args='--cflags --libs')
	checkPython(conf)

	conf.check_cfg(package='nekomata', uselib_store='NEKOMATA', mandatory=True, args='--cflags --libs')
	conf.check(features='cxx cxxprogram', lib=['gtest', 'gtest_main', 'pthread'], cflags=['-Wall'], uselib_store='GTEST', mandatory=False)

def build(bld):
	if not bld.variant:
		bld.set_env(bld.all_envs['debug' if (bld.options.debug) else 'release'])
	bld(
		features = 'cxx cprogram',
		source = SACC_SRC+CLI_SRC,
		target = 'SaccubusCLI',
		use=['PPROF', 'LIBXML2', 'CAIRO', 'FREETYPE2', 'FONTCONFIG', 'SDL2', 'PYTHON', 'NEKOMATA']
		)
	bld(
		features = 'cxx cxxshlib',
		source = SACC_SRC+FFMPEG_SRC,
		target = 'Saccubus',
		use=['PPROF', 'LIBXML2', 'CAIRO', 'FREETYPE2', 'FONTCONFIG', 'SDL2', 'PYTHON', 'NEKOMATA'],
		defs = '__miscellaneous__/adapter.def'
		)
	bld(
		features = 'cxx cprogram',
		source = SACC_SRC+TEST_SRC,
		target = 'SaccubusTest',
		env = ( bld.all_envs["coverage"] if ("coverage" in bld.all_envs) else bld.env ),
		use=['PPROF', 'LIBXML2', 'CAIRO', 'FREETYPE2', 'FONTCONFIG', 'SDL2', 'PYTHON', 'NEKOMATA', 'GTEST']
		)

# from http://docs.waf.googlecode.com/git/book_16/single.html#_custom_build_outputs
from waflib.Build import BuildContext, CleanContext, InstallContext, UninstallContext
for x in 'debug release'.split():
	for y in (BuildContext, CleanContext, InstallContext, UninstallContext):
		name = y.__name__.replace('Context','').lower()
		class tmp(y):
			cmd = name + '_' + x
			variant = x

def shutdown(ctx):
	pass

