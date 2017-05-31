#!/bin/bash

for i in $(eval echo {1..$1}) 
do
    sbatch $(eval echo submits/$i.sh)
done

