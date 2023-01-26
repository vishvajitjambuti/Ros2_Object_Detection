# my_tensorRt_pkg

This this package  is useful for Object Detection using tensorRT 

## Before Building The Node Make Following Changes In File

Before building the package you need to make changes in paths of engine_file_path and PLUGIN_LIBRARY

please check line are(line approx:  452 to 460)

- In file : trtnode.py, trwcam_trt.py and multicam_trt.py 

```python
PLUGIN_LIBRARY = "{your path}/src/my_tensorRt_pkg/my_tensorRt_pkg/build/libmyplugins.so"
engine_file_path = "{your path}/src/my_tensorRt_pkg/my_tensorRt_pkg/build/Vishvajit_trt.engine"
```


- This are the following nodes are available in pkg  

## Node: TRT_node

This node is useful to detect objects from one camera 

- This has following node subscribe to following topics 

```python 
\img_1
```

- This node Publishes to following topic 

```python 
\trt_image
```

## Node: twocam_trt


This node is useful to detect objects from two camera 

- This has following node subscribe to following topics 

```python 
\img_1
\img_2
```

- This node Publishes to following topic 
- All topic msg type  are Image 

```python 
\trt_image_1
\trt_image_2
```


## Node: multicam_trt

This node is useful to detect objects from four camera.

- This has following node subscribe to following topics 

```python 
\img_1
\img_2
\img_3
\img_4
```

- This node Publishes to following topic 
- All topic msg type  are Image 

```python 
\trt_image_1
\trt_image_2
\trt_image_3
\trt_image_4 

```
