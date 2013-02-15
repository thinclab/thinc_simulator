#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

//opencv2
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#define w 400

using namespace std; 
using namespace cv; 

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cout << "You must enter 4 additional arguments."; 
        exit(1); 
    }
    
    //save the arguments
    string output = ""; 
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
        }
    }

    imshow(grid_window, grid_image);
    imwrite("grid.png", grid_image);
//    cvMoveWindow(grid_window, 0, 200);

    waitKey(0);


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
    ofs.open("grid.urdf.xacro", ios::trunc);  
    if (ofs.is_open()) 
        ofs << output; 
    ofs.close(); 
}
