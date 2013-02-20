#ifndef DRONE_NAV_HPP_
#define DRONE_NAV_HPP_
#include "ros/ros.h"
#include "std_msgs/Empty.h"
#include "geometry_msgs/Twist.h"
#include <string>
#include <vector>
using namespace std; 

struct drone {
    double pos[3];
    string name; 
};

class drone_nav {
    public: 
        void advertise(vector<drone>); 
    private: 
        bool move_on_grid(string, int, int); 
        bool move_absolute(string, double, double, double); 
        bool is_valid_grid_cell(int, int); 
};


#endif
