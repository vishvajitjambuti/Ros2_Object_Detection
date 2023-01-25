#!/bin/bash

BASEDIR=${PWD}
echo "Ros2 workspace : $BASEDIR"

echo "running colcon build"

#colcon build --symlink-install

echo "sourceing the local setup file for workspace"

.  ./install/setup.bash

