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

#define w 400

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {

//    ros::init(argc, argv, "grid_cells");
//    ros::NodeHandle n; 
//    ros::Rate loop_rate(10); 

    if (argc != 5) {
        cout << "You must enter 4 additional arguments.";
        exit(1);
    }

    //save the arguments
    string output = "";
    string world_output = ""; 
    string c = argv[1];
    string r = argv[2];
    string width = argv[3];
    string height = argv[4];

    //convert arguments to ints
    int columns, rows, cell_width, cell_height;
    stringstream s1(c); stringstream s2(r);
    stringstream s3(width); stringstream s4(height);
    s1 >> columns; s2 >> rows;
    s3 >> cell_width; s4 >> cell_height;

    //determine size of the image
    int pixels_per_meter = 100;
    cell_width *= pixels_per_meter;
    cell_height *= pixels_per_meter;
    int x_pixels = cell_width*rows;
    int y_pixels = cell_height*columns;

    //create matrix and window
    Mat grid_image = Mat::zeros(x_pixels, y_pixels, CV_8UC3);
    char grid_window[] = "Grid";

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
                rectangle(grid_image, Point(i*cell_width, j*cell_height),
                    Point((i+1)*cell_width, (j+1)*cell_height),
                    Scalar(102, 0, 255), -1, 8);//pink
                color = false;

            }
            else {
                rectangle(grid_image, Point(i*cell_width, j*cell_height),
                    Point((i+1)*cell_width, (j+1)*cell_height),
                    Scalar(51, 204, 0), -1, 8);//green
                color = true;
            }
            circle(grid_image, Point(cell_width*(i+.5), cell_height*(j+.5)),
	        (cell_width/8), Scalar(255, 255, 255), 
		cell_width/4, 8, 0); //white
        }
    }

    imwrite("../Media/models/grid/material_1.png", grid_image);
    waitKey(0);                                                                                                   

    double origin_x = (-1)*columns/2; 
    double origin_y = (-1)*rows/2; 

    string spawn_x = origin_x.str(); 
    //begin urdf output
    output += "<?xml version=\"1.0\"?>\n\n\n<robot name=\"grid\">\n\n";
    output += "  <link name=\"base_link\">\n";

    //convert grid size to strings 
    stringstream s5, s6; string x_size, y_size;
    s5 << x_pixels; s6 << y_pixels;
    x_size = s5.str(); y_size = s6.str();

    //write link name and info 
    output += "    <inertial>\n";
    output += "      <origin xyz=\"0 0 0\"/>\n";
    output += "      <mass value=\"1.0\" />\n";
    output += "      <inertia  ixx=\"0.0\" ixy=\"0.0\"  ixz=\"0.0\"  iyy=\"0.0\"  iyz=\"0.0\"  izz=\"0.0\" />\n";
    output += "    </inertial>\n";
    output += "    <visual>\n";
    output += "      <origin xyz=\"0 0 0\"/>\n";
    output += "      <geometry>\n";
    output += "        <box size=\"" + c + " " + r + " 0.1\" />\n";
    output += "      </geometry>\n";
    output += "    </visual>\n";
    output += "    <collision>\n";
    output += "      <origin xyz=\"0 0 0\"/>\n";
    output += "      <geometry>\n";
    output += "        <box size=\"" + c + " " + r + " 0.1\" />\n";
    output += "      </geometry>\n";
    output += "    </collision>\n";
    output += "  </link>\n\n";
    output += "  <gazebo reference=\"base_link\">\n";
    output += "    <material name=\"grid\">\n";
    output += "      <texture filename=\"file://grid.png\"/>\n";
    output += "    </material>\n";
    output += "    <static>true</static>\n";
    output += "  </gazebo>\n\n";
    output += "</robot>";

    //write to file
    ofstream ofs;
    ofs.open("../urdf/grid.urdf.xacro", ios::trunc);
    if (ofs.is_open())
        ofs << output;
    ofs.close();

    

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
    world_output += "        <origin pose=\"" + origin_x + " " + origin_y + " 0 0 0 0\"/>\n"; 
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


}                         
