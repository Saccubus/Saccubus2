#! python
# -*- coding: utf-8 -*-

"""
 Saccubus
 Copyright (C) 2012-2013 psi
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
"""
import sys
import os
sys.path.append('external/WafHelper')
import Util

APPNAME = 'Saccubus'
VERSION = '2.0.0'

srcdir="."
bindir="build"

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
SACC_SRC=Util.enum('src/saccubus')

CLI_DIR=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'src','entry_points','cli')
CLI_SRC=Util.enum('src/entry_points/cli')

TEST_DIR=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'test')
TEST_SRC=Util.enum('test')

FFMPEG_DIR=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'src','entry_points','ffmpeg')
FFMPEG_SRC=Util.enum('src/entry_points/ffmpeg')

NEKOMATA_DIR=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'src', 'nekomata')
NEKOMATA_SRC=Util.enum('src/nekomata')
NEKOMATA_INC=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'include')

NEKOCLI_DIR=os.path.join(os.path.abspath(os.path.dirname(srcdir)), 'src', 'cli')
NEKOCLI_SRC=Util.enum('src/cli')

def options(opt):
	opt.add_option('--coverage', action='store_true', default=False, help='Enabling coverage measuring.')
	opt.add_option('--debug', action='store_true', default=False, help='debug build')
	opt.load('compiler_c compiler_cxx')
	opt.load('boost')

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
	conf.check_cfg(package='icu-uc icu-i18n', uselib_store='ICU', mandatory=True, args='--cflags --libs')
	conf.check_cfg(package='cairo', uselib_store='CAIRO', mandatory=True, args='--cflags --libs')
	conf.check_cfg(package='freetype2', uselib_store='FREETYPE2', mandatory=True, args='--cflags --libs')
	conf.check_cfg(package='fontconfig', uselib_store='FONTCONFIG', mandatory=True, args='--cflags --libs')
	conf.check_cfg(package='sdl2', uselib_store='SDL2', mandatory=True, args='--cflags --libs')
	checkPython(conf)
	conf.check(features='cxx cxxprogram', lib=['gtest', 'gtest_main', 'pthread'], cflags=['-Wall'], uselib_store='GTEST', mandatory=False)
	conf.check(features='cxx cxxprogram', lib=['antlr3c'], cflags=['-Wall'], uselib_store='ANTLR')

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
	bld(
		is_install=True,
		features = 'cxx cxxstlib',
		source = NEKOMATA_SRC,
		target = 'nekomata',
		use=['PPROF', 'ICU','ANTLR'],
		includes=[NEKOMATA_INC]
		)
	bld(
		features = 'cxx cxxprogram',
		source = NEKOMATA_SRC+NEKOCLI_SRC,
		target = 'Nekomata',
		use=['PPROF', 'ICU','ANTLR'],
		includes=[NEKOMATA_INC]
		)
	bld(
		features = "subst",
		source= "pkgconfig/nekomata.pc.in",
		target= "nekomata.pc",
		install_path='${PREFIX}/lib/pkgconfig/',
		PREFIX = bld.env['PREFIX'],
		VER=VERSION
		)
	bld.install_files("${PREFIX}", Util.enum('include',[],['.h']), relative_trick=True)
	bld.install_files("${PREFIX}/lib", 'libnekomata.a')
	#test_env = None
	#if "coverage" in bld.all_envs:
	#	test_env = bld.all_envs["coverage"]
	#else:
	#	test_env = bld.env


def shutdown(ctx):
	pass
