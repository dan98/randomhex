#!/bin/bash
#SBATCH --time=01:00:00
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --job-name=pp13
#SBATCH --mem=500
./simulate 13 63652410
