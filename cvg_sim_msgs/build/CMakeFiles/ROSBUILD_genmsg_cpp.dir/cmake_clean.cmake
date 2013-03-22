FILE(REMOVE_RECURSE
  "../msg_gen"
  "../src/cvg_sim_msgs/msg"
  "../msg_gen"
  "CMakeFiles/ROSBUILD_genmsg_cpp"
  "../msg_gen/cpp/include/cvg_sim_msgs/MotorStatus.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/RawRC.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/MotorPWM.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/VelocityXYCommand.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/ThrustCommand.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/ControllerState.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/Altitude.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/VelocityZCommand.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/Compass.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/YawrateCommand.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/MotorCommand.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/PositionXYCommand.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/ServoCommand.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/AttitudeCommand.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/RawImu.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/RC.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/RuddersCommand.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/RawMagnetic.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/Supply.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/Altimeter.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/HeadingCommand.h"
  "../msg_gen/cpp/include/cvg_sim_msgs/HeightCommand.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
