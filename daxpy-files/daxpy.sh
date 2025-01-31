#!/bin/bash
#SBATCH --job-name=daxpy
#SBATCH --account=COMS033964
#SBATCH --nodes=1
#SBATCH --time=00:10:00
#SBATCH --exclusive
#SBATCH --partition=teach_cpu



./daxpy