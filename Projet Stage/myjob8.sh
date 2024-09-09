#!/bin/bash
#SBATCH --job-name=my_horovod_job
#SBATCH --output=myjob.out
#SBATCH --error=myjob.err
#SBATCH --nodes=2   # Total number of nodes
#SBATCH --gres=gpu:4 # Number of GPUs per node
#SBATCH --reservation=CHPS
#SBATCH --ntasks-per-node=4
#SBATCH --partition=instant

# Charger les modules nécessaires
module purge

module load 2018/gcc/9.1.0
module load cuda/11.8
module load 2018/python/3.6.9_gnu-deeplearning
module load 2021/openmpi/4.0.5.1-gnu
module load cudnn

NODES=$(scontrol show hostnames $SLURM_NODELIST)

# Fonction pour obtenir l'adresse IP principale d'un nœud
get_ip() {
  getent hosts $1 | awk '{ print $1; exit }'
}

# Obtenir le nombre total de GPUs et le nombre de nœuds

TOTAL_GPUS=$SLURM_NTASKS
TOTAL_NODES=$SLURM_NNODES


# Calculer la répartition des GPUs par nœud (valeur entière)
GPUS_PER_NODE=$((TOTAL_GPUS / TOTAL_NODES))

# Créer une liste avec les adresses IP et les GPUs par nœud
NODE_IP_GPU_LIST=""
for NODE in $NODES; do
 
  NODE_IP_GPU_LIST+="$NODE:$GPUS_PER_NODE,"
done

# Supprimer la dernière virgule
NODE_IP_GPU_LIST=${NODE_IP_GPU_LIST%,}

source /home/qbatiste/stage/stage/bin/activate

# export CUDA_VISIBLE_DEVICES=0,1,2,3

mpirun -np $TOTAL_GPUS -H $NODE_IP_GPU_LIST -bind-to none -map-by slot \
-x NCCL_DEBUG=INFO -x LD_LIBRARY_PATH -x PATH \
-mca pml ob1 -mca btl ^openib \
python3 projet2.py --data=cifar10_data --num_classes=10 --module_name=model3 --function_name=createModel --gpu=8 --epoch=14 --batch=8

# horovodrun -np $TOTAL_GPUS python3 projet2.py --data=cifar100_data --num_classes=100 --module_name=model3 --function_name=createModel --gpu=8 --epoch=100 --batch=8

# NODES=$(scontrol show hostname | tr '\n' ',' | sed 's/,$//')
# GPU_PER_NODE=4
# HOSTS=$(echo $NODES | sed "s/,/:$GPU_PER_NODE,/g"):$GPU_PER_NODE

# horovodrun -np 8 -H $HOSTS python3 projet2.py --data=imagenette2 --num_classes=10 --module_name=convnextModel --function_name=createModel --gpu=8 --epoch=20 --batch=8


# mpirun -np $TOTAL_GPUS -H $NODE_IP_GPU_LIST -bind-to none -map-by slot \
# -x NCCL_DEBUG=INFO -x LD_LIBRARY_PATH -x PATH \
# -x CUDA_VISIBLE_DEVICES -x HOROVOD_CACHE_CAPACITY \
# -mca pml ob1 -mca btl ^openib \
# python3 projet2.py --data=imagenette2 --num_classes=10 --module_name=convnextModel --function_name=createModel --gpu=8 --epoch=32 --batch=2

