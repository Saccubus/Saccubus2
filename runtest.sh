#! /bin/sh

DIRNAME=$(cd $(dirname $0);pwd)
PATH_TO_FRONT_FILE=$DIRNAME/__miscellaneous__/path_to_SaccubusFront.txt

function validateSaccubusFront() {
	if [ ! -f $1 ];then
		echo "config file not created."
		return 0
	fi
	p=`cat $1`
	if [ ! -d $p ]; then
		echo "Dir: $p not found"
		return 0
	fi
	if [ ! -d $p/src/saccubus ]; then
		echo "Source Dir: $p/src/saccubus not found"
		return 0
	fi
	return 1
}

while validateSaccubusFront $PATH_TO_FRONT_FILE ;do
	echo "Please input path to SaccubusFront"
	echo "ex) in windows: c:/somewhere/SaccubusFront"
	echo "ex) in linux  : /dir/somewhere/SaccubusFront"
	read front_path
	echo $front_path > $PATH_TO_FRONT_FILE
done
front_path=`cat $PATH_TO_FRONT_FILE`/src
echo "SaccubusFront path: $front_path"

pypath="$(python -c 'import sys; import os;sys.stdout.write(os.pathsep.join(sys.path)+os.pathsep)')$front_path"
if [ -f $DIRNAME/build/debug/SaccubusTest ]; then
	echo "Running debug test"
	echo PYTHONPATH=$pypath build/debug/SaccubusTest $*
	PYTHONPATH=$pypath build/debug/SaccubusTest $*
fi
if [ -f $DIRNAME/build/release/SaccubusTest ]; then
	echo "Running release test"
	echo PYTHONPATH=$pypath build/release/SaccubusTest $*
	PYTHONPATH=$pypath build/release/SaccubusTest $*
fi
if [ -f $DIRNAME/build/SaccubusTest ]; then
	echo "Running test"
	echo PYTHONPATH=$pypath build/SaccubusTest $*
	PYTHONPATH=$pypath build/SaccubusTest $*
fi


