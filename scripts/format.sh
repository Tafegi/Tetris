#!/bin/bash

echo "Running clang-format..."

find src -name "*.cpp" -o -name "*.h" | xargs clang-format -i

echo "Done formatting."