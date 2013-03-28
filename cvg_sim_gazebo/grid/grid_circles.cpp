//C++
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

int main(int argc, char* argv[]) {

    if (argc != 5) {
        cout << "You must enter 4 additional arguments.";
        exit(1);
    }

    //save the arguments
    string output = "";
    string world_output = ""; 
    string c = argv[1];
    string r = argv[2];
    string x = argv[3]; 
    string y = argv[4]; 

    //convert arguments to ints
    int columns, rows;
    double x_scale, y_scale; 
    stringstream s1(c); stringstream s2(r);
    stringstream x1(x); stringstream y1(y); 
    s1 >> columns; s2 >> rows;
    x1 >> x_scale; y1 >> y_scale; 

    //determine size of the image
    int pixel_scale = 500; 
    int x_pixels = pixel_scale*rows;
    int y_pixels = pixel_scale*columns;

    //create matrix and window
    Mat grid_image = Mat::zeros(x_pixels, y_pixels, CV_8UC3);

    //create squares
    bool color = true; //to alternate colors
    bool first_color = true; //to alternate starting color of rows

    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {

            //set the starting color for the row
            if (j == 0 && first_color) {
                color = false;
                first_color = false;
            }
            else if (j == 0 && !first_color) {
                color = true;
                first_color = true;
            }

            if (color) {
                rectangle(grid_image, Point(i*pixel_scale, j*pixel_scale),
                    Point((i+1)*pixel_scale, (j+1)*pixel_scale),
                    Scalar(102, 0, 255), -1, 8);//pink
                color = false;

            }
            else {
                rectangle(grid_image, Point(i*pixel_scale, j*pixel_scale),
                    Point((i+1)*pixel_scale, (j+1)*pixel_scale),
                    Scalar(51, 204, 0), -1, 8);//green
                color = true;
            }
            circle(grid_image, Point(pixel_scale*(i+.5), pixel_scale*(j+.5)),
	        (pixel_scale/20), Scalar(255, 255, 255), 
		pixel_scale/20, 8, 0); //white
        }
    }

    imwrite("../Media/models/material_1.png", grid_image);
    waitKey(0);                                                       

    double origin_x = (-1)*columns*y_scale/2; 
    double origin_y = (-1)*rows*x_scale/2; 

    string spawn_x, spawn_y; 
    stringstream t1, t2; 
    t1 << origin_x; t2 << origin_y; 
    spawn_x = t1.str(); spawn_y = t2.str(); 

    //begin generation of world file
    world_output += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    world_output += "<gazebo version=\"1.0\">\n"; 
    world_output += "  <world name=\"default\">\n";
    world_output += "    <scene>\n"; 
    world_output += "      <ambient rgba=\"0.5 0.5 0.5 1\"/>\n";
    world_output += "      <background rgba=\"0.5 0.5 0.5 1\"/>\n";
    world_output += "      <shadows enabled=\"false\"/>\n";
    world_output += "    </scene>\n"; 
    world_output += "    <physics type=\"ode\" update_rate=\"1000\">\n";
    world_output += "      <gravity xyz=\"0 0 -9.81\"/>\n"; 
    world_output += "      <ode>\n"; 
    world_output += "        <solver type=\"quick\" dt=\"0.001\" iters=\"10\" sor=\"1.3\"/>\n";
    world_output += "        <constraints cfm=\"0.0\" erp=\"0.2\" contact_max_correcting_vel=\"10\" contact_surface_layer=\"0.001\"/>\n"; 
    world_output += "      </ode>\n"; 
    world_output += "    </physics>\n"; 
    world_output += "    <light type=\"directional\" name=\"directional_light_1\" cast_shadows=\"false\">\n"; 
    world_output += "      <origin pose=\"0 0 20 0 0 0\"/>\n"; 
    world_output += "      <diffuse rgba=\"1 1 1 1\"/>\n"; 
    world_output += "      <specular rgba=\"1 1 1 1\"/>\n"; 
    world_output += "      <attenuation range=\"300\"/>\n"; 
    world_output += "      <direction xyz=\"1 1 -1\"/>\n";
    world_output += "    </light>\n";
    world_output += "    <light type=\"directional\" name=\"directional_light_2\" cast_shadows=\"false\">\n"; 
    world_output += "      <origin pose=\"0 0 20 0 0 0\"/>\n"; 
    world_output += "      <diffuse rgba=\"1 1 1 1\"/>\n"; 
    world_output += "      <specular rgba=\"1 1 1 1\"/>\n"; 
    world_output += "      <attenuation range=\"300\"/>\n"; 
    world_output += "      <direction xyz=\"-1 1 -1\"/>\n"; 
    world_output += "    </light>\n"; 
    world_output += "    <light type=\"directional\" name=\"directional_light_3\" cast_shadows=\"false\">\n"; 
    world_output += "      <origin pose=\"0 0 20 0 0 0\"/>\n"; 
    world_output += "      <diffuse rgba=\"1 1 1 1\"/>\n"; 
    world_output += "      <specular rgba=\"1 1 1 1\"/>\n"; 
    world_output += "      <attenuation range=\"300\"/>\n"; 
    world_output += "      <direction xyz=\"-1 -1 -1\"/>\n"; 
    world_output += "    </light>\n"; 
    world_output += "    <model name=\"grid\" static=\"true\">\n"; 
    world_output += "      <link name=\"grid_link\">\n"; 
    world_output += "        <origin pose=\"" + spawn_x + " " + spawn_y + " 0 0 0 0\"/>\n"; 
    world_output += "        <collision name=\"grid_collision\">\n"; 
    world_output += "<!--                 <geometry>\n"; 
    world_output += "                     <mesh filename=\"grid.dae\" scale=\"1 1 1\"/>\n"; 
    world_output += "             </geometry> -->\n"; 
    world_output += "        <geometry>\n"; 
    world_output += "          <plane normal=\"0 0 1\"/>\n"; 
    world_output += "        </geometry>\n"; 
    world_output += "        <surface>\n"; 
    world_output += "          <friction>\n"; 
    world_output += "            <ode mu=\"10.0\" mu2=\"10.0\" fdir1=\"0 0 0\" slip1=\"0\" slip2=\"0\"/>\n"; 
    world_output += "          </friction>\n"; 
    world_output += "          <bounce restitution_coefficient=\"0\" threshold=\"1000000.0\"/>\n"; 
    world_output += "          <contact>\n"; 
    world_output += "            <ode soft_cfm=\"0\" soft_erp=\"0.2\" kp=\"1e10\" kd=\"1\" max_vel=\"100.0\" min_depth=\"0.0001\"/>\n"; 
    world_output += "          </contact>\n"; 
    world_output += "        </surface>\n"; 
    world_output += "      </collision>\n"; 
    world_output += "      <visual name=\"grid\" cast_shadows=\"false\">\n"; 
    world_output += "        <geometry>\n"; 
    world_output += "          <mesh filename=\"grid.dae\" scale=\"1 1 1\"/>\n"; 
    world_output += "        </geometry>\n"; 
    world_output += "      </visual>\n"; 
    world_output += "    </link>\n"; 
    world_output += "  </model>\n"; 
    world_output += "</world>\n"; 
    world_output += "</gazebo>\n"; 

    //write to file
    ofstream ofs;
    ofs.open("../worlds/grid.world", ios::trunc);
    if (ofs.is_open())
        ofs << world_output;
    ofs.close();



}                         
