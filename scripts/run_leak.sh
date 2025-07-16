#!/bin/bash

# To better view enable Debug mode in make file

# Navigate to project root (../ from scripts/)
cd "$(dirname "$0")/.."

CUB3D_EXEC="./debug_bin"
CUB3D_VAL="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --quiet --track-fds=all --suppressions=suppression.sup"

RED="\e[31m"
RESET="\e[0m"
GREEN="\e[32m"


# Check if cub3D exists
if [ ! -f "$CUB3D_EXEC" ]; then
    echo "cub3D not found, running make..."
    make
    if [ ! -f "$CUB3D_EXEC" ]; then
        echo "Make failed or cub3D still not found."
        exit 1
    fi
fi

echo -e "
  _____                    _                                
 / ____|                  | |                               
| |  __   ___    ___    __| |  _ __ ___    __ _  _ __   ___ 
| | |_ | / _ \  / _ \  / _\` | | '_ \` _ \  / _\` || '_ \ / __|
| |__| || (_) || (_) || (_| | | | | | | || (_| || |_) |\__ \\
 \_____| \___/  \___/  \__,_| |_| |_| |_| \__,_|| .__/ |___/
                                                | |         
                                                |_|         
"

# Run for all good maps
echo -e "${GREEN}Running Valgrind on GOOD maps:${RESET}"
for map in maps/good/*.cub; do
    if [ -f "$map" ]; then
        printf "$RED\nRunning:\n$map\n$CUB3D_VAL $CUB3D_EXEC  $RESET\n"
        $CUB3D_VAL $CUB3D_EXEC "$map"
    fi
done

echo -e "
  _                 _                                
 | |               | |                               
 | |__    __ _   __| |  _ __ ___    __ _  _ __   ___ 
 | '_ \  / _\` | / _\` | | '_ \` _ \  / _\` || '_ \ / __|
 | |_) || (_| || (_| | | | | | | || (_| || |_) |\__ \\
 |_.__/  \__,_| \__,_| |_| |_| |_| \__,_|| .__/ |___/
                                         | |         
                                         |_|         
"

# Run for all bad maps
echo -e "${RED}Running Valgrind on BAD maps:${RESET}"
for map in maps/bad/*.cub; do
    if [ -f "$map" ]; then
        printf "$RED\nRunning:\n$map\n$CUB3D_VAL $CUB3D_EXEC  $RESET\n"
        $CUB3D_VAL $CUB3D_EXEC "$map"
    fi
done
