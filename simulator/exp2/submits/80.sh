#!/bin/bash
#SBATCH --time=10:00:00
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --job-name=pp12
#SBATCH --mem=500
./simulate 12 1269263927
