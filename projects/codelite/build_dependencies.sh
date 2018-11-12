#!/bin/bash

base_dir=$(dirname "${BASH_SOURCE[0]}")
cd "$base_dir"
cd "../../"
project_dir="$PWD"

# build ffts
cd "external/ffts"
mkdir -p "build"
cd "build"
cmake ..
make

# create output folders
cd "$project_dir"
output_dir="$project_dir/projects/codelite/local"
mkdir -p "$output_dir"
mkdir -p "$output_dir/include"
mkdir -p "$output_dir/lib"

# copy ffts to output folder
rm -rf "$output_dir/include/ffts"
cp -rf "$project_dir/external/ffts/include" "$output_dir/include/ffts"
cp -f "$project_dir/external/ffts/build/libffts.a" "$output_dir/lib/libffts.a"
