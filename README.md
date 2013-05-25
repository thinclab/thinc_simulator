thinc\_simulator
===============

Installation
------------

```bash
$ cd ~/ros/stacks   # or equivalent
$ git clone https://github.com/dmillard/thinc_simulator.git
$ rospack profile && rosstack profile
$ rosmake thinc_sim_msgs
$ rosmake message_to_tf
$ rosmake thinc_sim_gazebo_plugins
```

Notes
-----

* This requires https://github.com/AutonomyLab/ardrone_autonomy
* This was designed with https://github.com/dmillard/ardrone_thinc

Usage
-----

To open gazebo with a grid with two drones on it, run

```bash
$ roslaunch thinc_sim_gazebo grid_flight.launch
```

To change the grid size, you must edit the launch file.  Gazebo/ROS doesn't
handle dynamic model generation well, so there is a distateful amount of
hardcoding currently.

To add another drone, copy the spawn_quadrotor sublaunch in the
`grid\_flight.launch` file and modify accordingly.  You will also need to copy
the requisite files in `urdf/`.  Use a commandline tool like `sed` (use the
`-i` option) to modify those files.  Again, I wish there was a more flexible
way, but this is what we have.
