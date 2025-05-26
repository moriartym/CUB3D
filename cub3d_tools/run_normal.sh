#!/bin/bash

# Check if a map file name was provided
if [ -z "$1" ]; then
  echo "Usage: $0 <map_filename>"
  exit 1
fi

MAP_FILE="$1"

# Go to cub3d_mandatory, rebuild, run, and return
cd cub3d_mandatory || exit
make re
./cub3D "../map/$MAP_FILE"
cd ..
