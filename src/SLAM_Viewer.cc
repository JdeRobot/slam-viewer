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

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "Config.h"
#include "Map.h"
#include "ui/Viewer.h"
#include "ui/MapDrawer.h"

using namespace std;

int main(int argc, char **argv) {
    vector<string> vFilenames;
    SLAM_VIEWER::Map map;

    if(argc != 2) {
        cerr << endl << "Usage: ./monocular data.yaml" << endl;
        return 1;
    }

    // Read parameters
    SLAM_VIEWER::Config &config = SLAM_VIEWER::Config::GetInstance();
    if (!config.ReadParameters(argv[1], map)) {
        cerr << "[ERROR] Data file contains errors" << endl;
        return 1;
    }

    // Create user interface
    SLAM_VIEWER::MapDrawer * mdrawer = new SLAM_VIEWER::MapDrawer(&map);

    SLAM_VIEWER::Viewer* viewer = nullptr;
    std::thread* tviewer = nullptr;

    viewer = new SLAM_VIEWER::Viewer(mdrawer);
    tviewer = new std::thread(&SLAM_VIEWER::Viewer::Run, viewer);

    // Wait until threads start
    usleep(1000*1e3);

    // Main loop
    while (!viewer->isFinished()) {
        // Wait
        usleep(30*1e3);
    }

    viewer->RequestFinish();
    while (!viewer->isFinished())
        usleep(5000);

    tviewer->join();

    return 0;
}
