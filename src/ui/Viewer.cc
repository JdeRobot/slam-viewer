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

#include "Viewer.h"
#include <pangolin/pangolin.h>
#include <unistd.h>
#include "Config.h"
#include "extra/log.h"

using std::mutex;
using std::unique_lock;

namespace SLAM_VIEWER {

Viewer::Viewer(MapDrawer *pMapDrawer):
    mpMapDrawer(pMapDrawer), mbFinishRequested(false), mbFinished(true) {
}

void Viewer::Run() {
    int w, h, mw;

    mbFinished = false;
    w = 1024;
    h = 768;
    mw = 175;

    pangolin::CreateWindowAndBind("SLAM Viewer", w, h);

    // 3D Mouse handler requires depth testing to be enabled
    glEnable(GL_DEPTH_TEST);

    // Issue specific OpenGl we might need
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pangolin::CreatePanel("menu").SetBounds(0.0, 1.0, 0.0,pangolin::Attach::Pix(mw));
    pangolin::Var<bool> menuShowPoints("menu.Show Points", true, true);
    pangolin::Var<bool> menuShowKeyFrames("menu.Show KeyFrames", true, true);
    pangolin::Var<bool> menuShowGraph("menu.Show Graph", true, true);
    pangolin::Var<bool> menuReset("menu.Reset", false, false);

    // Define Camera Render Object (for view / scene browsing)
    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(w, h, Config::ViewpointF(), Config::ViewpointF(), w/2, h/2, 0.1, 1000),
        pangolin::ModelViewLookAt(Config::ViewpointX(), Config::ViewpointY(), Config::ViewpointZ(), 0, 0, 0, 0.0,-1.0, 0.0));

    // Add named OpenGL viewport to window and provide 3D Handler
    pangolin::View& d_cam = pangolin::CreateDisplay()
        .SetBounds(0.0, 1.0, pangolin::Attach::Pix(mw), 1.0, -w/(float)h)
        .SetHandler(new pangolin::Handler3D(s_cam));

    pangolin::OpenGlMatrix Twc;
    Twc.SetIdentity();

    while (!pangolin::ShouldQuit()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        d_cam.Activate(s_cam);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        if (menuShowKeyFrames || menuShowGraph)
            mpMapDrawer->DrawKeyFrames(menuShowKeyFrames, menuShowGraph);
        if (menuShowPoints)
            mpMapDrawer->DrawMapPoints();

        pangolin::FinishFrame();

        if (menuReset) {
            menuShowGraph = true;
            menuShowKeyFrames = true;
            menuShowPoints = true;
            menuReset = false;
        }

        if (CheckFinish())
            break;
    }

    SetFinish();

	LOGD("UI thread finished, exiting...");
}

void Viewer::RequestFinish() {
    unique_lock<mutex> lock(mMutexFinish);
    mbFinishRequested = true;
}

bool Viewer::CheckFinish() {
    unique_lock<mutex> lock(mMutexFinish);
    return mbFinishRequested;
}

void Viewer::SetFinish() {
    unique_lock<mutex> lock(mMutexFinish);
    mbFinished = true;
}

bool Viewer::isFinished() {
    unique_lock<mutex> lock(mMutexFinish);
    return mbFinished;
}

}  // namespace SLAM_VIEWER
