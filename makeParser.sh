#! /bin/sh
DIRNAME=$(cd $(dirname $0);pwd)

ANTLR=${DIRNAME}/external/antlr/antlr-3.4-complete.jar
ANTLR_SRC=${DIRNAME}/src/nekomata/parser
ANTLR_OUT=${ANTLR_SRC}

if [ "$MSYSTEM" = "MINGW32" ] ; then
	CURDIR=${DIRNAME} \
	ANTLR_SRC=${ANTLR_SRC} \
	ANTLR_OUT=${ANTLR_OUT} \
	ANTLR=${ANTLR} \
	cmd << EOF
set CLASSPATH=%CURDIR%\external\antlr\antlr-3.4-complete.jar;%CLASSPATH%
java -Dfile.encoding=UTF-8 -Duser.language=en -Duser.region=US org.antlr.Tool -fo %ANTLR_OUT% -make %ANTLR_SRC%\niwango.g
EOF
else
	CLASSPATH=${ANTLR}:$CLASSPATH \
	java org.antlr.Tool -fo ${ANTLR_OUT} -make \
		${ANTLR_SRC}/niwango.g
fi

find ${ANTLR_OUT} -type f -name *.c | while read f; do
  mv $f ${ANTLR_OUT}/$(basename $f .c).cpp
done


