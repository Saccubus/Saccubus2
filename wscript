# -*- coding: utf-8 -*-
import sys
import os

APPNAME = 'Nekomata'
VERSION = '1.0.0'

srcdir = '.'
blddir = 'build'

def enum(dirname, exclude=[]):
	dirname = os.path.join(*(dirname.split('/')))
	COMPILED_EXT=['.cpp','.c']
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
			if ext in COMPILED_EXT:
				f.append(os.path.relpath(fabs))
	return f

NEKOMATA_DIR=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'src', 'nekomata')
NEKOMATA_SRC=enum('src/nekomata')
NEKOMATA_INC=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'include')

CLI_DIR=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'src', 'cli')
CLI_SRC=enum('src/cli')

def options(opt):
	opt.add_option('--coverage', action='store_true', default=False, help='Enabling coverage measuring.')
	opt.load('compiler_c compiler_cxx')

def configure(conf):
	conf.setenv('release')
	conf.env.append_value('CXXFLAGS', ['-O3', '-Wall', '-std=c++0x', '-std=c++11', '-D__GXX_EXPERIMENTAL_CXX0X__=1'])
	configureLibrary(conf)
	
	conf.setenv('debug')
	denv = conf.env;
	conf.env.append_value('CXXFLAGS', ['-ggdb','-O0', '-Wall', '-std=c++0x', '-std=c++11', '-D__GXX_EXPERIMENTAL_CXX0X__=1','-DDEBUG'])
	configureLibrary(conf)
	if conf.options.coverage:
		conf.setenv('coverage', denv)
		conf.env.append_value('LINKFLAGS', '-fprofile-arcs')
		conf.env.append_value('CXXFLAGS', ['-fprofile-arcs','-ftest-coverage'])

def configureLibrary(conf):
	conf.load('compiler_c compiler_cxx')
	conf.check_cfg(package='icu-uc icu-i18n', uselib_store='ICU', mandatory=True, args='--cflags --libs')
	conf.check(features='cxx cxxprogram', lib=['gtest', 'gtest_main', 'pthread'], cflags=['-Wall'], uselib_store='GTEST')
	conf.check(features='cxx cxxprogram', lib=['antlr3c'], cflags=['-Wall'], uselib_store='ANTLR')

LIB_SRC=\
		NEKOMATA_SRC
PRG_SRC=\
		NEKOMATA_SRC+\
		CLI_SRC

def build(bld):
	if not bld.variant:
		bld.fatal('call "waf build_debug" or "waf build_release", and try "waf --help"')
	srcdir=repr(bld.path)
	bld(
		features = 'cxx cxxprogram',
		source = PRG_SRC,
		target = 'nekomata',
		use=['PPROF', 'ICU','ANTLR'],
		includes=[NEKOMATA_INC])

	bld(
		features = 'cxx cxxstlib',
		source = NEKOMATA_SRC,
		target = 'nekomata',
		use=['PPROF', 'ICU','ANTLR'],
		includes=[NEKOMATA_INC])

		#test_env = None
	#if "coverage" in bld.all_envs:
	#	test_env = bld.all_envs["coverage"]
	#else:
	#	test_env = bld.env

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

