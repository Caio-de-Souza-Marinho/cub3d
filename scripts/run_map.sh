#!/bin/bash

# To better view enable Debug mode in make file

# Navigate to project root (../ from scripts/)
cd "$(dirname "$0")/.."

CUB3D_EXEC="./cub3D"

# Check if cub3D exists
if [ ! -f "$CUB3D_EXEC" ]; then
    echo "cub3D not found, running make..."
    make
    if [ ! -f "$CUB3D_EXEC" ]; then
        echo "Make failed or cub3D still not found."
        exit 1
    fi
fi

# Run for all good and bad maps
for map in maps/good/*.cub maps/bad/*.cub; do
    if [ -f "$map" ]; then
        printf "\nRunning: $CUB3D_EXEC $map\n"
        $CUB3D_EXEC "$map"
    fi
done
