#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <math.h>

using namespace std; 

int main() {
    for (int j = 0; j < 8; j++) {
        ifstream ifs; 
        if (j == 0) {
            ifs.open("drone1_run1.txt");
            cout << "Drone v.2" << endl; 
        }
        else if (j == 1)
            ifs.open("drone1_run2.txt");
        else if (j == 2)
            ifs.open("drone1_run3_bw.txt"); 
        else if (j == 3)
            ifs.open("drone1_run4_bw.txt"); 
        else if (j == 4) {
            ifs.open("drone2_run1.txt");  
            cout << "Drone v.1" << endl; 
        }
        else if (j == 5)
            ifs.open("drone2_run2.txt"); 
        else if (j == 6)
            ifs.open("drone2_run3_bw.txt"); 
        else if (j == 7)
            ifs.open("drone2_run4_bw.txt"); 

        string line; 
        vector<double> x_values; 
        vector<double> y_values; 
        vector<double> z_values; 
        bool frame_line = true; 
        bool remove = true; 
        double x_drift = 0;
        double y_drift = 0; 
        double z_drift = 0;
        double total_drift = 0; 
    
        while (ifs.good()) {
            if (remove) {
                for (int i = 0; i < 44; i++) 
                    getline(ifs, line); 
                remove = false; 
            }

            if (!frame_line) {
                getline(ifs, line); 
                frame_line = true; 
             }
    
            else {
                getline(ifs, line);
                stringstream ss(line); 
                string word; 
    
                for (int i = 0; i < 5; i++) 
                    getline(ss, word, ','); 
    
                for (int i = 0; i < 3; i++) {
                    getline(ss, word, ','); 
    
                    if (i == 0)
                        x_values.push_back(atof(word.c_str())); 
    
                    else if (i == 1)
                        y_values.push_back(atof(word.c_str())); 
    
                    else
                        z_values.push_back(atof(word.c_str())); 
                }
                frame_line = false; 
            }

        }

        for(vector<double>::size_type i = 0; i != x_values.size(); i++) {
            double x_diff = x_values[i] - x_values[i-1];
            double y_diff = y_values[i] - y_values[i-1];
            double z_diff = z_values[i] - z_values[i-1];
 
            x_drift += abs(x_diff); 
            y_drift += abs(y_diff); 
            z_drift += abs(z_diff); 
             
            if (i == 0) {
                //do nothing
            }
            else {
                total_drift += sqrt(x_diff*x_diff + y_diff*y_diff + z_diff*z_diff); 
            }
        }

        cout << "Total drift: " << total_drift << endl; 
        cout << "X drift: " << x_drift << endl; 
        cout << "Y drift: " << y_drift << endl; 
        cout << "Z drift: " << z_drift << endl; 

        ifs.close(); 

    }

}
