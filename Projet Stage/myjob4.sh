#!/bin/bash
#SBATCH --job-name=hvd
#SBATCH --output=myjob.out
#SBATCH --error=myjob.err
#SBATCH --nodes=1
#SBATCH --ntasks=4
#SBATCH --gres=gpu:4
#SBATCH --reservation=CHPS

# Module
module purge

module load 2018/gcc/9.1.0
module load cuda/11.8
module load 2018/python/3.6.9_gnu-deeplearning
module load 2021/openmpi/4.0.5.1-gnu
module load cudnn

# Env python with horovod
source /home/qbatiste/stage/stage/bin/activate


#Choose and Run
#Cifar-10
#horovodrun -np 4 python3 projet2.py --data=cifar10_data --num_classes=10 --module_name=cifar10_model --function_name=createModel --gpu=4 --epoch=100 --batch=16

#Cifar-100
#horovodrun -np 4 python3 projet2.py --data=cifar100_data --num_classes=100 --module_name=cifar100_model --function_name=createModel --gpu=4 --epoch=100 --batch=16

#Imagenette
#horovodrun -np 4 python3 projet2.py --data=imagenette2 --num_classes=10 --module_name=convnextModel --function_name=createModel --gpu=4 --epoch=100 --batch=16
