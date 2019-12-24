#!/bin/bash -e
if [ -z "$INPUT" ]; then
  echo "run with env var INPUT targeted to input file"
  exit 1
fi

BUILD_ONLY=false

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
export OUTPUT_PATH=output.txt
./solution < ${INPUT}
cat ${INPUT}
echo "====8<===="
cat output.txt
