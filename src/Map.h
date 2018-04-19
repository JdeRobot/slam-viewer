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

#ifndef SLAM_VIEWER_MAP_H
#define SLAM_VIEWER_MAP_H

#include <set>
#include <mutex>
#include "MapPoint.h"
#include "KeyFrame.h"

namespace SLAM_VIEWER {

class MapPoint;
class KeyFrame;

class Map {
 public:
    Map();

    std::vector<KeyFrame*> GetAllKeyFrames();
    std::vector<MapPoint*> GetAllMapPoints();

    // Get KeyFrame by id
    KeyFrame* GetKeyFrame(int id);

    // Add KeyFrames and MapPoints
    void AddKeyFrame(KeyFrame* kf);
    void AddMapPoint(MapPoint* mp);

    // Remove KeyFrames and MapPoints
    void EraseMapPoint(MapPoint* mp);
    void EraseKeyFrame(KeyFrame* kf);

    // Update connected KeyFrames
    void UpdateConnections();

    // Clear saved data
    void clear();

 private:
    std::set<MapPoint*> mapPoints_;
    std::set<KeyFrame*> keyFrames_;

    std::mutex mmutexMap_;
};

}  // namespace SLAM_VIEWER

#endif  // SLAM_VIEWER_MAP_H
