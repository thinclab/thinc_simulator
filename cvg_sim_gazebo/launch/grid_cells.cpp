#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std; 

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
    stringstream s1(c); 
    s1 >> columns;
    stringstream s2(r); 
    s2 >> rows;  
    stringstream s3(width); 
    s3 >> cell_width; 
    stringstream s4(height); 
    s4 >> cell_height; 
   
    //define colors
    string WHITE = "      <material name=\"white\">\n        <color rgba=\"1 1 1 1\"/>\n      </material>\n";
    string BLUE = "      <material name=\"blue\">\n        <color rgba=\"0 0 0.8 1\"/>\n      </material>\n";


    bool color = true;
    int counter = 0;  
    output += "<?xml version=\"1.0\"?>\n\n\n<robot name=\"grid\">\n";

    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            //convert position coordinates for grid to strings
            string col_pos, row_pos, count; 
            stringstream s5;
            s5 << i * columns * cell_width + 0.01;
            col_pos = s5.str(); ;
            stringstream s6;
            s6 << j * rows * cell_height + 0.01;
            row_pos = s6.str();
            stringstream s7; 
            s7 << counter; 
            count = s7.str(); 
            
            if (j == 0)
                output += "  <link name=\"base_link\">\n";
            else
                output += "  <link name=\"link" + count + "\">\n";
            counter++;

            output += "    <inertial>\n";
            output += "      <origin xyz=\"" + col_pos + " " + row_pos + " 0\"/>\n";
            output += "      <mass value=\"1.0\" />\n";
            output += "      <inertia  ixx=\"1.0\" ixy=\"0.0\"  ixz=\"0.0\"  iyy=\"100.0\"  iyz=\"0.0\"  izz=\"1.0\" />\n";
            output += "    </inertial>\n";
            output += "    <visual>\n";
            output += "      <origin xyz=\"" + col_pos + " " + row_pos + " 0\"/>\n";
            output += "      <geometry>\n";
            output += "        <box size=\"" + width + " " + height + " 0.1\" />\n";
            output += "      </geometry>\n";
            output += "      <material name=\"blue\">\n";
            output += "        <color rgba=\"0 0 .8 1\"/>\n";
            output += "      </material>\n";
            output += "    </visual>\n";
            output += "    <collision>\n";
            output += "      <origin xyz=\"" + col_pos + " " + row_pos + " 0\"/>\n";
            output += "      <geometry>\n";
            output += "        <box size=\"" + width + " " + height + " 0.1\" />\n";
            output += "      </geometry>\n";
            output += "    </collision>\n";
            output += "  </link>\n";
            output += "  <gazebo>\n";
            output += "    <static>true</static>\n";
            output += "  </gazebo>\n\n\n";
        }
    }

    output += "</robot>";

    //write to file
    ofstream ofs; 
    ofs.open("grid.urdf", ios::trunc);  
    if (ofs.is_open()) 
        ofs << output; 
    ofs.close(); 
}
