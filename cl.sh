#! /bin/bash
find . -type f -name *.fs  | xargs wc -l
echo commits: $(git log --pretty=oneline | wc -l)
