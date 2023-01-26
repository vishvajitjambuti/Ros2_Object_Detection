# my_camera_pkg

This package is useful for publishing camera image and subscribing the images

- these are the following Nodes are available 

## Node: camera_pub

Publish the camera image 

- Parameters

```python 
camera_id  # default 0 
``` 

- This node Publishes to following topic 

```python 
\image_raw
\fps # frame rate 
```

## Node: camera_stride_pub

Publish the camera image  with skipping frame 

- Parameters

```python 
camera_id  # default 0 
vid_stride
``` 

- This node Publishes to following topic 

```python 
\image_raw
\fps # frame rate 
```

## Node: 2camera_pub

Publish the camera image  with skipping frame 

- Parameters

```python 
camera_id  # default 0 
camera_id_2

``` 

- This node Publishes to following topic 

```python 
\img_1
\img_1 # frame rate 
```

## Node: camera_sub

Subscribe the image and view the image

- Parameters

```python 
window_name  # default 0 
``` 

- This node subscribes to following topic 

```python 
\image_raw
\fps # frame rate 
```

## Node: 2camera_sub


Subscribe the image and view the image

- This node subscribes to following topic 

```python 
\img_1
\img_2  
```
