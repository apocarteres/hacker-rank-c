#!/bin/bash -e
BUILD_ONLY=false
ARGS="6 1 2 5 3 4 6"

if [[ "$1" == "build-only" ]]; then
  BUILD_ONLY=true
  echo "build only. no editing"
fi

if [[ "$BUILD_ONLY" == "false" ]]; then
  find . -name "*.[ch]" | xargs clang-format -i
  vim solution.c
fi

rm -f solution
SOURCES=`find . -name "*.c"`
gcc -std=c99 ${SOURCES} -o solution
./solution ${ARGS}
echo "press CTRL+C to continue..."
read
