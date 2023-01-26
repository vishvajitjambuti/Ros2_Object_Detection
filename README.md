# **Ros2_Object_Detection**

## System Requirements  

- Jetson Nano
- Jetpack 4.6 or higher

## Jetpack Setup

```python
free -m

```

If you don't have the right amount of swap, or want to change the value, use the following procedure to do so (from a terminal):

```python
# Disable ZRAM:
sudo systemctl disable nvzramconfig

# Create 4GB swap file
sudo fallocate -l 4G /mnt/4GB.swap
sudo chmod 600 /mnt/4GB.swap
sudo mkswap /mnt/4GB.swap

# Append the following line to /etc/fstab
sudo su
echo "/mnt/4GB.swap swap swap defaults 0 0" >> /etc/fstab
exit
```

## REBOOT

## Install Docker From Docker Hub

- Docker is Already available on docker hub with will satisfy following requirements for the system
- Link is given bellow

```python
docker pull karandhage/thesis_version1
```

- Docker run [guide](/src/Docker.md) 


### Docker Features  Availability

Docker comes with following packages preinstalled 

- ROS2 -foxy 
- pytorch 
- torch Vision
- tensor RT
- [more details](/src/Docker.md)

### Please Check Docker Installation Guide  [**Click Here**](/src/Docker.md)

## Build the ROS2 Packages

Build the all the ros2 packages from src folder 

- Navigate  to  Ros2_Object_Detection(cd Ros2_Object_Detection)

- And Run following command 

```python 
colcon build or ./run.sh 

```

- after this source the  setup.bash 


```python 
source install/setup.bash
```

### Available packages and Usage

- please check available package in repo and details before building the packages.

#### my_camera_pkg

- For more details [**click here**](/src/camera.md)

#### my_undistorted_img_pkg

- For more details [**click here**](/src/undistorted.md)

#### my_tensorRt_pkg

- For mode details [**click here**](/src/tensorRt.md)

#### my_yolov5_pkg

- For mode details [**click here**](/src/yolov5.md)

#### my_yolo_launch

-  For mode details [**click here**](/src/launch.md)

