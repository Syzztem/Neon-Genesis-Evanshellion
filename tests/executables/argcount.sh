#!/bin/bash

echo $#
for var in "$@"
do
    echo "[$var]"
done