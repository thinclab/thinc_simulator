/*
 * Responsible for navigating the drones on the grid in simulation.
 */

#include "drone_nav.hpp"
#include "drone.cpp"

int main(int argc, char* argv[]) {

    ros::init(argc, argv, "mover"); 
    ros::Rate loop_rate(10); 
    //first two arguments are columns and rows, respectively.
    int c, r; 
    stringstream s1(argv[0]);
    s1 >> c;
    stringstream s2(argv[1]);
    s2 >> r;

    //after columns and rows, arguments proceed as follows: 
    //drone name, spawn x position, spawn y position, and
    //repeat n times for n drones
    vector<drone*> drones;  
    ros::init(argc, argv, "mover"); 
    for (int i = 0; i < argc; i++) {
        int x, y; 
        string name = argv[2 + 3*i]; 
        string x_string = argv[3 + 3*i]; 
        string y_string = argv[4 + 3*i]; 
        stringstream s3(x_string); 
        s3 >> x; 
        stringstream s4(y_string);
        s4 >> y; 
        
        drone* d = new drone(name, x, y); 
        drones.push_back(d); 
    }

    drone_nav* dn = new drone_nav(drones, c, r);
    dn->advertise(drones);
}

/*
 * Constructor for drone_nav object.
 * Columns is the number of columns in 
 * grid, and rows is the number of rows.
 */
drone_nav::drone_nav(vector<drone*> d, int c, int r) {
    drones = vector<drone*>(d); 
    columns = c; 
    rows = r; 
}

/*
 * Advertise to appropriate topics for given drones.
 * Each drone has its own set of topics.
 */
void drone_nav::advertise(vector<drone*> drones) {
    for(std::vector<int>::size_type i = 0; i != drones.size(); i++) {
        drones[i]->advertise(); 
    }
}

/*
 * Move drone "name" to grid cell (x,y). 
 * Return true if successful, false otherwise.
 */
bool drone_nav::move_on_grid(string name, int x, int y) {
    //>>>>make sure drone is valid in drones vector 
    if (!is_valid_grid_cell(x, y))
        return false; 

    drone* d = find_drone(name); 
    if (d == NULL)
        return false; //drone doesn't exist with name "name" 

    d->move_on_grid(x,y); 
    return true; 
}

/*
 * Move the drone with the given name to absolute
 * position (x,y,z). 
 */
bool drone_nav::move_absolute(string name, double x, double y, double z) {
    drone* d = find_drone(name); 
    if (d == NULL)
        return false; //drone doesn't exist with name "name"

    d->move_absolute(x,y,z); 
    return true;        
}

/*
 * Determine if the given grid cell (x,y) is valid.
 * Return true if it is, otherwise return false. Note 
 * that 0,0 represents the corner of the grid, and is 
 * not a valid grid cell. Valid values are 
 * (1,1) -> (columns, rows)
 */
bool drone_nav::is_valid_grid_cell(int x, int y) {
    if (x < 1 || y < 1 || x > columns || y > rows)
        return false; 

    return true; 
}

/*
 * Find the drone in the vector of drones with the
 * given name.
 */
drone* drone_nav::find_drone(string name) {
    drone* d;
    for(std::vector<int>::size_type i = 0; i != drones.size(); i++) {
        if (drones[i]->name.compare(name)) {
            d = drones[i];
        }
    }
    
    return d; 
}


