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

#ifndef SLAM_VIEWER_MAPPOINT_H
#define SLAM_VIEWER_MAPPOINT_H

#include <mutex>
#include <set>
#include <Eigen/Dense>
#include "KeyFrame.h"

namespace SLAM_VIEWER {

class KeyFrame;

class MapPoint {
 public:
    MapPoint(int id, const std::vector<double> &position);

    Eigen::Vector3d GetWorldPos();

    // Observations functions
    std::set<KeyFrame*> GetObservations();
    void AddObservation(KeyFrame* kf);
    void EraseObservation(KeyFrame* kf);

 private:
    // Map Point id
    int id_;

    // Position in absolute coordinates
    Eigen::Vector3d position_;

    // Keyframes observing the point
    std::set<KeyFrame*> observations_;

    std::mutex mutexPos_;
    std::mutex mutexFeatures_;

 public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

}  // namespace SLAM_VIEWER

#endif  // SLAM_VIEWER_MAPPOINT_H
