#! /bin/sh

DIRNAME=$(cd $(dirname $0);pwd)
find $DIRNAME/src -type f -name *.py | xargs wc -l
echo. GIT logs: `git --git-dir=${DIRNAME}/.git log --pretty=oneline | wc -l`
