#!/bin/bash

read -p "Enter Password: " pass

org="mlp0zaq1"

if [[ "$pass" == "$org" ]]; then
  echo "password is correct:"

else
echo "password is incorrect"
fi 
