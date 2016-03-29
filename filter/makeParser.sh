#! /bin/sh
DIRNAME=$(cd $(dirname $0);pwd)

ANTLR=${DIRNAME}/external/antlr/antlr-3.4-complete.jar
PARSER_SRC=${DIRNAME}/src/nekomata/parser
PARSER_OUT=${PARSER_SRC}
TRANS_SRC=${DIRNAME}/src/saccubus/nicos
TRANS_OUT=${TRANS_SRC}

if [ "$MSYSTEM" = "MINGW32" ] ; then
	CURDIR=${DIRNAME} \
	PARSER_SRC=${PARSER_SRC} \
	PARSER_OUT=${PARSER_OUT} \
	TRANS_SRC=${TRANS_SRC} \
	TRANS_OUT=${TRANS_OUT} \
	ANTLR=${ANTLR} \
	cmd << EOF
set CLASSPATH=%CURDIR%\external\antlr\antlr-3.4-complete.jar;%CLASSPATH%
java -Dfile.encoding=UTF-8 -Duser.language=en -Duser.region=US org.antlr.Tool -fo %PARSER_OUT% -make %PARSER_SRC%\niwango.g
java -Dfile.encoding=UTF-8 -Duser.language=en -Duser.region=US org.antlr.Tool -fo %TRANS_OUT% -make %TRANS_SRC%\NicosMessage.g
EOF
else
	CLASSPATH=${ANTLR}:$CLASSPATH \
	java org.antlr.Tool -fo ${PARSER_OUT} -make \
		${PARSER_SRC}/niwango.g
	CLASSPATH=${ANTLR}:$CLASSPATH \
	java org.antlr.Tool -fo ${TRANS_OUT} -make \
		${TRANS_SRC}/NicosMessage.g
fi

find ${PARSER_OUT} -type f -name *.c | while read f; do
  mv $f ${PARSER_OUT}/$(basename $f .c).cpp
done

find ${TRANS_OUT} -type f -name *.c | while read f; do
  mv $f ${TRANS_OUT}/$(basename $f .c).cpp
done


