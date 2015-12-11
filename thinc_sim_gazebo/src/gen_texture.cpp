//=================================================================================================
// Copyright (c) 2013 David Millard, Alex Poole, Emily Wall, and Kenneth Bogert - University of Georgia
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Simulation, Systems Optimization and Robotics
//       group, TU Darmstadt nor the names of its contributors may be used to
//       endorse or promote products derived from this software without
//       specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//=================================================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

//opencv2
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

//ros
#include "ros/ros.h"

using namespace std;
using namespace cv;

int main(int argc, char ** argv) {
    ros::init(argc, argv, "gen_texture");
    ros::NodeHandle n;

    if (argc != 7) {
        cout << "usage: " << argv[0];
        cout << " <columns> <rows> <col-scale> <row-scale>";
        cout << " <png-path> <world-path>" << endl;
        exit(1);
    }

    //save the arguments
    string output = "";
    string world_output = ""; 

    int columns = atoi(argv[1]);
    int rows = atoi(argv[2]);
    double x_scale = atof(argv[3]);
    double y_scale = atof(argv[4]);

    //determine size of the image
    int pixel_scale = 500; 
    int x_pixels = pixel_scale*rows;
    int y_pixels = pixel_scale*columns;

    //create matrix and window
    Mat grid_image = Mat::zeros(x_pixels, y_pixels, CV_8UC3);

    //create squares
    bool color = true; //to alternate colors
    bool first_color = true; //to alternate starting color of rows
 
    //size of circle
    int radius = 30;

    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {

            //set the starting color for the row
            if (j == 0 && first_color) { color = false; first_color = false; }
            else if (j == 0 && !first_color) { color = true; first_color = true; }

            if (color) {
                rectangle(
                    grid_image, Point(i*pixel_scale, j*pixel_scale),
                    Point((i+1)*pixel_scale, (j+1)*pixel_scale),
                    Scalar(102, 0, 255), -1, 8
                );//pink
                color = false;
            } else {
                rectangle(
                    grid_image, Point(i*pixel_scale, j*pixel_scale),
                    Point((i+1)*pixel_scale, (j+1)*pixel_scale),
                    Scalar(51, 204, 0), -1, 8
                );//green
                color = true;
            }
            circle(
                grid_image, Point(pixel_scale*(i+.5), pixel_scale*(j+.5)),
                (radius/2), Scalar(255, 255, 255), 
                radius, 8, 0
            ); //white
        }
    }

    imwrite(argv[5], grid_image);

    double origin_x = (-1)*(double)columns*y_scale;
    double origin_y = (-1)*(double)rows*x_scale;

    string spawn_x, spawn_y; 
    stringstream t1, t2; 
    t1 << origin_x; t2 << origin_y; 
    spawn_x = t1.str(); spawn_y = t2.str(); 

    //begin generation of world file
    world_output += "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
    world_output += "<sdf version=\"1.4\">\n"; 
    world_output += "  <world name=\"default\">\n";
    world_output += "    <gui>\n";
    world_output += "      <camera name=\"main\">\n";
    world_output += "        <pose>-6 -1 20 0 1.3 0</pose>\n";
    world_output += "      </camera>\n";
    world_output += "    </gui>\n";
    world_output += "    <scene>\n"; 
    world_output +="      <ambient>0.5 0.5 0.5 1</ambient>\n";
    world_output +="      <background>0.5 0.5 0.5 1</background>\n";
    world_output +="      <shadows>false</shadows>\n";
    world_output += "    </scene>\n"; 
    world_output += "    <physics type=\"ode\">\n";
    world_output += "      <gravity>0 0 -9.81</gravity>\n"; 
    world_output += "      <ode>\n"; 
    world_output += "        <solver>\n";
    world_output += "          <type>quick</type>\n";
    world_output += "          <iters>10</iters>\n";
    world_output += "          <sor>1.3</sor>\n";
    world_output += "        </solver>\n";
    world_output += "        <constraints>\n";
    world_output += "          <cfm>0.0</cfm>\n";
    world_output += "          <erp>0.2</erp>\n";
    world_output += "          <contact_max_correcting_vel>10</contact_max_correcting_vel>\n";
    world_output += "          <contact_surface_layer>0.001</contact_surface_layer>\n";
    world_output += "        </constraints>\n";
    world_output += "      </ode>\n"; 
    world_output += "      <real_time_update_rate>1000</real_time_update_rate>\n";
    world_output += "      <max_step_size>0.001</max_step_size>\n";
    world_output += "    </physics>\n"; 
    world_output += "    <light type=\"directional\" name=\"directional_light_1\">\n";
    world_output += "      <pose>0 0 20 0 0 0</pose>\n";
    world_output += "      <diffuse>1 1 1 1</diffuse>\n";
    world_output += "      <specular>1 1 1 1</specular>\n";
    world_output += "      <attenuation>\n";
    world_output += "        <range>300</range>\n";
    world_output += "      </attenuation>\n";
    world_output += "      <direction>1 1 -1</direction>\n";
    world_output += "      <cast_shadows>false</cast_shadows>\n";
    world_output += "    </light>\n";
    world_output += "    <light type=\"directional\" name=\"directional_light_2\">\n";
    world_output += "      <pose>0 0 20 0 0 0</pose>\n";
    world_output += "      <diffuse>1 1 1 1</diffuse>\n";
    world_output += "      <specular>1 1 1 1</specular>\n";
    world_output += "      <attenuation>\n";
    world_output += "        <range>300</range>\n";
    world_output += "      </attenuation>\n";
    world_output += "      <direction>-1 1 -1</direction>\n";
    world_output += "      <cast_shadows>false</cast_shadows>\n";
    world_output += "    </light>\n"; 
    world_output += "    <light type=\"directional\" name=\"directional_light_3\">\n";
    world_output += "      <pose>0 0 20 0 0 0</pose>\n";
    world_output += "      <diffuse>1 1 1 1</diffuse>\n";
    world_output += "      <specular>1 1 1 1</specular>\n";
    world_output += "      <attenuation>\n";
    world_output += "        <range>300</range>\n";
    world_output += "      </attenuation>\n";
    world_output += "      <direction>-1 -1 -1</direction>\n";
    world_output += "      <cast_shadows>false</cast_shadows>\n";
    world_output += "    </light>\n"; 
    world_output += "    <model name=\"grid\">\n"; 
    world_output += "      <link name=\"grid_link\">\n"; 
    world_output += "        <pose>" + spawn_x + " " + spawn_y + " 0 0 0 0</pose>\n"; 
    world_output += "        <collision name=\"grid_collision\">\n";
    world_output += "          <geometry>\n"; 
    world_output += "            <plane>\n"; 
    world_output += "              <normal>0 0 1</normal>\n"; 
    world_output += "            </plane>\n"; 
    world_output += "          </geometry>\n"; 
    world_output += "          <surface>\n"; 
    world_output += "            <friction>\n"; 
    world_output += "              <ode>\n"; 
    world_output += "                <mu>10.0</mu>\n"; 
    world_output += "                <mu2>10.0</mu2>\n"; 
    world_output += "                <fdir1>0 0 0</fdir1>\n"; 
    world_output += "                <slip1>0</slip1>\n"; 
    world_output += "                <slip2>0</slip2>\n"; 
    world_output += "              </ode>\n"; 
    world_output += "            </friction>\n"; 
    world_output += "            <bounce>\n"; 
    world_output += "              <restitution_coefficient>0</restitution_coefficient>\n"; 
    world_output += "              <threshold>1000000.0</threshold>\n"; 
    world_output += "            </bounce>\n"; 
    world_output += "            <contact>\n"; 
    world_output += "              <ode>\n"; 
    world_output += "                <soft_cfm>0</soft_cfm>\n"; 
    world_output += "                <soft_erp>0.2</soft_erp>\n"; 
    world_output += "                <kp>1e10</kp>\n"; 
    world_output += "                <kd>1</kd>\n"; 
    world_output += "                <max_vel>100.0</max_vel>\n"; 
    world_output += "                <min_depth>0.0001</min_depth>\n"; 
    world_output += "              </ode>\n"; 
    world_output += "            </contact>\n"; 
    world_output += "          </surface>\n"; 
    world_output += "        </collision>\n"; 
    world_output += "        <visual name=\"grid\">\n"; 
    world_output += "          <geometry>\n"; 
    world_output += "            <mesh>\n"; 
    world_output += "              <uri>model://grid.dae</uri>\n"; 
    world_output += "              <scale>1 1 1</scale>\n"; 
    world_output += "            </mesh>\n"; 
    world_output += "          </geometry>\n"; 
    world_output += "          <cast_shadows>false</cast_shadows>\n"; 
    world_output += "        </visual>\n"; 
    world_output += "      </link>\n"; 
    world_output += "      <static>true</static>\n"; 
    world_output += "    </model>\n"; 
    world_output += "  </world>\n"; 
    world_output += "</sdf>\n"; 

    //write to file
    ofstream ofs;
    ofs.open(argv[6], ios::trunc);
    if (ofs.is_open())
        ofs << world_output;
    ofs.close();

    return 0;
}
