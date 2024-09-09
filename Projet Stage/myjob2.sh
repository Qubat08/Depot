#!/bin/bash
#SBATCH --job-name=hvd
#SBATCH --output=myjob_%j.out
#SBATCH --error=myjob_%j.err
#SBATCH --nodes=1
#SBATCH --ntasks=2
#SBATCH --gres=gpu:2
#SBATCH --reservation=CHPS

# Module
module purge

module load 2018/gcc/9.1.0
module load cuda/11.8
module load 2018/python/3.6.9_gnu-deeplearning
module load 2021/openmpi/4.0.5.1-gnu
module load cudnn

# Env
source /home/qbatiste/stage/stage/bin/activate

#Run
# Choose the run command

# Cifar-10
#horovodrun -np 2 python3 projet2.py --data=cifar10_data --num_classes=10 --module_name=cifar10_model --function_name=createModel --gpu=2 --epoch=100 --batch=32

#Cifar-100
#horovodrun -np 2 python3 projet2.py --data=cifar100_data --num_classes=100 --module_name=cifar100_model --function_name=createModel --gpu=2 --epoch=100 --batch=32

# Imagenette
#horovodrun -np 2 python3 projet2.py --data=imagenette2 --num_classes=10 --module_name=convnextModel --function_name=createModel --gpu=2 --epoch=100 --batch=32
