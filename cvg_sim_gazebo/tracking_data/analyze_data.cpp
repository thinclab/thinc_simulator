#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>

using namespace std; 

int main() {
    ifstream ifs; 
    ifs.open("drone1_run1.txt");
    string line; 
    vector<double> x_values;
    vector<double> y_values; 
    vector<double> z_values; 
    bool frame_line = true; 
    bool remove = true; 
    
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
//            cout << line << endl;  
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
//        cout << line << endl; 

    }

    for(vector<double>::size_type i = 0; i != x_values.size(); i++) {
        cout << "<" << x_values[i] << ", " << y_values[i] << ", " << z_values[i] << ">" << endl; 
    }

    ifs.close(); 



}
