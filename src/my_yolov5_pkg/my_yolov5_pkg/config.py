from easydict import EasyDict as edict


__C                           = edict()
# Consumers can get config by: from config import cfg

cfg                           = __C

# YOLO options
__C.YOLO                      = edict()

__C.YOLO.CLASSES              = '/home/vishvajit/ros2_ws/src/my_yolov5_pkg/my_yolov5_pkg/data/classes/coco.names'