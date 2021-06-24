#!/bin/bash
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

cd $SCRIPT_DIR
cd ./Premake

cp premake5macos ../premake5

cd ..

sudo chmod +x premake5
./premake5 xcode4

rm -f premake5



