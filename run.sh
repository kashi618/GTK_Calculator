#!/bin/bash

run="${1:-n}"
source="${2:-main.c}"
build="gtk_calculator"

echo ""
echo "-------------------------"
echo "Compiling $source..."
echo "-------------------------"
echo ""

gcc -o "$build" "$source" $(pkg-config --cflags --libs gtk4) 2>&1
status=$?

if [ $status -eq 0 ]; then
    echo "Compilation successful !"
    
    echo ""
    echo "-------------------------"

     if [ "$run" == "y" ]; then
        chmod u+x "$build"
        ./"$build"
        exit 0
    fi

    read -p "Run? (y/n): " answer
    echo "-------------------------"
    echo ""
    
    if ["$answer" == "y" ]; then
        chmod u+x "$build"
        ./"$build"
    else
        exit 0
    fi
else
    echo ""
    echo "-----------------------"
    echo ""
fi
