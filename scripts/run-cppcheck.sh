#!/bin/bash

echo "Running cppcheck..."

cppcheck --enable=all --inconclusive --std=c++20 \
         --suppress=missingIncludeSystem \
         src

echo "cppcheck finished."