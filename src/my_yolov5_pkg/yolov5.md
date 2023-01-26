# my_yolov5_pkg 

Simple object detection using yolov5 and .pt weights 


## Node: yolo_detect

- Detecting the object from one camera 

- Topic to subscribe 

```python
/image_raw
```

- Topic Published 

```python
/yolov5/bounding_boxes
/yolov5/image_raw'
```


## Node: yolo_2cam_detect

- Detecting the object from two camera 

- Topic to subscribe 

```python
/img_1
/img_2
```

- Topic Published 

```python
/yolov5/bounding_boxes_1
yolov5/bounding_boxes_2
/yolov5/image_raw_1
/yolov5/image_raw_2
```


## Node: yolo_4cam_detect

- Detecting the object from four camera 

- Topic to subscribe 

```python
/img_1
/img_2
/img_3
/img_4
```

- Topic Published 

```python
/yolov5/bounding_boxes_1
/yolov5/bounding_boxes_2
/yolov5/bounding_boxes_3
/yolov5/bounding_boxes_4
/yolov5/image_raw_1
/yolov5/image_raw_2
/yolov5/image_raw_3
/yolov5/image_raw_4
```

