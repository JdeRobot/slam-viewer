# SLAM Viewer
**Authors:** [Eduardo Perdices](https://gsyc.urjc.es/~eperdices/)

SLAM Viewer

# 1. License

SLAM Viewer is released under a [GPLv3 license](https://github.com/eperdices/slam-viewer/blob/master/License-gpl.txt).

# 2. Prerequisites
We have tested the library in **Ubuntu 16.04**, but it should be easy to compile in other platforms.

## Pangolin
We use [Pangolin](https://github.com/stevenlovegrove/Pangolin) for visualization and user interface. Dowload and install instructions can be found at: https://github.com/stevenlovegrove/Pangolin.

## OpenCV
We use [OpenCV](http://opencv.org) to manipulate images and features. Dowload and install instructions can be found at: http://opencv.org. **Required at leat 2.4.3. Tested with OpenCV 2.4.11 and OpenCV 3.2**.

## Eigen3
We use [Eigen3](http://eigen.tuxfamily.org) to perform matrices operations. Download and install instructions can be found at: http://eigen.tuxfamily.org. **Required at least 3.1.0**.

# 3. Building SLAM Viewer library and examples

Clone the repository:
```
git clone https://github.com/eperdices/slam-viewer
```
We provide a script `build.sh` to build *SLAM Viewer*. Please make sure you have installed all required dependencies (see section 2). Execute:

```
cd slam-viewer
chmod +x build.sh
./build.sh
```

This will create **libSLAM_VIEWER.so** at *lib* folder and the executable **Viewer** in *bin* folder.

# 4. Run SLAM Viewer

Execute the following command. Change `TRAJECTORY_FILE` to the path to the corresponding trajectory file (see Examples/trajectory.yaml). 

```
./bin/Viewer TRAJECTORY_FILE
```
