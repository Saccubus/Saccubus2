#! /bin/bash

DIRNAME=$(cd $(dirname $0);pwd)
PATH_TO_FRONT_FILE=$DIRNAME/__miscellaneous__/path_to_SaccubusFront.txt
TEST_FILE=SaccubusTest

function validateSaccubusFront() {
	if [ ! -f $1 ];then
		echo "config file not created."
		return 0
	fi
	p=$(cat $1)
	if [ ! -d $p ]; then
		echo "Dir: $p not found"
		return 0
	fi
	if [ ! -d $p/src/saccubus ]; then
		echo "Source Dir: $p/src/saccubus not found. Invalid repository."
		return 0
	fi
	return 1
}

while validateSaccubusFront $PATH_TO_FRONT_FILE ;do
	echo "Please input path to SaccubusFront"
	echo "ex) /dir/somewhere/SaccubusFront"
	read -er front_path
	if [ "$MSYSTEM" = "MINGW32" ] ; then
		echo $(cd $front_path; pwd -LPW) > $PATH_TO_FRONT_FILE
	else
		echo $(cd $front_path; pwd) > $PATH_TO_FRONT_FILE
	fi
done
front_path=`cat $PATH_TO_FRONT_FILE`/src
echo "SaccubusFront path detected: $front_path"

if [ -z "$PYTHON" ]; then
	PYTHON=python
fi

PYPATH="$(${PYTHON} -c 'import sys; import os;sys.stdout.write(os.pathsep.join(sys.path)+os.pathsep)')$front_path"
echo $PYPATH

function run() {
	PROG=$1/$TEST_FILE
	MODE=$2
	shift
	shift
	if [ -f $PROG ]; then
		echo "------------------------------------------------------------"
		echo "Running $MODE test"
		echo "------------------------------------------------------------"
		ECMD="$PROG $*"
		echo "%" $ECMD
		PYTHONPATH=$PYPATH $ECMD
	else
		echo "not found: \"$PROG\", skip."
		return 1
	fi
}

run "$DIRNAME/build" "normal" $*
run "$DIRNAME/build/debug" "debug" $*
run "$DIRNAME/build/release" "release" $*

