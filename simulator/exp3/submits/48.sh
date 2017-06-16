#!/bin/bash
#SBATCH --time=01:00:00
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --job-name=pp9
#SBATCH --mem=500
./simulate 9 1272292923
