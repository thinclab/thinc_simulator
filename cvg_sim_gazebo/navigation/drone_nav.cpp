/*
 * Responsible for navigating the drone on the grid in simulation.
 */

#include "drone_nav.hpp"

int main(int argc, char* argv[]) {

    drone_nav* dn = new drone_nav(); 
    ros::init(argc, argv, "mover"); 
//    ros::NodeHandle n; 
    vector<drone> drones;
    //using argc, populate drones vector  
    dn->advertise(drones);
}

/*
 * Advertise to appropriate topics for given drones.
 * Each drone has its own set of topics.
 */
void drone_nav::advertise(vector<drone> drones) {
    ros::NodeHandle n; 

    //for now, hard code in advertising to topics for two drones
    ros::Publisher drone0_takeoff_pub = n.advertise<std_msgs::Empty>("drone0/ardrone/takeoff", 1);
    ros::Publisher drone0_reset_pub = n.advertise<std_msgs::Empty>("drone0/ardrone/reset", 1);
    ros::Publisher drone0_land_pub = n.advertise<std_msgs::Empty>("drone0/ardrone/land", 1);
    ros::Publisher drone0_cmd_vel_pub = n.advertise<geometry_msgs::Twist>("drone0/cmd_vel", 1);

    ros::Publisher drone1_takeoff_pub = n.advertise<std_msgs::Empty>("drone1/ardrone/takeoff", 1);
    ros::Publisher drone1_reset_pub = n.advertise<std_msgs::Empty>("drone1/ardrone/reset", 1);
    ros::Publisher drone1_land_pub = n.advertise<std_msgs::Empty>("drone1/ardrone/land", 1);
    ros::Publisher drone1_cmd_vel_pub = n.advertise<geometry_msgs::Twist>("drone1/cmd_vel", 1);

}

/*
 * Move drone "name" to grid cell (x,y). 
 * Return true if successful, false otherwise.
 */
bool drone_nav::move_on_grid(string name, int x, int y) {
    //>>>>make sure drone is valid in drones vector 
    if (!is_valid_grid_cell(x, y))
        return false; 

    
}

bool drone_nav::move_absolute(string, double, double, double) {

}

bool drone_nav::is_valid_grid_cell(int, int) {

}


