#!/bin/bash
#SBATCH --time=10:00:00
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --job-name=pp18
#SBATCH --mem=500
./simulate 18 1672089902
