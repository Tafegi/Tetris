#!/bin/bash

echo "Running clang-tidy..."

BUILD_DIR="cmake-build-debug"

if [ ! -d "$BUILD_DIR" ]; then
  echo "Build directory not found!"
  exit 1
fi

run-clang-tidy -p $BUILD_DIR src

echo "clang-tidy finished."