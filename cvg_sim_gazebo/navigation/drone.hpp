#ifndef DRONE_HPP_
#define DRONE_HPP_

#include "ros/ros.h"
#include "std_msgs/Empty.h"
#include "geometry_msgs/Twist.h"
#include <string>
#include <cmath>
using namespace std; 

class drone {
    public: 
        drone(string, int, int); 
        void advertise(void);
        void move_on_grid(int, int);
        void move_absolute(double, double, double);
        int id; 
 
    private: 
        int grid_pos[2]; 
        double abs_pos[3]; 
        std_msgs::Empty empty_msg; 
        geometry_msgs::Twist twist_msg; 

    // ADD: Check expected grid cell color vs. actual cell color
    // ADD: Way to handle when we ended up in the wrong cell
    // ADD: Check for orientation to adjust which way we move
};

#endif
