# my_yolo_launch

This package contain following launch files 

## Launch: 4cam.launch.py

- Publish Undistored images from my_undistort_pkg 
- four camera images are published 
- topic Published 

```python
/img_1
/img_2
/img_3
/img_4
```

## Launch : view_2cam.launch.py

- Subscribe the image and view the image coming from two camera 

- topic subscribed 

```python
/img_1
/img_2

```

## launch : view_4cam.launch.py

- Subscribe the image and view the image coming from four camera 

- topic subscribed 

```python
/img_1
/img_2
/img_3
/img_4

```

## launch : yolo_app.launch.py

-single camera image publish and object detection from single camera  
