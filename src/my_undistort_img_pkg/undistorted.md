# my_undistort_img_pkg 

this packed is used to get image from the rstp camera  undistorted the image and publish it to the topics. 

## Before You Build This Package Please change the following line in 

- Please go to  location : /my_undistort_img_pkg/src/Source/

- open: camera.cpp
- change the distortionMatrix.yml file path  

-- line nr 109

```python 
 readIntrinsicExtrinsic("{your path}/src/my_undistort_img_pkg/src/Source/distortionMatrix.yml");

```


## Node:  distorted_img

- This node is useful to publish  raw RSTP cam image 
- parameters 

``` python 
camera_id # rstp address
```

- topic publish 

```python
/distorted/image_raw
```

## Node: undistort_img1

- This Node is useful to publish undistorted image 

- topic publish 

```python
/undistorded/image_raw_1
```

## Node: undistort_img2

 This Node is useful to publish undistorted image 

- topic publish 

```python
/undistorded/image_raw_2
```

## Node: undistort_img3

 This Node is useful to publish undistorted image 

- topic publish 

```python
/undistorded/image_raw_3
```

## Node: undistort_img4

 This Node is useful to publish undistorted image 

- topic publish 

```python
/undistorded/image_raw_4
```

## [Run from the launch file](../my_yolo_launch/launch.md) 
