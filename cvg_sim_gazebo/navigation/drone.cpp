/*
 * Represents a drone- qualities include position, topics, etc.
 */

#include "drone.hpp"

/*
 * Constructor for a drone. The drone goes by "name" 
 * and has initial grid position (x,y).
 */
drone::drone(string n, int x, int y) {
    id = n; 
    grid_pos[0] = x; 
    grid_pos[1] = y;

//    abs_pos[0] = ~do something
//    abs_pos[1] = ~do something
    
    //we can query absolute position
    //from Gazebo if needed 
}

/*
 * Move the drone to the given grid cell.
 */
void drone::move_on_grid(int new_x, int new_y) {
    bool move_right = false; 
    bool move_left = false; 
    bool move_up = false; 
    bool move_down = false; 
   
    int delta_x = grid_pos[0] - new_x; 
    int delta_y = grid_pos[1] - new_y; 

    if (delta_x < 0)
        move_right = true; 
    else if (delta_x > 0)
        move_left = true; 
    if (delta_y < 0)
        move_up = true; 
    else if (delta_y > 0)
        move_down = true; 

    int x_moves = abs(delta_x); 
    int y_moves = abs(delta_y); 


    /* -linear.x: move backward
     * +linear.x: move forward
     * -linear.y: move right
     * +linear.y: move left
     */

    while (ros::ok() && (x_moves > 0 || y_moves > 0)) {
        //complete all moves in x-direction first
        if (x_moves > 0) {
            if (move_right) {
//                while (~circle not seen...) {
//                    twist_msg.linear.y = -0.25; 
//                }
            }
            else if (move_left) {
//                while (~circle not seen...) {
//                    twist_msg.linear.y = 0.25; 
//                }
            }
     // PUBLISH MESSAGES
            x_moves--; 
        } 
         
         //complete all moves in y-direction second
         else if (y_moves > 0) {
             if (move_up) {
//                 while (~circle not seen...) {
//                     twist_msg.linear.x = 0.25;
//                 }
              }
              else if (move_down) {
//                  while (~circle not seen...) {
//                      twist_msg.linear.x = -0.25;
//                  }
              }
              
              y_moves --; 
         } 
    }
}

/* 
 * Move the drone to a new absolute position. 
 */
void drone::move_absolute(double new_x, double new_y, double new_z) {

}


