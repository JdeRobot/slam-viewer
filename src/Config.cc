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

#include <vector>
#include <opencv2/core/core.hpp>
#include "Config.h"
#include "extra/log.h"

using std::vector;

namespace SLAM_VIEWER {

Config::Config() {
    // Default UI values
    kKeyFrameSize_ = 0.05;
    kKeyFrameLineWidth_ = 1.0;
    kGraphLineWidth_ = 0.9;
    kPointSize_ = 2.0;
    kCameraSize_ = 0.08;
    kCameraLineWidth_ = 3.0;
    kViewpointX_ = 0.0;
    kViewpointY_ = -0.7;
    kViewpointZ_ = -1.8;
    kViewpointF_ = 500.0;
}

bool Config::ReadParameters(std::string filename, Map &map) {
    cv::FileStorage fs;

    try {
        // Read config file
        fs.open(filename.c_str(), cv::FileStorage::READ);
        if (!fs.isOpened()) {
            LOGE("Failed to open file: %s", filename.c_str());
            return false;
        }
    } catch(cv::Exception &ex) {
        LOGE("Parse error: %s", ex.what());
        return false;
    }

    // Read camera parameters
    cv::FileNode camera = fs["camera"];
    CameraParameters cdata;
    camera["fx"] >> cdata.fx;
    camera["fy"] >> cdata.fy;
    camera["cx"] >> cdata.cx;
    camera["cy"] >> cdata.cy;
    camera["k1"] >> cdata.k1;
    camera["k2"] >> cdata.k2;
    camera["p1"] >> cdata.p1;
    camera["p2"] >> cdata.p2;
    camera["k3"] >> cdata.k3;

    // Read keyframes
    cv::FileNode keyframes = fs["keyframes"];

    for(auto it = keyframes.begin(); it != keyframes.end(); ++it) {
        int id;
        vector<double> pose;
        std::string filename;

        (*it)["id"] >> id;
        (*it)["filename"] >> filename;
        (*it)["pose"] >> pose;

        KeyFrame * kf = new KeyFrame(id, filename, pose);
        map.AddKeyFrame(kf);
    }

    // Read map points
    cv::FileNode points = fs["points"];

    for(auto it = points.begin(); it != points.end(); ++it) {
        int id;
        vector<double> position;

        (*it)["id"] >> id;
        (*it)["pose"] >> position;

        MapPoint * mp = new MapPoint(id, position);
        map.AddMapPoint(mp);

        cv::FileNode observations = (*it)["observations"];

        // Read observations
        for(auto it_obs = observations.begin(); it_obs != observations.end(); ++it_obs) {
            int kf_id;
            vector<double> pixel;

            (*it_obs)["kf"] >> kf_id;
            (*it_obs)["pixel"] >> pixel;

            // Search keyFrame by id
            KeyFrame * kf = map.GetKeyFrame(kf_id);
            if (kf != nullptr) {
                kf->AddObservation(mp, pixel);
            } else {
                LOGD("Observation ignored, KeyFrame %d not found", kf_id);
            }
        }
    }

    fs.release();

    // Synchronize map
    map.UpdateConnections();

    return true;
}

}  // namespace SLAM_VIEWER
