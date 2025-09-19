#!/bin/bash

rightTriangle(){
    echo "Right Triangle Pattern:"
    local height=$1
    for ((i=1; i<=height; i++)); do
        for ((j=1; j<=i; j++)); do
        echo -n "* "
        done
        echo ""
    done
}

primadTriangle(){
    echo "Pyramid Triangle Pattern:"
    local height=$1
    for ((i=1; i<=height; i++)); do
        for ((j=i; j<height; j++)); do
        echo -n "  "
        done
        for ((k=1; k<=(2*i-1); k++)); do
        echo -n "* "
        done
        echo ""
    done
}

Dimond(){
    echo "Diamond Pattern:"
    local height=$1
    for ((i=1; i<=height; i++)); do
        for ((j=i; j<height; j++)); do
        echo -n "  "
        done
        for ((k=1; k<=(2*i-1); k++)); do
        echo -n "* "
        done
        echo ""
    done
    for ((i=height-1; i>=1; i--)); do
        for ((j=height; j>i; j--)); do
        echo -n "  "
        done
        for ((k=1; k<=(2*i-1); k++)); do
        echo -n "* "
        done
        echo ""
    done
}

read -p "Enter the height of the triangle: " height
rightTriangle $height
echo ""
primadTriangle $height
echo ""
Dimond $height