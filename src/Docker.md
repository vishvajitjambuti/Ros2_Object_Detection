# Docker installation Guide

This docker installation guide will only work  on the jetson nano with jetpacke 4.5 or higher

## available docker on docker hub

- Below given docker is available on docker hub
- You can directly pull and start using as shown  in section [**Docker run guide**](##Docker-run-guide )

```python
docker pull karandhage/thesis_version1
```

## Build the docker locally

After running above docker  if it can not run pytorch and access to Cuda you need to build the docker as given bellow

- Download following git repo from git hum 

```python
git pull https://github.com/dusty-nv/jetson-containers.git
``` 

- To enable access to the CUDA compiler (nvcc) during docker build operations, add "default-runtime": "nvidia" to your /etc/docker/daemon.json configuration file before attempting to build the containers:

```python
{
    "runtimes": {
        "nvidia": {
            "path": "nvidia-container-runtime",
            "runtimeArgs": []
        }
    },

    "default-runtime": "nvidia"
}

```

- You will then want to restart the Docker service or reboot your system before proceeding.
- After this need start building jetson container 

```python
# navigate to repo 

cd jetson-containers

# build the docker image with following command
 
./scripts/docker_build_ros.sh --distro foxy --with-pytorch

```

- this will take 3 to 4 hours 


## Docker run guide

- To run the docker you need to create ros2 workspace in home directory of jetson nano

```python
mkdir ros2_ws
```

- create .sh file (example: docker_run.sh)
- Add following containt in it 

```python

sudo xhost +si:localuser:root
# enable SSH X11 forwarding inside container (https://stackoverflow.com/q/48235040)
XAUTH=/tmp/.docker.xauth
xauth nlist $DISPLAY | sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -
chmod 777 $XAUTH


sudo docker run --runtime nvidia -it --rm --network host --volume ~/ros2_ws:/home --device /dev/video0 karandhage/thesis_version1:latest

```

- Create docker file executable 

```python
chmod +x docker_run.sh 
```

- run the docker 

```python
./docker_run.sh
```


## Detailed packages  available  

Docker has preinstalled libs list is giver bellow:

- this list satisfy requirements of  yolov5 pytorch object detection repo maintained by [ultralytics](https://github.com/ultralytics/yolov5.git)  

```python
# YOLOv5 requirements


# Base ----------------------------------------
matplotlib>=3.2.2
numpy>=1.18.5
opencv-python>=4.1.1
Pillow>=7.1.2
PyYAML>=5.3.1
requests>=2.23.0
scipy>=1.4.1
torch>=1.7.0
torchvision>=0.8.1
tqdm>=4.64.0


# Logging -------------------------------------
tensorboard>=2.4.1
# wandb
# clearml

# Plotting ------------------------------------
pandas>=1.1.4
seaborn>=0.11.0


ipython  # interactive notebook
psutil  # system utilization
thop>=0.1.1  # FLOPs computation

```

- Please Do not install anything new
