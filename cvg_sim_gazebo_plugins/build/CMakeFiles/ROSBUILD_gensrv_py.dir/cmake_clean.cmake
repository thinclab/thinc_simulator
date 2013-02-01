FILE(REMOVE_RECURSE
  "../srv_gen"
  "../src/cvg_sim_gazebo_plugins/srv"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_py"
  "../src/cvg_sim_gazebo_plugins/srv/__init__.py"
  "../src/cvg_sim_gazebo_plugins/srv/_SetBias.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
