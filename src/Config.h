/**
 *
 *  Copyright (C) 2018 Eduardo Perdices <eperdices at gsyc dot es>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef SLAM_VIEWER_CONFIG_H_
#define SLAM_VIEWER_CONFIG_H_

#include <iostream>
#include <string>
#include "Map.h"

namespace SLAM_VIEWER {

struct CameraParameters {
    double fx;
    double fy;
    double cx;
    double cy;
    double k1;
    double k2;
    double p1;
    double p2;
    double k3;
};

class Config {
 public:
    // Singleton
    static Config& GetInstance() {
        static Config instance;
        return instance;
    }

    // Read parameters from file
    bool ReadParameters(std::string filename, Map &map);

    // Get UI parameters
    static double KeyFrameSize() { return GetInstance().kKeyFrameSize_; }
    static double KeyFrameLineWidth() { return GetInstance().kKeyFrameLineWidth_; }
    static double GraphLineWidth() { return GetInstance().kGraphLineWidth_; }
    static double PointSize() { return GetInstance().kPointSize_; }
    static double CameraSize() { return GetInstance().kCameraSize_; }
    static double CameraLineWidth() { return GetInstance().kCameraLineWidth_; }
    static double ViewpointX() { return GetInstance().kViewpointX_; }
    static double ViewpointY() { return GetInstance().kViewpointY_; }
    static double ViewpointZ() { return GetInstance().kViewpointZ_; }
    static double ViewpointF() { return GetInstance().kViewpointF_; }

 private:
    Config();

    // UI
    double kKeyFrameSize_;
    double kKeyFrameLineWidth_;
    double kGraphLineWidth_;
    double kPointSize_;
    double kCameraSize_;
    double kCameraLineWidth_;
    double kViewpointX_;
    double kViewpointY_;
    double kViewpointZ_;
    double kViewpointF_;
};

}  // namespace SLAM_VIEWER


#endif  // SLAM_VIEWER_CONFIG_H_
