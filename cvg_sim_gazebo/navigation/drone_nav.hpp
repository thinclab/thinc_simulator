#ifndef DRONE_NAV_HPP_
#define DRONE_NAV_HPP_
#include "drone.hpp"
#include "ros/ros.h"
#include "std_msgs/Empty.h"
#include "geometry_msgs/Twist.h"
#include <string>
#include <vector>
#include <sstream>
using namespace std; 

class drone_nav {
    public:
        drone_nav(vector<drone*>, int, int); 
        void advertise(vector<drone*>);  
        bool move_on_grid(string, int, int);
        bool move_absolute(string, double, double, double);
    private:
        int columns; 
        int rows; 
        vector<drone*> drones; 
        bool is_valid_grid_cell(int, int); 
        drone* find_drone(string);  
};

#endif
